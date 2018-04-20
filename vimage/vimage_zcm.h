#ifndef VIMAGE_ZCM_H
#define VIMAGE_ZCM_H


#include "vimage.h"

#include "basler_zcm.h"


template<typename AnyZcmImage>
class VImage_ZCM final : public VImage
{
public:

    static AnyZcmImage convert( const VImage &other );

    VImage_ZCM( const AnyZcmImage &img );

    virtual Format format()         const override;

    virtual int width()             const override;
    virtual int height()            const override;
    virtual int bytes_per_line()    const override;

    virtual const data_t* data()    const override;

private:
    const AnyZcmImage & _img;
};



//=======================================================================================
template<typename AnyZcmImage>
AnyZcmImage VImage_ZCM<AnyZcmImage>::convert( const VImage &other )
{
    AnyZcmImage res;

    res.width  = other.width();
    res.height = other.height();
    res.bytes_per_line = other.bytes_per_line();
    res.format = format_to_string( other.format() );

    res.data_size = other.data_size();
    res.data.resize( static_cast<size_t>(other.data_size()) );
    std::copy( other.data(), other.data() + other.data_size(), res.data.begin() );

    return res;
}
//=======================================================================================


//=======================================================================================
template<typename AnyZcmImage>
VImage_ZCM<AnyZcmImage>::VImage_ZCM( const AnyZcmImage & img )
    : _img( img )
{}
//=======================================================================================
template<typename AnyZcmImage>
VImage::Format VImage_ZCM<AnyZcmImage>::format() const
{
    return VImage::string_to_format( _img.format );
}
//=======================================================================================
template<typename AnyZcmImage>
int VImage_ZCM<AnyZcmImage>::width() const
{
    return _img.width;
}
//=======================================================================================
template<typename AnyZcmImage>
int VImage_ZCM<AnyZcmImage>::height() const
{
    return _img.height;
}
//=======================================================================================
template<typename AnyZcmImage>
int VImage_ZCM<AnyZcmImage>::bytes_per_line() const
{
    return _img.bytes_per_line;
}
//=======================================================================================
template<typename AnyZcmImage>
const VImage::data_t *VImage_ZCM<AnyZcmImage>::data() const
{
    return _img.data.data();
}
//=======================================================================================



#endif // VIMAGE_ZCM_H
