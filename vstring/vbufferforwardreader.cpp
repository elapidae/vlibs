#include "vbufferforwardreader.h"

VBufferForwardReader::VBufferForwardReader( const std::string &buf )
    : _buffer   ( buf.data() )
    , _remained ( buf.size() )
{}

VBufferForwardReader::VBufferForwardReader( const char *buf, size_t size )
    : _buffer   ( buf )
    , _remained ( size )
{}

std::string VBufferForwardReader::take_str( size_t sz )
{
    if ( _remained < int(sz) )
        throw std::out_of_range( "VBufferForwardReader::take_str(): not enouth data" );
}

int VBufferForwardReader::remained() const
{
    return _remained;
}
