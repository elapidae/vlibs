#include "vimage.h"

#include <stdexcept>
#include <assert.h>

//=======================================================================================
std::string VImage::format_to_string( VImage::Format f )
{
    switch (f)
    {
    case Format::Invalid:   return "Invalid";
    case Format::Gray_8:    return "Gray_8";
    case Format::RGB_888:   return "RGB_888";
    case Format::BGR_888:   return "BGR_888";
    }
    throw std::logic_error("Unknown image format.");
}
//=======================================================================================
VImage::Format VImage::string_to_format( const std::string &s )
{
    if ( s == "Gray_8"  ) return Format::Gray_8;
    if ( s == "RGB_888" ) return Format::RGB_888;
    if ( s == "BGR_888" ) return Format::BGR_888;

    return Format::Invalid;
}
//=======================================================================================
const VImage::data_t *VImage::line( int row ) const
{
    if ( row >= height() ) throw std::out_of_range("VImage::line: row >= height()");
    return data() + row * bytes_per_line();
}
//=======================================================================================
int VImage::data_size() const
{
    return bytes_per_line() * height();
}
//=======================================================================================
uint VImage::data_usize() const
{
    if ( data_size() < 0 )
        throw std::logic_error( "VImage::data_size() < 0" );

    return static_cast<uint>( data_size() );
}
//=======================================================================================
