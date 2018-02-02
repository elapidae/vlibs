#ifndef VSTRING_H
#define VSTRING_H

#include "vstringref.h"


//=======================================================================================
//=======================================================================================


//=======================================================================================
//      VString
//=======================================================================================
class VString : public std::string, public VStringRef
{
public:
    VString();
    VString( const std::string& str );
    VString( const std::string& str, size_t pos, size_t len = npos );
    VString( const char* s );
    VString( const char* s, size_t n );
    VString( size_t n, char c );

    template <typename InputIterator>
    VString( InputIterator first, InputIterator last );

    VString( std::initializer_list<char> il );
    VString( std::string&& str ) noexcept;


    VString( VString && ) = default;
    VString( const VString & ) = default;
    VString & operator = ( VString && ) = default;
    VString & operator = ( const VString & ) = default;
};
//=======================================================================================
//      VString
//=======================================================================================



//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
template<typename InputIterator>
VString::VString( InputIterator first, InputIterator last )
    : std::string( first, last )
    , VStringRef(this)
{}
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================




#endif // VSTRING_H
