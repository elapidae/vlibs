#include "vqimageimpl.h"

#include "vlog_pretty.h"

//=======================================================================================
VQImageImpl::VQImageImpl( QImage &&img_ )
    : img( std::move(img_) )
{
    detach();
}
//=======================================================================================
VQImageImpl::VQImageImpl( const QImage &img_ )
    : img( img_ )
{
    detach();
}
//=======================================================================================
bool VQImageImpl::is_valid() const
{
    return img.isNull();
}
//=======================================================================================
VImage::Format VQImageImpl::format() const
{
    switch ( img.format() )
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
void VQImageImpl::detach()
{
    if ( !img.isDetached() )
        img.detach();
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
