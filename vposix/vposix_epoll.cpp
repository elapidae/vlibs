#include "vposix_epoll.h"

#include "vlog_pretty.h"
#include <assert.h>
#include "vposix_errno.h"
#include "vposix_core.h"

using namespace vposix;

//=======================================================================================
int vposix::EPoll::_create()
{
    if ( do_trace() ) vtrace( "epoll_create1(CLOEXEC);" );
    return linux_call_eintr<int>( epoll_create1, EPOLL_CLOEXEC );
}
//=======================================================================================
int EPoll::_wait( int fd, epoll_event *events, int maxevents, int wait_ms )
{
    if ( do_trace() ) vtrace( "epoll_wait(", fd, maxevents, wait_ms, ")" );
    return linux_call_eintr<int>( epoll_wait, fd, events, maxevents, wait_ms );
}
//=======================================================================================
void EPoll::_add( int epoll_fd, int fd, epoll_event *event )
{
    if ( do_trace() ) vtrace( "epoll_add(", epoll_fd, fd, event, ")" );
    auto res = linux_call_eintr<int>( epoll_ctl, epoll_fd, EPOLL_CTL_ADD, fd, event );
    assert( res == 0 );
}
//=======================================================================================
void EPoll::_del( int epoll_fd, int fd )
{
    if ( do_trace() ) vtrace( "epoll_del(", epoll_fd, fd, ")" );
    epoll_event event;
    auto res = linux_call_eintr<int>( epoll_ctl, epoll_fd, EPOLL_CTL_DEL, fd, &event );
    assert( res == 0 );
}
//=======================================================================================


//=======================================================================================
std::vector<epoll_event> EPoll::wait( int maxevents, int wait_ms )
{
    assert( maxevents > 0 );
    std::vector<epoll_event> res( (size_t(maxevents)) );
    auto wres = _wait( _epoll_fd, res.data(), maxevents, wait_ms );
    res.resize( size_t(wres) );
    return res;
}
//=======================================================================================


//=======================================================================================
bool EPoll::EventFlags::IN() const
{
    return _events & EPOLLIN;
}
//=======================================================================================
bool EPoll::EventFlags::OUT() const
{
    return _events & EPOLLOUT;
}
//=======================================================================================
bool EPoll::EventFlags::RDHUP() const
{
    return _events & EPOLLRDHUP;
}
//=======================================================================================
bool EPoll::EventFlags::PRI() const
{
    return _events & EPOLLPRI;
}
//=======================================================================================
bool EPoll::EventFlags::ERR() const
{
    return _events & EPOLLERR;
}
//=======================================================================================
bool EPoll::EventFlags::HUP() const
{
    return _events & EPOLLHUP;
}
//=======================================================================================
