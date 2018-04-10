#include "vimage.h"

#include <assert.h>

//=======================================================================================
std::string VImage::format_to_string( VImage::Format f )
{
    switch (f)
    {
    case Format::Invalid:   return "Invalid";
    case Format::Gray8:     return "Gray8";
    case Format::RGB888:    return "RGB888";
    }
    throw std::logic_error("Unknown image format.");
}
//=======================================================================================
VImage::Format VImage::string_to_format( const std::string &s )
{
    if ( s == "Gray8"  ) return Format::Gray8;
    if ( s == "RGB888" ) return Format::RGB888;

    return Format::Invalid;
}
//=======================================================================================
const VImage::data_t *VImage::line( int row ) const
{
    assert( row < height() );
    return is_valid() ? data() + row * bytes_per_line() : nullptr;
}
//=======================================================================================
int VImage::data_size() const
{
    return bytes_per_line() * height();
}
//=======================================================================================
