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


#include "vimage_opencv.h"


//=======================================================================================
cv::Mat VImage_OpenCV::convert( const VImage &other )
{
    int cv_color_format_flag = -1;
    int cv_data_size_type = CV_8U;

    switch ( other.format() )
    {
        case VImage::Format::Gray_8:
            cv_data_size_type = CV_8U;;
            break;
        case VImage::Format::BGR_888:
            cv_data_size_type = CV_8UC3;
            break;
        case VImage::Format::RGB_888:
            cv_data_size_type = CV_8UC3;
            cv_color_format_flag = cv::COLOR_RGB2BGR;
            break;
        default:
            throw std::logic_error( "Invalid format can" );
    }

    cv::Mat result = cv::Mat( other.height(),     // rows
                              other.width(),      // cols
                              cv_data_size_type,  // type (CV_DEPTH MACROS)
                              const_cast<void*>(static_cast<const void*>(other.data())),
                              static_cast<size_t>(other.bytes_per_line()) ).clone();

    if ( cv_color_format_flag > 0 )
    {
        cv::cvtColor(result, result, cv_color_format_flag);
    }

    return result;
}
//=======================================================================================
static VImage::Format bgr24_or_gray8( int channels_count )
{
    if ( channels_count == 3 ) return VImage::Format::BGR_888;
    if ( channels_count == 1 ) return VImage::Format::Gray_8;
    throw std::logic_error( "Cannot define image format by channels" );
}
//=======================================================================================
VImage_OpenCV::VImage_OpenCV( const cv::Mat &mat )
    : _fmt ( bgr24_or_gray8(mat.channels()) )
    , _mat_obj_for_quick_convert ( cv::Mat() ) // ?
    , _mat_ref ( mat )
{}
//=======================================================================================
VImage_OpenCV::VImage_OpenCV( const cv::Mat &mat, VImage::Format fmt )
    : _fmt ( fmt )
    , _mat_obj_for_quick_convert ( cv::Mat() )
    , _mat_ref ( mat )
{
    if ( fmt == VImage::Format::Gray_8  && mat.channels() == 1 ) return;
    if ( fmt == VImage::Format::BGR_888 && mat.channels() == 3 ) return;
    if ( fmt == VImage::Format::RGB_888 && mat.channels() == 3 ) return;

    throw std::logic_error( "Incorrect format." );
}
//=======================================================================================
VImage_OpenCV::VImage_OpenCV( cv::Mat &&mat, VImage::Format fmt )
    : _fmt ( fmt )
    , _mat_obj_for_quick_convert ( std::move(mat) )
    , _mat_ref ( _mat_obj_for_quick_convert )
{}
//=======================================================================================
const cv::Mat &VImage_OpenCV::mat() const
{
    return _mat_ref;
}
//=======================================================================================
VImage_OpenCV VImage_OpenCV::to_rgb888() const
{
    auto fmt = VImage::Format::RGB_888;
    auto mat = to_format( fmt );
    return VImage_OpenCV( std::move(mat), fmt );
}
//=======================================================================================
VImage_OpenCV VImage_OpenCV::to_bgr888() const
{
    auto fmt = VImage::Format::BGR_888;
    auto mat = to_format( fmt );
    return VImage_OpenCV( std::move(mat), fmt );
}
//=======================================================================================
VImage_OpenCV VImage_OpenCV::to_gray8() const
{
    auto fmt = VImage::Format::Gray_8;
    auto mat = to_format( fmt );
    return VImage_OpenCV( std::move(mat), fmt );
}
//=======================================================================================
VImage::Format VImage_OpenCV::format() const
{
    return _fmt;
}
//=======================================================================================
cv::Mat VImage_OpenCV::to_format( VImage::Format dst_fmt ) const
{
    if ( dst_fmt == _fmt ) return _mat_ref;

    auto cvt_color = [this]( int dst_color )
    {
        cv::Mat result;
        cv::cvtColor( _mat_ref, result, dst_color );
        return result;
    };

    if ( _fmt == Format::Gray_8 )
    {
        if ( dst_fmt == Format::BGR_888 ) return cvt_color( cv::COLOR_GRAY2BGR );
        if ( dst_fmt == Format::RGB_888 ) return cvt_color( cv::COLOR_GRAY2RGB );
    } // Gray_8

    if ( _fmt == Format::BGR_888 )
    {
        if ( dst_fmt == Format::Gray_8  ) return cvt_color( cv::COLOR_BGR2GRAY );
        if ( dst_fmt == Format::RGB_888 ) return cvt_color( cv::COLOR_BGR2RGB  );
    } // BGR_888

    if ( _fmt == Format::RGB_888 )
    {
        if ( dst_fmt == Format::Gray_8  ) return cvt_color( cv::COLOR_RGB2GRAY );
        if ( dst_fmt == Format::BGR_888 ) return cvt_color( cv::COLOR_RGB2BGR  );
    } // RGB_888

    throw std::logic_error( "Invalid color format in cv::Mat before conversion." );
}
//=======================================================================================
int VImage_OpenCV::width() const
{
    return _mat_ref.size().width;
}
//=======================================================================================
int VImage_OpenCV::height() const
{
    return _mat_ref.size().height;
}
//=======================================================================================
int VImage_OpenCV::bytes_per_line() const
{
    return  _mat_ref.cols * int(_mat_ref.elemSize());
}
//=======================================================================================
const VImage::data_t *VImage_OpenCV::data() const
{
    return _mat_ref.data;
}
//=======================================================================================
