#include "vposix_eventfd.h"

#include <assert.h>
#include "verror.h"
#include "vposix_files.h"
#include "vposix_errno.h"
#include <sys/eventfd.h>
#include "vposix_core.h"
#include "vlog_pretty.h"


using namespace vposix;

//=======================================================================================
int EventFD::_semaphore_create()
{
    auto flags = EFD_CLOEXEC | EFD_NONBLOCK | EFD_SEMAPHORE;

    if ( do_trace() ) vtrace( "::eventfd(", 0, flags, ");" );
    return Core::linux_call( ::eventfd, 0, flags );
}
//=======================================================================================
bool EventFD::_semaphore_read( int fd )
{
    eventfd_t buf;
    if ( do_trace() ) vtrace( "::eventfd_read(", fd, ");" );
    auto res = Core::linux_call_or_err( ::eventfd_read, fd, &buf );
    if ( res == -1 )
    {
        auto e = errno;
        if ( e == EAGAIN )
            return false;

        Core::throw_err( e, "Very poor eventfd read" );
    }
    assert( res == 0 && buf == 1 );
    return true;
}
//=======================================================================================
void EventFD::_semaphore_write( int fd )
{
    if ( do_trace() ) vtrace( "::eventfd_write(", fd, "1);" );
    auto res = Core::linux_call( ::eventfd_write, fd, 1 );
    assert( res == 0 );
}
//=======================================================================================


//=======================================================================================
Semaphore::Semaphore()
    : _fd( EventFD::_semaphore_create() )
{}
//=======================================================================================
Semaphore::~Semaphore()
{
    vposix::Files::close( _fd );
}
//=======================================================================================
void Semaphore::inc()
{
    EventFD::_semaphore_write( _fd );
}
//=======================================================================================
bool Semaphore::dec()
{
    return EventFD::_semaphore_read( _fd );
}
//=======================================================================================
int Semaphore::fd() const
{
    return _fd;
}
//=======================================================================================
