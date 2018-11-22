#include "vpoll_fds.h"


#include "vposix_epoll.h"

#include <thread>
#include <memory>
#include <assert.h>
#include "vstd_atomic_map.h"


//=======================================================================================
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
};
//=======================================================================================

//=======================================================================================
static Thread_2_Poll& th_2_poll()
{
    static Thread_2_Poll res;
    return res;
}
//=======================================================================================
void VPoll_FDs::add_fd( int fd, VEventReceiver *receiver, Direction d, Triggered t )
{
    bool dir_in  = d == Direction::In  || d == Direction::InOut;
    bool dir_out = d == Direction::Out || d == Direction::InOut;
    bool trigg   = t == Triggered::Edge;

    th_2_poll().get()->native_poll.add( fd, receiver, dir_in, dir_out, trigg );
}
//=======================================================================================
void VPoll_FDs::mod_fd( int fd, VEventReceiver *receiver, Direction d, Triggered t )
{
    bool dir_in  = d == Direction::In  || d == Direction::InOut;
    bool dir_out = d == Direction::Out || d == Direction::InOut;
    bool trigg   = t == Triggered::Edge;

    th_2_poll().get()->native_poll.mod( fd, receiver, dir_in, dir_out, trigg );
}
//=======================================================================================
void VPoll_FDs::del_fd( int fd )
{
    th_2_poll().get()->native_poll.del( fd );
}
//=======================================================================================
void VPoll_FDs::poll_once( int timeout_ms )
{
    auto& rpoll = th_2_poll().get();
    auto& poll = rpoll->native_poll;

    auto ev = poll.wait_1( timeout_ms );
    auto event = static_cast<VEventReceiver*>( ev.data.ptr );
    event->event_received( ev.events );
}
//=======================================================================================
void VPoll_FDs::poll( volatile bool *stop, int timeout_ms)
{
    auto& rpoll = th_2_poll().get();
    auto& poll = rpoll->native_poll;

    while ( !*stop )
    {
        auto ev = poll.wait_1( timeout_ms );
        auto event = static_cast<VEventReceiver*>( ev.data.ptr );
        event->event_received( ev.events );
    }
}
//=======================================================================================
void VPoll_FDs::add_poll()
{
    th_2_poll().add();
}
//=======================================================================================
void VPoll_FDs::del_poll()
{
    th_2_poll().del();
}
//=======================================================================================


//=======================================================================================
VPoll_FDs::EventFlags::EventFlags(uint32_t evs)
    : _events(evs)
{}
//=======================================================================================
bool VPoll_FDs::EventFlags::IN() const
{
    return vposix::EPoll::has_EPOLLIN( _events );
}
//=======================================================================================
