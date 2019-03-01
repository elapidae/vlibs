#include "serialization/serialization_decoder.h"

using namespace serialization;

//=======================================================================================
AbstractDecoder::DecodeError::DecodeError( const std::string &msg )
    : std::runtime_error::runtime_error( msg )
{}
//=======================================================================================


//=======================================================================================
AbstractDecoder::AbstractDecoder(hash_type hname, hash_type hfull)
    : _hname( hname )
    , _hfull( hfull )
{}
//=======================================================================================
hash_type AbstractDecoder::hash_name() const
{
    return _hname;
}
//=======================================================================================
hash_type AbstractDecoder::hash_full() const
{
    return _hfull;
}
//=======================================================================================


//=======================================================================================
void AbstractDecoder::process( const VString &buf )
{
    ReadBuffer rbuf( buf );
    process( &rbuf );
    if ( !rbuf.finished() )
        throw DecodeError( "Buffer is not finished." );
}
//=======================================================================================
