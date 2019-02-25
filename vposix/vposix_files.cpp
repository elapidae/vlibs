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


#include "vposix_files.h"

#include "vlog.h"
#include "vposix_core.h"
#include <assert.h>

//  Here:   ::open
#include <fcntl.h>

//  Here:   ::write
//          ::close
#include <unistd.h>

//  Here:   std::remove
#include <stdio.h>

//  Here: ioctl -- awfull function what do everything.
#include <sys/ioctl.h>



using namespace vposix;


//=======================================================================================
int Files::open( cstr name, int flags )
{
    if ( do_trace() ) vtrace( "V::open(", name, flags, ")" );

    return Core::linux_call( ::open64, "::open64", name.c_str(), flags );
}
//=======================================================================================
int Files::open_mode( cstr name, int flags, mode_t mode )
{
    if ( do_trace() ) vtrace( "V::open_mode(", name, flags, mode, ")" );

    return Core::linux_call( ::open64, "::open64(mode)", name.c_str(), flags, mode );
}
//=======================================================================================
ssize_t Files::_write( int fd, const void *buf, size_t count )
{
    if ( do_trace() ) vtrace( "V::write(", fd, buf, count, ")" );

    return Core::linux_call( ::write, "::write", fd, buf, count );
}
//=======================================================================================
ssize_t Files::write( int fd, Files::cstr buf )
{
    return _write( fd, buf.c_str(), buf.size() );
}
//=======================================================================================
ssize_t Files::read( int fd, void *buf, size_t count )
{
    auto res = read_or_err( fd, buf, count );
    assert( res >= 0 );
    return res;
}
//=======================================================================================
ssize_t Files::read_or_err(int fd, void *buf, size_t count)
{
    if ( do_trace() ) vtrace( "V::read(", fd, buf, count, ")" );

    return Core::linux_call_or_err( ::read, fd, buf, count );
}
//=======================================================================================
int Files::_remove(  const char* pathname )
{
    if ( do_trace() ) vtrace << "V::remove(" << pathname << ");";

    return Core::linux_call( std::remove, "std::remove", pathname );
}
//=======================================================================================
void Files::remove( cstr pathname )
{
    auto res = _remove( pathname.c_str() );
    assert( res == 0 );
}
//=======================================================================================
void Files::close( int fd )
{
    if ( do_trace() ) vtrace << "V::close(" << fd << ");";

    auto flags = _fcntl_get_flags( fd );

    if ( flags & O_NONBLOCK )
    {
        flags &= ~O_NONBLOCK;
        _fcntl_set_flags( fd, flags );
    }

    auto res = Core::linux_call( ::close, "::close", fd );
    assert( res == 0 );
}
//=======================================================================================
void Files::_ioctl(int fd, unsigned long ctl)
{
    auto res = Core::linux_call( ::ioctl, "::ioctl", fd, ctl );
    assert( res == 0 );
}
//=======================================================================================
int Files::_ioctl_or_err( int fd, unsigned long ctl )
{
    return Core::linux_call_or_err( ::ioctl, fd, ctl );
}
//=======================================================================================
void Files::set_tio_EXCL(int fd)
{
    #ifdef TIOCEXCL
        _ioctl( fd, TIOCEXCL );
    #endif
}
//=======================================================================================
void Files::set_tio_soft_not_EXCL( int fd )
{
    #ifdef TIOCNXCL
        _ioctl_or_err( fd, TIOCNXCL );
    #endif
}
//=======================================================================================

//=======================================================================================
//      FCNTL
//=======================================================================================
//http://www.opennet.ru/man.shtml?topic=fcntl&category=2&russian=2
//=======================================================================================
long Files::_fcntl_get_flags( int fd )
{
    return Core::linux_call( ::fcntl, "::fcntl", fd, F_GETFL );
}
//=======================================================================================
void Files::_fcntl_set_flags( int fd, long flags )
{
    auto res = Core::linux_call( ::fcntl, "::fcntl", fd, F_SETFL, flags );
    assert( res == 0 );
}
//=======================================================================================
//      FCNTL
//=======================================================================================


//=======================================================================================
FD::FD( int fd, const FD::close_func &cf )
    : _fd( fd )
    , _close( cf )
{}
//=======================================================================================
FD::FD( FD && rhs )
    : _fd( std::move(rhs._fd) )
    , _close( std::move(rhs._close) )
{
    rhs._fd = -1;
    rhs._close = nullptr;
}
//=======================================================================================
FD& FD::operator = ( FD && rhs )
{
    if ( this != &rhs )
    {
        close();
        std::swap( _fd, rhs._fd );
        std::swap( _close, rhs._close );
    }
    return *this;
}
//=======================================================================================
FD::~FD()
{
    close();
}
//=======================================================================================
bool FD::valid() const
{
    return _fd >= 0;
}
//=======================================================================================
void FD::close()
{
    if ( valid() )
        _close( _fd );

    _close = nullptr;
    _fd = -1;
}
//=======================================================================================
int FD::raw() const
{
    return _fd;
}
//=======================================================================================
