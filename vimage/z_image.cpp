#include "z_image.h"

//=======================================================================================
Z_Image Z_Image::copy_from( const VImage &src )
{
    ZCM_Image res;

    res.width           = src.width();
    res.height          = src.height();
    res.bytes_per_line  = src.bytes_per_line();

    res.format          = format_to_string( src.format() );

    res.data.resize( static_cast<uint>(src.data_size()) );
    std::copy( src.data(), src.data() + src.data_size(), res.data.begin() );
    res.data_size = src.data_size();

    return std::move( res );
}
//=======================================================================================
Z_Image::Z_Image()
{
    img.width           = 0;
    img.height          = 0;
    img.bytes_per_line  = 0;
    img.data_size       = 0;
    img.format          = format_to_string( Format::Invalid );
}
//=======================================================================================
Z_Image::Z_Image( ZCM_Image &&i )
    : img( std::move(i) )
{}
//=======================================================================================
Z_Image::Z_Image( const ZCM_Image &i )
    : img( i )
{}
//=======================================================================================
bool Z_Image::is_valid() const
{
    return format() != Format::Invalid;
}
//=======================================================================================
VImage::Format Z_Image::format() const
{
    return string_to_format( img.format );
}
//=======================================================================================
int Z_Image::width() const
{
    return img.width;
}
//=======================================================================================
int Z_Image::height() const
{
    return img.height;
}
//=======================================================================================
int Z_Image::bytes_per_line() const
{
    return img.bytes_per_line;
}
//=======================================================================================
const VImage::data_t *Z_Image::data() const
{
    return img.data.data();
}
//=======================================================================================
void Z_Image::detach()
{}
//=======================================================================================
const ZCM_Image &Z_Image::zcm_image() const
{
    return img;
}
//=======================================================================================
