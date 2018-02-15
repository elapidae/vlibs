#include "vbufferforwardreader.h"

VBufferForwardReader::VBufferForwardReader( const std::string &buf )
    : VBufferForwardReader( buf.data(), buf.size() )
{}

VBufferForwardReader::VBufferForwardReader( const char *buf, size_t size )
    : _buffer   ( buf  )
    , _remained ( size )
{}

std::string VBufferForwardReader::take_str( size_t sz )
{
    if ( _remained < sz )
        throw std::out_of_range( "VBufferForwardReader::take_str(): not enouth data" );

    auto res = std::string( _buffer, _buffer + sz );

    _buffer   += sz;
    _remained -= sz;

    return res;
}

std::string VBufferForwardReader::take_byte_string()
{
    auto sz = take_u8();
    return take_str( sz );
}

int VBufferForwardReader::remained() const
{
    return _remained;
}

bool VBufferForwardReader::finished() const
{
    return remained() == 0;
}
