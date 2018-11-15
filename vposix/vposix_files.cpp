#include "vposix_files.h"

#include "vlog_pretty.h"
#include <assert.h>

//  Here: ::open
#include <fcntl.h>

//  Here: ::write
#include <unistd.h>

//  Here: std::remove
#include <stdio.h>


using namespace vposix;



//=======================================================================================
int Files::open( cstr name, int flags )
{
    //return Core::linux_call<int>( ::open64, name.c_str(), flags );
    return Core::linux_call( ::open64, name.c_str(), flags );
}
//=======================================================================================
int Files::open_mode( cstr name, int flags, mode_t mode )
{
    //return Core::linux_call<int>( ::open64, name.c_str(), flags, mode );
    return Core::linux_call( ::open64, name.c_str(), flags, mode );
}
//=======================================================================================
ssize_t Files::_write( int fd, const void *buf, size_t count )
{
    //return Core::linux_call<ssize_t>( ::write, fd, buf, count );
    return Core::linux_call( ::write, fd, buf, count );
}
//=======================================================================================
ssize_t Files::write( int fd, Files::cstr buf )
{
    return _write( fd, buf.c_str(), buf.size() );
}
//=======================================================================================
ssize_t Files::read( int fd, void *buf, size_t count )
{
    //return Core::linux_call<ssize_t>( ::read, fd, buf, count );
    return Core::linux_call( ::read, fd, buf, count );
}
//=======================================================================================
ssize_t Files::read_or_err(int fd, void *buf, size_t count)
{
    return Core::linux_call_or_err( ::read, fd, buf, count );
}
//=======================================================================================
int Files::_remove(  const char* pathname )
{
    //return Core::linux_call<int>( std::remove, pathname );
    return Core::linux_call( std::remove, pathname );
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
    if (trace) vtrace << "V::close(" << fd << ");";

    //auto res = Core::linux_call<int>( ::close, fd );
    auto res = Core::linux_call( ::close, fd );
    assert( res == 0 );
}
//=======================================================================================
