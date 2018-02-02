#include "vstring.h"

//=======================================================================================
VString::VString()
    : VStringRef(this)
{}
//=======================================================================================
VString::VString(const std::string &str)
    : std::string( str )
    , VStringRef(this)
{}
//=======================================================================================
VString::VString(const std::string &str, size_t pos, size_t len)
    : std::string( str, pos, len )
    , VStringRef(this)
{}
//=======================================================================================
VString::VString(const char *s)
    : std::string( s )
    , VStringRef(this)
{}
//=======================================================================================
VString::VString(const char *s, size_t n)
    : std::string( s, n )
    , VStringRef(this)
{}
//=======================================================================================
VString::VString(size_t n, char c)
    : std::string( n, c )
    , VStringRef(this)
{}
//=======================================================================================
VString::VString(std::initializer_list<char> il)
    : std::string( il )
    , VStringRef(this)
{}
//=======================================================================================
VString::VString(std::string &&str) noexcept
    : std::string( std::move(str) )
    , VStringRef(this)
{}
//=======================================================================================
