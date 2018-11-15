#include "vposix_epoll.h"

#include <sys/epoll.h>
#include <assert.h>

#include "vposix_errno.h"
#include "vposix_core.h"
#include "vposix_files.h"

#include "vlog_pretty.h"


using namespace vposix;

//=======================================================================================
int vposix::EPoll::_create()
{
    if ( do_trace() ) vtrace( "V::epoll_create1(CLOEXEC);" );
    return Core::linux_call( ::epoll_create1, EPOLL_CLOEXEC );
}
//=======================================================================================
int EPoll::_wait( int fd, epoll_event *events, int maxevents, int wait_ms )
{
    if ( do_trace() ) vtrace( "V::epoll_wait(", fd, maxevents, wait_ms, ")" );
    return Core::linux_call( ::epoll_wait, fd, events, maxevents, wait_ms );
}
//=======================================================================================
void EPoll::_add( int epoll_fd, int fd, epoll_event* event )
{
    if ( do_trace() ) vtrace( "epoll_add(", epoll_fd, fd, event, ")" );
    //auto res = Core::linux_call<int>( epoll_ctl, epoll_fd, EPOLL_CTL_ADD, fd, event );
    auto res = Core::linux_call( epoll_ctl, epoll_fd, EPOLL_CTL_ADD, fd, event );
    assert( res == 0 );
}
//=======================================================================================
void EPoll::_mod( int epoll_fd, int fd, epoll_event* event )
{
    if ( do_trace() ) vtrace( "epoll_mod(", epoll_fd, fd, event, ")" );
    //auto res = Core::linux_call<int>( epoll_ctl, epoll_fd, EPOLL_CTL_MOD, fd, event );
    auto res = Core::linux_call( epoll_ctl, epoll_fd, EPOLL_CTL_MOD, fd, event );
    assert( res == 0 );
}
//=======================================================================================
void EPoll::_del( int epoll_fd, int fd )
{
    if ( do_trace() ) vtrace( "epoll_del(", epoll_fd, fd, ")" );
    epoll_event event;
    //auto res = Core::linux_call<int>( epoll_ctl, epoll_fd, EPOLL_CTL_DEL, fd, &event );
    auto res = Core::linux_call( epoll_ctl, epoll_fd, EPOLL_CTL_DEL, fd, &event );
    assert( res == 0 );
}
//=======================================================================================


//=======================================================================================
bool EPoll::has_EPOLLIN( uint32_t events )
{
    return events & EPOLLIN;
}
//=======================================================================================
EPoll::EPoll()
    : _epoll_fd( _create() )
{}
//=======================================================================================
EPoll::~EPoll()
{
    assert( _count == 0 );
    Files::close( _epoll_fd );
}
//=======================================================================================
void EPoll::add( int fd, bool dir_in, bool dir_out, bool trigg )
{
    epoll_event ev;
    ev.data.fd = fd;

    //  Пока нет понимания какие из флагов полезные, какие фтопку, какие на выбор.
    ev.events = EPOLLRDHUP  |
                EPOLLPRI    |
                EPOLLERR    |
                EPOLLHUP;

    if ( dir_in  ) ev.events |= EPOLLIN;
    if ( dir_out ) ev.events |= EPOLLOUT;

    if ( trigg   ) ev.events |= EPOLLET;

    raw_add( fd, &ev );
}
//=======================================================================================
void EPoll::raw_add( int fd, epoll_event* event )
{
    _add( _epoll_fd, fd, event );
    ++_count;
}
//=======================================================================================
//void EPoll::add( int fd, epoll_event *event )
//{
//    _add( _epoll_fd, fd, event );
//    ++_count;
//}
//=======================================================================================
void EPoll::raw_mod(int fd, epoll_event *event)
{
    _mod( _epoll_fd, fd, event );
}
//=======================================================================================
void EPoll::del( int fd )
{
    _del( _epoll_fd, fd );
    --_count;
}
//=======================================================================================
void EPoll::wait( CallBack cb, int maxevents, int wait_ms )
{
    assert( maxevents > 0 );
    std::vector<epoll_event> events( (size_t(maxevents)) );
    auto wres = _wait( _epoll_fd, events.data(), maxevents, wait_ms );
    events.resize( size_t(wres) );

    for ( auto& ev: events )
        cb( ev.data.fd, ev.events );
}
//=======================================================================================


//=======================================================================================
//bool EPoll::EventFlags::IN() const
//{
//    return _events & EPOLLIN;
//}
//=======================================================================================
//bool EPoll::EventFlags::OUT() const
//{
//    return _events & EPOLLOUT;
//}
//=======================================================================================
//bool EPoll::EventFlags::RDHUP() const
//{
//    return _events & EPOLLRDHUP;
//}
//=======================================================================================
//bool EPoll::EventFlags::PRI() const
//{
//    return _events & EPOLLPRI;
//}
//=======================================================================================
//bool EPoll::EventFlags::ERR() const
//{
//    return _events & EPOLLERR;
//}
//=======================================================================================
//bool EPoll::EventFlags::HUP() const
//{
//    return _events & EPOLLHUP;
//}
//=======================================================================================
