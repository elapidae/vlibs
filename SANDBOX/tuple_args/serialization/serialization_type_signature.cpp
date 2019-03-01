#include "serialization_type_signature.h"

#include <assert.h>

//=======================================================================================
//  Cut from __PRETTY_FUNCTION__ signature type name.
std::string serialization::_serializable_type_name( const std::string& pretty_func )
{
    //  These lines may change from compiler to compiler.
    //  Need to use #ifdef macros for various compilers.
    static constexpr const char
            begin_sign[] = "serialization::serializable_type_name() [with T = ";

    static constexpr const char end_sign[]   = ";";

    auto b = pretty_func.find(begin_sign) + sizeof(begin_sign) - 1;
    auto e = pretty_func.find(end_sign);
    assert( e > b && e != std::string::npos );
    return pretty_func.substr( b, e - b );
}

//=======================================================================================
