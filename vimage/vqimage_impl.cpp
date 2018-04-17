#include "vqimage_impl.h"

#include "vlog_pretty.h"

//=======================================================================================
QImage::Format VQImage_Impl::format_to_QImageFormat( VImage::Format f )
{
    switch( f )
    {
    case Format::Invalid: return QImage::Format_Invalid;
    case Format::Gray8:   return QImage::Format_Grayscale8;
    case Format::RGB888:  return QImage::Format_RGB888;
    case Format::BGR888:
        throw VLogError( vfatal << "Format GBR not supported by QImage... "
                                   "May be use QImage::invertPixels(InvertMode)" );
    }
    throw VLogError( vfatal << "Unknown vimage format:" << int(f) );
}
//=======================================================================================
VImage::Format VQImage_Impl::qImageFormat_to_format( QImage::Format f )
{
    switch( f )
    {
    case QImage::Format_Invalid:    return Format::Invalid;
    case QImage::Format_Grayscale8: return Format::Gray8;
    case QImage::Format_RGB888:     return Format::RGB888;
    default: break;
    }
    throw VLogError( vfatal << "Unknown vimage format:" << f );
}
//=======================================================================================
VQImage_Impl VQImage_Impl::copy_from( const VImage &src )
{
    QImage img( src.data(),
                src.width(),
                src.height(),
                src.bytes_per_line(),
                format_to_QImageFormat(src.format()) );

    return std::move( img );
}
//=======================================================================================
VQImage_Impl::VQImage_Impl( QImage &&img_ )
    : img( std::move(img_) )
{
    detach();
}
//=======================================================================================
VQImage_Impl::VQImage_Impl( const QImage &img_ )
    : img( img_ )
{
    detach();
}
//=======================================================================================
bool VQImage_Impl::is_valid() const
{
    return !img.isNull();
}
//=======================================================================================
VImage::Format VQImage_Impl::format() const
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
int VQImage_Impl::width() const
{
    return img.width();
}
//=======================================================================================
int VQImage_Impl::height() const
{
    return img.height();
}
//=======================================================================================
int VQImage_Impl::bytes_per_line() const
{
    return img.bytesPerLine();
}
//=======================================================================================
const VImage::data_t * VQImage_Impl::data() const
{
    return img.bits();
}
//=======================================================================================
const VImage::data_t *VQImage_Impl::line( int row ) const
{
    return img.scanLine( row );
}
//=======================================================================================
void VQImage_Impl::detach()
{
    if ( !img.isDetached() )
        img.detach();
}
//=======================================================================================
QImage &VQImage_Impl::image()
{
    return img;
}
//=======================================================================================
const QImage &VQImage_Impl::image() const
{
    return img;
}
//=======================================================================================



//=======================================================================================
VQImage_Ref_Impl::VQImage_Ref_Impl( const QImage *ptr )
    : img( ptr )
{}
//=======================================================================================
bool VQImage_Ref_Impl::is_valid() const
{
    return !img->isNull();
}
//=======================================================================================
VImage::Format VQImage_Ref_Impl::format() const
{
    return VQImage_Impl::qImageFormat_to_format( img->format() );
}
//=======================================================================================
int VQImage_Ref_Impl::width() const
{
    return img->width();
}
//=======================================================================================
int VQImage_Ref_Impl::height() const
{
    return img->height();
}
//=======================================================================================
int VQImage_Ref_Impl::bytes_per_line() const
{
    return img->bytesPerLine();
}
//=======================================================================================
const VImage::data_t *VQImage_Ref_Impl::data() const
{
    return img->bits();
}
//=======================================================================================
const VImage::data_t *VQImage_Ref_Impl::line(int row) const
{
    return img->scanLine( row );
}
//=======================================================================================
void VQImage_Ref_Impl::detach()
{}
//=======================================================================================
const QImage &VQImage_Ref_Impl::image() const
{
    return *img;
}
//=======================================================================================
