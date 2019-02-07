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


#include "vposix_eventfd.h"

#include <sys/eventfd.h>

#include "vposix_files.h"
#include "vposix_core.h"

#include <assert.h>
#include "verror.h"
#include "vlog.h"


using namespace vposix;

//=======================================================================================
int EventFD::_semaphore_create()
{
    auto flags = EFD_CLOEXEC | EFD_NONBLOCK | EFD_SEMAPHORE;
    int count = 0; // initial count of events.

    if ( do_trace() ) vtrace( "V::eventfd(", count, flags, ");" );
    return Core::linux_call( ::eventfd, "::eventfd", count, flags );
}
//=======================================================================================
bool EventFD::_semaphore_read( int fd )
{
    eventfd_t buf;
    if ( do_trace() ) vtrace( "V::eventfd_read(", fd, ");" );
    auto res = Core::linux_call_or_err( ::eventfd_read, fd, &buf );
    if ( res == -1 )
    {
        Errno e;
        if ( e.resource_unavailable_try_again() )
            return false;

        e.throw_verror("EventFD::_semaphore_read");
    }
    assert( res == 0 && buf == 1 );
    return true;
}
//=======================================================================================
void EventFD::_semaphore_write( int fd )
{
    if ( do_trace() ) vtrace( "V::eventfd_write(", fd, "1);" );
    auto res = Core::linux_call( ::eventfd_write, "::eventfd_write", fd, 1 );
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
