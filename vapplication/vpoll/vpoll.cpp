/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


#include "vpoll.h"


#include "vposix_epoll.h"

#include <thread>
#include <memory>
#include <assert.h>
#include "vstd_atomic_map.h"
#include "vlog.h"
#include "verror.h"
#include "vcompiler.h" // for V_COMPILER_KNOWS_THREAD_LOCAL


//=======================================================================================
//  UPD 22-11-2018 -- Ниже написанное устарело, требуется переосмысление.
//
//  Задача: привязать к каждому потоку свой VPoll_Impl, так, чтобы пользователю было
//  прозрачно. Использование VPoll_Impl не должно быть ограничено, при необходимости
//  нужно, чтобы его передача между потоками была безопасна.
//
//  Придумалась следующая машинерия: VPoll_Impl работает только статическими методами,
//  обращаясь к инкапсулированным Real_Poll-ам.
//=======================================================================================


//=======================================================================================
//  UPD 27-12-2018  by Elapidae
//
//  Касаемо класса Thread_2_Poll и статической функции th_2_poll() -- введены, во-первых,
//  чтобы старый компилятор юзал атомарный словарь, а нормальные посоны пользовались
//  thread_local. Удаление поллинга сделано ручным, т.к. приходится учитывать, что
//  старый компилятор сам не сможет очистить ресурсы.
//=======================================================================================
#if (V_COMPILER_KNOWS_THREAD_LOCAL)
class Thread_2_Poll final
{
    vposix::EPoll epoll;
    int init_count = 0;
public:
    //-----------------------------------------------------------------------------------
    void add()
    {
        ++init_count;
        assert( init_count == 1 );
    }
    //-----------------------------------------------------------------------------------
    vposix::EPoll& current()
    {
        assert( init_count == 1 );
        return epoll;
    }
    //-----------------------------------------------------------------------------------
    void del()
    {
        --init_count;
        assert( init_count == 0 );
    }
    //-----------------------------------------------------------------------------------
    ~Thread_2_Poll()
    {
       assert( init_count == 0 );
    }
};
//=======================================================================================
static Thread_2_Poll& th_2_poll()
{
    static thread_local Thread_2_Poll res;
    return res;
}
//=======================================================================================
#else // V_COMPILER_KNOWS_THREAD_LOCAL
//=======================================================================================
//  Проецирует по одному поллингу на поток.
class Thread_2_Poll_OldSys
{
    using epoll_ptr = std::shared_ptr<vposix::EPoll>;
    vstd::atomic_map<std::thread::id, epoll_ptr> th_2_poll;

public:
    //-----------------------------------------------------------------------------------
    void add()
    {
        auto id = std::this_thread::get_id();
        assert( !th_2_poll.contains(id) );
        auto ptr = std::make_shared<vposix::EPoll>();
        th_2_poll.emplace( id, ptr );
    }
    //-----------------------------------------------------------------------------------
    vposix::EPoll& current()
    {
        auto id = std::this_thread::get_id();

        //  Если ошибка произошла здесь, значит:
        //      - не было создано VApplication в главном потоке, или
        //      - поток был создан не через VThread и в нем нету механизма поллинга.
        try
        {
            return *th_2_poll.at(id);
        }
        catch ( const std::out_of_range& )
        {
            throw verror("Poll loop is not ready for this thread. "
                         "Use VApplication and VThread for nice.");
        }
    }
    //-----------------------------------------------------------------------------------
    void del()
    {
        auto id = std::this_thread::get_id();
        auto ok = th_2_poll.erase( id );
        assert( ok );
    }
    //-----------------------------------------------------------------------------------
    ~Thread_2_Poll_OldSys()
    {
        if ( !th_2_poll.empty() )
            vfatal << "Thread to poll: polls is not empty, some threads closed "
                      "inaccuracy.";
    }
    //-----------------------------------------------------------------------------------
};
//=======================================================================================
static Thread_2_Poll_OldSys& th_2_poll()
{
    static Thread_2_Poll_OldSys res;
    return res;
}
#endif // V_COMPILER_KNOWS_THREAD_LOCAL
//=======================================================================================


//=======================================================================================
void VPoll::add_fd( int fd, EventReceiver *receiver, Direction d, Triggered t )
{
    bool dir_in  = d == Direction::In  || d == Direction::InOut;
    bool dir_out = d == Direction::Out || d == Direction::InOut;
    bool trigg   = t == Triggered::Edge;

    th_2_poll().current().add( fd, receiver, dir_in, dir_out, trigg );
}
//=======================================================================================
void VPoll::mod_fd(int fd, EventReceiver *receiver, Direction d, Triggered t )
{
    bool dir_in  = d == Direction::In  || d == Direction::InOut;
    bool dir_out = d == Direction::Out || d == Direction::InOut;
    bool trigg   = t == Triggered::Edge;

    th_2_poll().current().mod( fd, receiver, dir_in, dir_out, trigg );
}
//=======================================================================================
void VPoll::del_fd( int fd )
{
    th_2_poll().current().del( fd );
}
//=======================================================================================
void VPoll::poll( bool *stop, int timeout_ms )
{
    std::vector<epoll_event> events( Wait_Max_Events );

    *stop = false;
    while ( !*stop )
    {
        auto cnt = th_2_poll().current().wait( &events, timeout_ms );
        assert( cnt <= events.size() );

        // Здесь может быть ситуация, когда попросили выключить очередь (*stop == true),
        // но после этого еще есть события. Будем считать, что их следует обработать.
        for ( uint i = 0; i < cnt; ++i )
        {
            auto ev = events[i];
            auto event = static_cast<EventReceiver*>( ev.data.ptr );
            event->event_received( ev.events );
        }
    }
}
//=======================================================================================
void VPoll::add_poll()
{
    th_2_poll().add();
}
//=======================================================================================
void VPoll::del_poll()
{
    th_2_poll().del();
}
//=======================================================================================


//=======================================================================================
//      EventFlags
//=======================================================================================
VPoll::EventFlags::EventFlags(uint32_t evs)
    : _events(evs)
{}
//=======================================================================================
bool VPoll::EventFlags::take_IN()
{ return _take_flag( vposix::EPoll::flag_IN() ); }
//=======================================================================================
bool VPoll::EventFlags::take_OUT()
{ return _take_flag( vposix::EPoll::flag_OUT() ); }
//=======================================================================================
bool VPoll::EventFlags::take_HangUp()
{ return _take_flag( vposix::EPoll::flag_HangUp() ); }
//=======================================================================================
bool VPoll::EventFlags::take_RD_HangUp()
{ return _take_flag( vposix::EPoll::flag_RD_HangUp() ); }
//=======================================================================================
bool VPoll::EventFlags::take_ERR()
{ return _take_flag( vposix::EPoll::flag_ERR() ); }
//=======================================================================================
uint32_t VPoll::EventFlags::raw() const
{
    return _events;
}
//=======================================================================================
bool VPoll::EventFlags::empty() const
{
    return _events == 0;
}
//=======================================================================================
void VPoll::EventFlags::throw_not_empty() const
{
    if ( !empty() )
        throw verror( "Event flags not read at all, leaved:", _events );
}
//=======================================================================================
bool VPoll::EventFlags::_take_flag( uint32_t flag )
{
    bool res = _events & flag;
    _events &= ~flag;
    return res;
}
//=======================================================================================
//      EventFlags
//=======================================================================================


//=======================================================================================
//      FD_Polled
//=======================================================================================
FD_Polled::FD_Polled()
    : _fd()
{}
//=======================================================================================
FD_Polled::FD_Polled( int fd,
                      VPoll::EventReceiver *receiver,
                      const vposix::FD::close_func &cf,
                      VPoll::Direction d,
                      VPoll::Triggered t )
    : _fd( fd, cf )
{
    VPoll::add_fd( fd, receiver, d, t );
}
//=======================================================================================
FD_Polled::FD_Polled( FD_Polled && rhs )
    : _fd( std::move(rhs._fd) )
{}
//=======================================================================================
FD_Polled &FD_Polled::operator = ( FD_Polled && rhs )
{
    if ( this != &rhs )
    {
        close();
        _fd = std::move( rhs._fd );
    }
    return *this;
}
//=======================================================================================
FD_Polled::~FD_Polled()
{
    close();
}
//=======================================================================================
bool FD_Polled::valid() const
{
    return _fd.valid();
}
//=======================================================================================
void FD_Polled::close()
{
    if ( _fd.valid() )
        VPoll::del_fd( _fd.raw() );

    _fd.close();
}
//=======================================================================================
int FD_Polled::raw() const
{
    return _fd.raw();
}
//=======================================================================================
//      FD_Polled
//=======================================================================================


//=======================================================================================
//  Declaration for old compilers...
VPoll::EventReceiver::~EventReceiver()
{}
//=======================================================================================
