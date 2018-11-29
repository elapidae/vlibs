#include "vposix_epoll.h"

#include <string.h>
#include <assert.h>
#include <algorithm>

#include "vposix_core.h"
#include "vposix_files.h"

#include "vlog_pretty.h"


using namespace vposix;

//=======================================================================================
int vposix::EPoll::_create()
{
    if ( do_trace() ) vtrace( "V::epoll_create1(CLOEXEC);" );

    return Core::linux_call( ::epoll_create1, "::epoll_create1", EPOLL_CLOEXEC );
}
//=======================================================================================
uint EPoll::_wait( int fd, epoll_event *events, int maxevents, int wait_ms )
{
    if ( do_trace() ) vtrace( "V::epoll_wait(", fd, maxevents, wait_ms, ")" );

    auto res = Core::linux_call( ::epoll_wait, "::epoll_wait",
                                 fd, events, maxevents, wait_ms );
    return uint( res );
}
//=======================================================================================
void EPoll::_add( int epoll_fd, int fd, epoll_event* event )
{
    if ( do_trace() ) vtrace( "V::epoll_add(", epoll_fd, fd, event, ")" );

    auto res = Core::linux_call( ::epoll_ctl, "::epoll_ctl",
                                 epoll_fd, EPOLL_CTL_ADD, fd, event );
    assert( res == 0 );
}
//=======================================================================================
void EPoll::_mod( int epoll_fd, int fd, epoll_event* event )
{
    if ( do_trace() ) vtrace( "V::epoll_mod(", epoll_fd, fd, event, ")" );

    auto res = Core::linux_call( ::epoll_ctl, "::epoll-> _mod",
                                 epoll_fd, EPOLL_CTL_MOD, fd, event );
    assert( res == 0 );
}
//=======================================================================================
void EPoll::_del( int epoll_fd, int fd )
{
    if ( do_trace() ) vtrace( "V::epoll_del(", epoll_fd, fd, ")" );

    epoll_event event;
    auto res = Core::linux_call( ::epoll_ctl, vcat("::epoll-> _del[", fd, "]"),
                                 epoll_fd, EPOLL_CTL_DEL, fd, &event );
    assert( res == 0 );
}
//=======================================================================================


//=======================================================================================
uint32_t EPoll::flag_IN()
{ return EPOLLIN; }
//=======================================================================================
uint32_t EPoll::flag_OUT()
{ return EPOLLOUT; }
//=======================================================================================
uint32_t EPoll::flag_PRI()
{ return EPOLLPRI; }
//=======================================================================================
uint32_t EPoll::flag_RDNORM()
{ return EPOLLRDNORM; }
//=======================================================================================
uint32_t EPoll::flag_RDBAND()
{ return EPOLLRDBAND; }
//=======================================================================================
uint32_t EPoll::flag_WRNORM()
{ return EPOLLWRNORM; }
//=======================================================================================
uint32_t EPoll::flag_WRBAND()
{ return EPOLLWRBAND; }
//=======================================================================================
uint32_t EPoll::flag_MSG()
{ return EPOLLMSG; }
//=======================================================================================
uint32_t EPoll::flag_ERR()
{ return EPOLLERR; }
//=======================================================================================
uint32_t EPoll::flag_HangUp()
{ return EPOLLHUP; }
//=======================================================================================
uint32_t EPoll::flag_RD_HangUp()
{ return EPOLLRDHUP; }
//=======================================================================================


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
static decltype(epoll_event().events)
compile_events( bool dir_in, bool dir_out, bool trigg )
{
    //  Пока нет понимания какие из флагов полезные, какие фтопку, какие на выбор.

    decltype(epoll_event().events)
    res =   EPOLLRDHUP  |
            EPOLLPRI    |
            EPOLLERR    |   //  Судя по документации, можно не устанавливать
            EPOLLHUP;       //

    if ( dir_in  ) res |= EPOLLIN;
    if ( dir_out ) res |= EPOLLOUT;
    if ( trigg   ) res |= EPOLLET;

    return res;
}
//=======================================================================================
void EPoll::add( int fd, void* arg, bool dir_in, bool dir_out, bool trigg )
{
    epoll_event ev;
    ev.data.ptr = arg;
    ev.events = compile_events( dir_in, dir_out, trigg );

    _add( _epoll_fd, fd, &ev );
    ++_count;
}
//=======================================================================================
void EPoll::mod( int fd, void *arg, bool dir_in, bool dir_out, bool trigg )
{
    epoll_event ev;
    ev.data.ptr = arg;
    ev.events = compile_events( dir_in, dir_out, trigg );

    _mod( _epoll_fd, fd, &ev );
}
//=======================================================================================
void EPoll::del( int fd )
{
    _del( _epoll_fd, fd );
    --_count;
}
//=======================================================================================
uint EPoll::wait( std::vector<epoll_event>* res, int wait_ms )
{
    assert( _count > 0 );
    assert( !res->empty() );

    return _wait( _epoll_fd, res->data(), int(res->size()), wait_ms );
}
//=======================================================================================
