#include "vposix_files.h"

//  Here: ::open
#include <fcntl.h>

//  Here: ::write
#include <unistd.h>

//  Here: std::remove
#include <stdio.h>


using namespace vposix;


//=======================================================================================
int Files::open(Files::cstr name, int flags)
{
    return open64( name.c_str(), flags );
}
//=======================================================================================
int Files::open_mode(Files::cstr name, int flags, mode_t mode)
{
    return open64( name.c_str(), flags, mode );
}
//=======================================================================================
ssize_t Files::write_raw( int fd, const void *buf, size_t count )
{
    return ::write( fd, buf, count );
}
//=======================================================================================
ssize_t Files::write( int fd, Files::cstr buf )
{
    return write_raw( fd, buf.c_str(), buf.size() );
}
//=======================================================================================
int Files::remove_raw(  const char *pathname )
{
    return std::remove( pathname );
}
//=======================================================================================
int Files::remove( cstr pathname )
{
    return remove_raw( pathname.c_str() );
}
//=======================================================================================
