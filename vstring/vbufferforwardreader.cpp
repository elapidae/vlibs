#include "vbufferforwardreader.h"

#include <assert.h>

using namespace std;



//=======================================================================================
VBufferForwardReader::VBufferForwardReader( const std::string &buf )
    : VBufferForwardReader( buf.data(), buf.size() )
{}
//=======================================================================================
VBufferForwardReader::VBufferForwardReader( const char *buf, size_t size )
    : _buffer   ( buf  )
    , _remained ( size )
{}
//=======================================================================================
std::string VBufferForwardReader::take_string( size_t sz )
{
    if ( _remained < sz )
        throw std::out_of_range( "VBufferForwardReader::take_str(): not enouth data" );

    auto res = std::string( _buffer, _buffer + sz );

    _buffer   += sz;
    _remained -= sz;

    return res;
}
//=======================================================================================
string VBufferForwardReader::show_byte_string() const
{
    auto sz = show_u8();
    if ( _remained - 1 < sz )
        throw std::out_of_range( "VBufferForwardReader::show_byte_string()." );

    return { _buffer + 1, sz };
}
//=======================================================================================
string VBufferForwardReader::show_word_string_LE() const
{
    auto sz = show_u16_LE();
    if ( _remained - 2 < sz )
        throw std::out_of_range( "VBufferForwardReader::show_word_string()." );

    return { _buffer + 2, sz };
}
//=======================================================================================
string VBufferForwardReader::show_dword_string_LE() const
{
    auto sz = show_u32_LE();
    if ( _remained - 4 < sz )
        throw std::out_of_range( "VBufferForwardReader::show_dword_string()." );

    return { _buffer + 4, sz };
}
//=======================================================================================
std::string VBufferForwardReader::take_byte_string()
{
    auto sz = take_u8();
    return take_string( sz );
}
//=======================================================================================
string VBufferForwardReader::take_word_string_LE()
{
    auto sz = take_u16_LE();
    return take_string( sz );
}
//=======================================================================================
string VBufferForwardReader::take_dword_string_LE()
{
    auto sz = take_u32_LE();
    return take_string( sz );
}
//=======================================================================================
size_t VBufferForwardReader::remained() const
{
    return _remained;
}
//=======================================================================================
bool VBufferForwardReader::finished() const
{
    return remained() == 0;
}
//=======================================================================================
std::string VBufferForwardReader::show_string( size_t sz ) const
{
    assert( sz <= size_t(remained()) );
    return string( _buffer, sz );
}
//=======================================================================================
