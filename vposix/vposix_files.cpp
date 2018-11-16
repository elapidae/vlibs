#include "vposix_files.h"

#include "vlog_pretty.h"
#include <assert.h>

//  Here: ::open
#include <fcntl.h>

//  Here: ::write
#include <unistd.h>

//  Here: std::remove
#include <stdio.h>

#include "vposix_core.h"


using namespace vposix;



//=======================================================================================
int Files::open( cstr name, int flags )
{
    if ( do_files_trace() ) vtrace( "V::open(", name, flags, ")" );

    return Core::linux_call( ::open64, name.c_str(), flags );
}
//=======================================================================================
int Files::open_mode( cstr name, int flags, mode_t mode )
{
    if ( do_files_trace() ) vtrace( "V::open_mode(", name, flags, mode, ")" );

    return Core::linux_call( ::open64, name.c_str(), flags, mode );
}
//=======================================================================================
ssize_t Files::_write( int fd, const void *buf, size_t count )
{
    if ( do_files_trace() ) vtrace( "V::write(", fd, buf, count, ")" );

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
    auto res = read_or_err( fd, buf, count );
    assert( res >= 0 );
    return res;
}
//=======================================================================================
ssize_t Files::read_or_err(int fd, void *buf, size_t count)
{
    if ( do_files_trace() ) vtrace( "V::read(", fd, buf, count, ")" );

    return Core::linux_call_or_err( ::read, fd, buf, count );
}
//=======================================================================================
int Files::_remove(  const char* pathname )
{
    if ( do_files_trace() ) vtrace << "V::remove(" << pathname << ");";

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
    if ( do_files_trace() ) vtrace << "V::close(" << fd << ");";

    auto res = Core::linux_call( ::close, fd );
    assert( res == 0 );
}
//=======================================================================================
