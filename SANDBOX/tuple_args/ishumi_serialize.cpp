#include "ishumi_serialize.h"

#include "vlog_pretty.h"
#include <assert.h>

//=======================================================================================
std::string ishumi::extract_serialize_typename( const std::string &pretty_func )
{
    static constexpr const char begin_sign[] = "ishumi::Serialize<";
    static constexpr const char end_sign[]   = ">::id()";

    auto b = pretty_func.find(begin_sign) + sizeof(begin_sign) - 1;
    auto e = pretty_func.find(end_sign);
    assert( e > b );
    return pretty_func.substr( b, e - b ) + " "; // Пробел -- чтобы не забывали.
}
//static std::__cxx11::string ishumi::Serialize<PV>::id()
//=======================================================================================
