#include "serialization/serialization_writebuffer.h"

//#include "vlog_pretty.h"

using namespace serialization;


//=======================================================================================
void WriteBuffer::add_to_reserve( size_t reserve )
{
    _reserve += reserve;
    //vdeb << "reserve: +" << reserve << ", now reserve: " << _reserve;
    _buf.reserve( _reserve );
}
//=======================================================================================
void WriteBuffer::write( const std::string &val )
{
    auto real_size = size_of_size(val.size()) + val.size();

    if ( real_size > min_size<std::string>() )
        add_to_reserve( real_size - min_size<std::string>() );

    write_size( val.size() );
    _buf.append( val );
}
//=======================================================================================
void WriteBuffer::write( bool val )
{
    write( _bool_to_byte(val) );
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
        if ( sz == 0 ) cur |= 0x80;         // последний байт маркируется старшим битом.
        _buf.append_LE<uint8_t>( cur );
    }
    while( sz != 0 );
}
//=======================================================================================
void WriteBuffer::write_raw( const std::string &val )
{
    _buf.append( val );
}
//=======================================================================================
int WriteBuffer::size() const
{
    if ( _buf.size() > std::numeric_limits<int>::max() )
        throw std::out_of_range( "Size of buffer is too big..." );

    return static_cast<int>( _buf.size() );
}
//=======================================================================================
const VString &WriteBuffer::result() const
{
    return _buf;
}
//=======================================================================================
