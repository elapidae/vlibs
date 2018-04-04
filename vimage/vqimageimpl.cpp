#include "vqimageimpl.h"

#include "vlog_pretty.h"

//=======================================================================================
VImage::Impl_Ptr VQImageImpl::make( QImage &&img )
{
    return std::make_shared<VQImageImpl>( std::move(img) );
}
//=======================================================================================
VImage::Impl_Ptr VQImageImpl::make( const QImage &img )
{
    return std::make_shared<VQImageImpl>( img );
}
//=======================================================================================
VQImageImpl::VQImageImpl( QImage &&img_ )
    : img( std::move(img_) )
{
    img.detach();
}
//=======================================================================================
VQImageImpl::VQImageImpl( const QImage &img_ )
    : img( img_ )
{
    img.detach();
}
//=======================================================================================
VImage::Format VQImageImpl::format() const
{
    switch (img.format())
    {
    case QImage::Format_Invalid:    return VImage::Format::Invalid;
    case QImage::Format_Grayscale8: return VImage::Format::Gray8;
    case QImage::Format_RGB888:     return VImage::Format::RGB888;
    //case QImage::Format_: return VImage::Format::;

    default: break;
    }
    throw VLogError( vfatal << "Unknown type of QImage:" << img.format() );
}
//=======================================================================================
int VQImageImpl::width() const
{
    return img.width();
}
//=======================================================================================
int VQImageImpl::height() const
{
    return img.height();
}
//=======================================================================================
int VQImageImpl::bytes_per_line() const
{
    return img.bytesPerLine();
}
//=======================================================================================
const VImage::data_t * VQImageImpl::data() const
{
    return img.bits();
}
//=======================================================================================
const VImage::data_t *VQImageImpl::line( int row ) const
{
    return img.scanLine( row );
}
//=======================================================================================
VImage::Impl_Ptr VQImageImpl::copy()
{
    return make( img );
}
//=======================================================================================
QImage &VQImageImpl::image()
{
    return img;
}
//=======================================================================================
const QImage &VQImageImpl::image() const
{
    return img;
}
//=======================================================================================
