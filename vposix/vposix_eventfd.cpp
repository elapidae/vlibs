#include "vposix_eventfd.h"

#include <assert.h>
#include "verror.h"
#include "vposix_files.h"
#include "vposix_errno.h"
#include <sys/eventfd.h>

using namespace vposix;

//=======================================================================================
int EventFD::_semaphore_create()
{
    return eventfd( 0, EFD_CLOEXEC | EFD_NONBLOCK | EFD_SEMAPHORE );
}
//=======================================================================================
bool EventFD::_semaphore_read( int fd )
{
    eventfd_t buf;
    auto res = eventfd_read( fd, &buf );
    if ( res == -1 )
    {
        auto e = errno;
        if ( e == EAGAIN )
            return false;

        throw verror( "Very poor eventfd read:", Errno::str_error(e) );
    }
    assert( res == 0 && buf == 1 );
    return true;
}
//=======================================================================================
void EventFD::_semaphore_write( int fd )
{
    auto res = eventfd_write( fd, 1 );
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
