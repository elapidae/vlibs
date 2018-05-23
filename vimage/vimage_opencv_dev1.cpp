#include "vimage_opencv_dev1.h"


//=======================================================================================
static VImage::Format bgr24_or_gray8( int channels_count )
{
    if ( channels_count == 3 ) return VImage::Format::BGR_888;
    if ( channels_count == 1 ) return VImage::Format::Gray_8;
    throw std::logic_error( "Cannot define image format by channels" );
}
//=======================================================================================
VImage_OpenCv::VImage_OpenCv( const cv::Mat &mat )
    : _fmt ( bgr24_or_gray8(mat.channels()) )
    , _mat_obj_for_quick_convert ( cv::Mat() )
    , _mat_ref ( mat )
{}
//=======================================================================================
VImage_OpenCv::VImage_OpenCv( const cv::Mat &mat, VImage::Format fmt )
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
VImage_OpenCv::VImage_OpenCv( cv::Mat &&mat, VImage::Format fmt )
    : _fmt ( fmt )
    , _mat_obj_for_quick_convert ( std::move(mat) )
    , _mat_ref ( _mat_obj_for_quick_convert )
{}
//=======================================================================================
const cv::Mat &VImage_OpenCv::mat() const
{
    return _mat_ref;
}
//=======================================================================================
VImage_OpenCv VImage_OpenCv::to_rgb888() const
{
    auto fmt = VImage::Format::RGB_888;
    auto mat = to_format( fmt );
    return VImage_OpenCv( std::move(mat), fmt );
}
//=======================================================================================
VImage_OpenCv VImage_OpenCv::to_bgr888() const
{
    auto fmt = VImage::Format::BGR_888;
    auto mat = to_format( fmt );
    return VImage_OpenCv( std::move(mat), fmt );
}
//=======================================================================================
VImage_OpenCv VImage_OpenCv::to_gray8() const
{
    auto fmt = VImage::Format::Gray_8;
    auto mat = to_format( fmt );
    return VImage_OpenCv( std::move(mat), fmt );
}
//=======================================================================================
VImage::Format VImage_OpenCv::format() const
{
    return _fmt;
}
//=======================================================================================
cv::Mat VImage_OpenCv::to_format( VImage::Format fmt ) const
{
    throw std::logic_error( "Not implemented, use _mat_ref or mat() for work." );
}
//=======================================================================================
int VImage_OpenCv::width() const
{
    // ??? return mat().cols;
    throw std::logic_error( "Not implemented, use _mat_ref or mat() for work." );
}
//=======================================================================================
int VImage_OpenCv::height() const
{
    throw std::logic_error( "Not implemented, use _mat_ref or mat() for work." );
}
//=======================================================================================
int VImage_OpenCv::bytes_per_line() const
{
    throw std::logic_error( "Not implemented, use _mat_ref or mat() for work." );
}
//=======================================================================================
const VImage::data_t *VImage_OpenCv::data() const
{
    throw std::logic_error( "Not implemented, use _mat_ref or mat() for work." );
}
//=======================================================================================
const VImage::data_t *VImage_OpenCv::line( int row ) const
{
    // Можно не перегружать если устроит вариант
    // if ( row >= height() ) throw std::out_of_range("VImage::line: row >= height()");
    // return data() + row * bytes_per_line();

    throw std::logic_error( "Not implemented, use _mat_ref or mat() for work." );
}
//=======================================================================================
int VImage_OpenCv::data_size() const
{
    // Можно не перегружать если устроит вариант
    // return bytes_per_line() * height();

    throw std::logic_error( "Not implemented, use _mat_ref or mat() for work." );
}
//=======================================================================================
