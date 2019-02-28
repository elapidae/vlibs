/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


#include "vimage_qt.h"

#include "vlog_pretty.h"
#include "verror.h"
#include <assert.h>

//=======================================================================================
QImage::Format VImage_Qt::format_to_QImageFormat(VImage::Format f)
{
    switch( f )
    {
    case Format::Invalid: return QImage::Format_Invalid;
    case Format::Gray_8:  return QImage::Format_Grayscale8;
    case Format::RGB_888: return QImage::Format_RGB888;
    case Format::BGR_888:
        throw verror << "Format GBR not supported by QImage... "
                        "May be use QImage::invertPixels(InvertMode)";
    }
    throw verror << "Unknown vimage format:" << int(f);
}
//=======================================================================================
VImage::Format VImage_Qt::qImageFormat_to_format(QImage::Format f)
{
    switch( f )
    {
    case QImage::Format_Invalid:    return Format::Invalid;
    case QImage::Format_Grayscale8: return Format::Gray_8;
    case QImage::Format_RGB888:     return Format::RGB_888;
    default: break;
    }
    throw verror << "Unknown vimage format:" << f;
}
//=======================================================================================


//=======================================================================================
QImage VImage_Qt::convert( const VImage &other )
{
    return QImage( other.data(),
                   other.width(),
                   other.height(),
                   other.bytes_per_line(),
                   format_to_QImageFormat(other.format()) );
}
//=======================================================================================


//=======================================================================================
VImage_Qt::VImage_Qt( const QImage *img )
    : _img( img )
{}
//=======================================================================================
VImage::Format VImage_Qt::format() const
{
    return qImageFormat_to_format( _img->format() );
}
//=======================================================================================
int VImage_Qt::width() const
{
    return _img->width();
}
//=======================================================================================
int VImage_Qt::height() const
{
    return _img->height();
}
//=======================================================================================
int VImage_Qt::bytes_per_line() const
{
    return _img->bytesPerLine();
}
//=======================================================================================
const VImage::data_t *VImage_Qt::data() const
{
    return _img->bits();
}
//=======================================================================================
const VImage::data_t *VImage_Qt::line(int row) const
{
    assert( row < height() );
    return _img->scanLine( row );
}
//=======================================================================================
int VImage_Qt::data_size() const
{
    return static_cast<int>( _img->sizeInBytes() );
}
//=======================================================================================


