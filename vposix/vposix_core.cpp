#include "vposix_core.h"

#include <vector>
#include <stdexcept>
#include <string.h>

#include "vposix_alloca.h"


using namespace vposix;

//=======================================================================================
//
//  http://man7.org/linux/man-pages/man3/strerror.3.html
//
std::string vposix::Core::str_error( int err )
{
    //  TS версия.
    constexpr auto buf_size = 1024;
    auto buf = Alloca::allocate<char>( buf_size );
    return  strerror_r( err, buf, buf_size );
}
//=======================================================================================
[[noreturn]]
void vposix::Core::throw_err( int err, const std::string& who )
{
    throw verror( "Linux error in '", who,"': [",
                  err, "]: '", str_error(err), "'" );
}
//=======================================================================================

//=======================================================================================
Errno::Errno()
    : _err( errno )
{}
//=======================================================================================
int Errno::has() const
{
    return _err != 0;
}
//=======================================================================================
int Errno::code() const
{
    return _err;
}
//=======================================================================================
std::string Errno::str() const
{
    return Core::str_error( _err );
}
//=======================================================================================
[[noreturn]] void Errno::throw_verror() const
{
    throw verror( str() );
}
//=======================================================================================
bool Errno::eagain() const
{
    return _err == EAGAIN;
}
//=======================================================================================
bool Errno::resource_unavailable_try_again() const
{
    return eagain();
}
//=======================================================================================
