#include "vpoll.h"


#include "vposix_epoll.h"

#include <thread>
#include <memory>
#include <assert.h>
#include "vstd_atomic_map.h"
#include "vlog_pretty.h"


//=======================================================================================
//  UPD 22-11-2018 -- Ниже написанное устарело, требуется переосмысление.

//  Задача: привязать к каждому потоку свой VPoll_Impl, так, чтобы пользователю было
//  прозрачно. Использование VPoll_Impl не должно быть ограничено, при необходимости
//  нужно, чтобы его передача между потоками была безопасна.
//
//  Придумалась следующая машинерия: VPoll_Impl работает только статическими методами,
//  обращаясь к инкапсулированным Real_Poll-ам.
//=======================================================================================



//=======================================================================================
//  Пусть пока здесь лежит, чувствую, захочется еще контролов на поток поставить.
class Real_Poll
{
public:
    using Ptr = std::shared_ptr<Real_Poll>;

    vposix::EPoll native_poll;
};
//=======================================================================================


//=======================================================================================
//  Проецирует по одному поллингу на поток.
class Thread_2_Poll
{
    vstd::atomic_map<std::thread::id, Real_Poll::Ptr> th_2_poll;

public:
    //-----------------------------------------------------------------------------------
    void add()
    {
        auto id = std::this_thread::get_id();
        assert( !th_2_poll.contains(id) );
        auto ptr = std::make_shared<Real_Poll>();
        th_2_poll.emplace( id, ptr );
    }
    //-----------------------------------------------------------------------------------
    Real_Poll::Ptr& get()
    {
        auto id = std::this_thread::get_id();

        //  Если ошибка произошла здесь, значит:
        //      - не было создано VApplication в главном потоке, или
        //      - поток был создан не через VThread и в нем нету механизма поллинга.
        return th_2_poll.at( id );
    }
    //-----------------------------------------------------------------------------------
    void del()
    {
        auto id = std::this_thread::get_id();
        auto ok = th_2_poll.erase( id );
        assert( ok );
    }
    //-----------------------------------------------------------------------------------
    ~Thread_2_Poll()
    {
        if ( !th_2_poll.empty() )
            vfatal << "Thread to poll: polls is not empty, some threads closed "
                      "inaccuracy.";
    }
    //-----------------------------------------------------------------------------------
};
//=======================================================================================

//=======================================================================================
static Thread_2_Poll& th_2_poll()
{
    static Thread_2_Poll res;
    return res;
}
//=======================================================================================
void VPoll::add_fd( int fd, EventReceiver *receiver, Direction d, Triggered t )
{
    bool dir_in  = d == Direction::In  || d == Direction::InOut;
    bool dir_out = d == Direction::Out || d == Direction::InOut;
    bool trigg   = t == Triggered::Edge;

    th_2_poll().get()->native_poll.add( fd, receiver, dir_in, dir_out, trigg );
}
//=======================================================================================
void VPoll::mod_fd(int fd, EventReceiver *receiver, Direction d, Triggered t )
{
    bool dir_in  = d == Direction::In  || d == Direction::InOut;
    bool dir_out = d == Direction::Out || d == Direction::InOut;
    bool trigg   = t == Triggered::Edge;

    th_2_poll().get()->native_poll.mod( fd, receiver, dir_in, dir_out, trigg );
}
//=======================================================================================
void VPoll::del_fd( int fd )
{
    th_2_poll().get()->native_poll.del( fd );
}
//=======================================================================================
//void VPoll::poll_once( int timeout_ms )
//{
//    auto& rpoll = th_2_poll().get();
//    auto& poll = rpoll->native_poll;

//    auto ev = poll.wait_1( timeout_ms );
//    auto event = static_cast<EventReceiver*>( ev.data.ptr );
//    event->event_received( ev.events );
//}
//=======================================================================================
void VPoll::poll( bool *stop, int timeout_ms )
{
    auto& poll = th_2_poll().get()->native_poll;

    std::vector<epoll_event> events(Wait_Max_Events);

    while ( !*stop )
    {
        auto cnt = poll.wait_many( &events, timeout_ms );
        assert( cnt >= 0 && cnt <= int(events.size()) );

        // Здесь может быть ситуация, когда попросили выключить очередь (*stop == true),
        // но после этого еще есть события. Будем считать, что их следует обработать.
        for ( int i = 0; i < cnt; ++i )
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
VPoll::EventFlags::EventFlags(uint32_t evs)
    : _events(evs)
{}
//=======================================================================================
bool VPoll::EventFlags::IN() const
{
    return vposix::EPoll::has_EPOLLIN( _events );
}
//=======================================================================================
bool VPoll::EventFlags::IN_only() const
{
    return vposix::EPoll::only_EPOLLIN( _events );
}
//=======================================================================================
