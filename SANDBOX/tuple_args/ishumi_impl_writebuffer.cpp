#include "ishumi_impl_writebuffer.h"

using namespace ishumi::impl;



//=======================================================================================
WriteBuffer::WriteBuffer( size_t reserve )
{
    if (reserve)
        _buf.reserve( reserve );
}
//=======================================================================================
void WriteBuffer::write( const std::string &val )
{
    write_size( val.size() );
    _buf.append( val );
}
//=======================================================================================
void WriteBuffer::write_size( size_t big_sz )
{
    if ( big_sz > std::numeric_limits<uint32_t>::max() )
        throw std::overflow_error( "Size is too big... " );

    uint32_t sz = static_cast<uint32_t>( big_sz );
    do
    {
        uint8_t cur = sz & 0x7F;
        sz >>= 7;
        if ( sz == 0 ) cur |= 0x80;
        _buf.append_LE<uint8_t>( cur );
    } while( sz != 0 );
}
//=======================================================================================
