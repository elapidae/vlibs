#include "serialization/serialization_readbuffer.h"
#include "serialization/serialization_decoder.h"

using namespace serialization;


//=======================================================================================
ReadBuffer::ReadBuffer( const VString &buf )
    : _buf  ( buf )
    , _view ( _buf.forward_view() )
{}
//=======================================================================================
bool ReadBuffer::finished() const
{
    return _view.finished();
}
//=======================================================================================
uint32_t ReadBuffer::read_size()
{
    uint32_t res        = 0;
    int      shift      = 0;
    bool     stop       = false;
    int      pos_watch  = 0;

    do
    {
        if ( ++pos_watch > 5 )
            throw AbstractDecoder::DecodeError( "Size out" );

        uint32_t cur = _view.take_u8();
        stop = cur & 0x80;
        cur &= 0x7F;
        cur <<= shift;
        shift += 7;
        res |= cur;
    }
    while( !stop );

    return res;

}
//=======================================================================================
