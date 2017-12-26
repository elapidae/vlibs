#include "c_errno.h"

#include <errno.h>
#include <string.h>

#include "vlogger.h"


//=======================================================================================
C_ErrNo::C_ErrNo( int res_from_c_style_funcs )
{
    if ( res_from_c_style_funcs != -1 )
        return;

    _err = errno;

    char buf[256];
    bzero( buf, 256 );
    auto res_second = strerror_r( _err, buf, 255 );

    if (res_second != 0)
    {
        vwarning(vlog("Bad call of strerror_r, full horror..."));
        exit(42);
    }
    _msg = buf;
}
//=======================================================================================
C_ErrNo::operator bool() const
{
    return has();
}
//=======================================================================================
bool C_ErrNo::has() const
{
    return _err != 0;
}
//=======================================================================================
int C_ErrNo::err_code() const
{
    return _err;
}
//=======================================================================================
const std::string &C_ErrNo::text() const
{
    return _msg;
}
//=======================================================================================
