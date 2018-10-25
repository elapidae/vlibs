#include "vposix_errno.h"

#include <vector>
#include <stdexcept>
#include <string.h>

using namespace vposix;

//=======================================================================================
//  http://man7.org/linux/man-pages/man3/strerror.3.html
std::string Errno::str_error( int err )
{
    //  TS версия.
    constexpr auto buf_size = 1024;
    std::vector<char> buf( buf_size );
    return  strerror_r( err, buf.data(), buf_size );
}
//=======================================================================================
//std::string Errno::str_error() const
//{
//    return str_error( err_code );
//}
////=======================================================================================
//Errno::Errno( int res )
//    : err_code( res == -1 ? errno : 0 )
//{
//    if (err_code)
//        throw std::runtime_error( str_error(err_code) );
//}
////=======================================================================================
//vposix::Errno::operator int() const
//{
//    return err_code;
//}
//=======================================================================================
