#include "vcvimage_impl.h"

#include "vlog_pretty.h"
#include <iostream>

VCVImage_Impl::VCVImage_Impl()
{}

int VCVImage_Impl::format_to_VCVImageDepth(VImage::Format f)
{
    switch( f )
    {
    case Format::Invalid: return -1;
    case Format::Gray_8:   return CV_8UC1;
    case Format::RGB_888:  return CV_8UC3;
    case Format::BGR_888:  return CV_8UC3;
    }
    throw VLogError( vfatal << "Unknown vimage format:" << int(f) );
}

VCVImage_Impl VCVImage_Impl::copy_from( const VImage &src )
{
    auto img = convert(src);
    return std::move(VCVImage_Impl(img, src.format()));
}

VCVImage_Impl VCVImage_Impl::convert_to_format( const Format format_ )
{
    std::cout << "Current format: " << (int)image_format << "\n";
    std::cout << "Expected format: " << (int)format_ << "\n";
	int cvt_flag = -1;
    switch( image_format )
    {
    case Format::Invalid: cvt_flag -1; // TODO
    case Format::Gray_8:
		switch( format_ )
		{
            case Format::Invalid: cvt_flag = 0;
            case Format::Gray_8:   cvt_flag = -1;
            case Format::RGB_888:  cvt_flag = cv::COLOR_GRAY2RGB;
            case Format::BGR_888:  cvt_flag = cv::COLOR_GRAY2BGR;
		}
    case Format::RGB_888:
		switch( format_ )
		{
            case Format::Invalid: cvt_flag = 0;
            case Format::Gray_8:  cvt_flag = cv::COLOR_RGB2GRAY;
            case Format::RGB_888:  cvt_flag = -1;
            case Format::BGR_888:  cvt_flag = cv::COLOR_RGB2BGR;
		}
    case Format::BGR_888:
		switch( format_ )
		{
            case Format::Invalid: cvt_flag = 0;
            case Format::Gray_8:  cvt_flag = cv::COLOR_BGR2GRAY;
            case Format::RGB_888:  cvt_flag = cv::COLOR_BGR2RGB;
            case Format::BGR_888:  cvt_flag = -1;
		}
    }

    if (cvt_flag == -1)
    {
        return *this;
        return VCVImage_Impl(this->image(), format_);
	}

	cv::Mat mat;
    cv::cvtColor(img, mat, cvt_flag);

    return VCVImage_Impl(mat, format_);
}

int VCVImage_Impl::width() const
{
    return img.size().width;
}

int VCVImage_Impl::height() const
{
    return img.size().height;
}

const cv::Mat &VCVImage_Impl::image() const
{
    return img;
}

cv::Mat &VCVImage_Impl::image()
{
    return img;
}

int VCVImage_Impl::bytes_per_line() const
{
    return img.cols * img.elemSize();
}

VImage::Format VCVImage_Impl::format() const
{
    int expected_channels = 0;

    switch ( image_format )
    {
    case VImage::Format::Invalid:    expected_channels = 0;
    case VImage::Format::Gray_8:      expected_channels = 1;
    case VImage::Format::RGB_888:     expected_channels = 3;

    default: break;
    }

    if ( expected_channels != img.channels() )
    {
        throw VLogError( vfatal << "Mismatch of the number of the real number of image channels and "
                                << "the number of channels of the format. "
                                << "Format: " << int(image_format) << "; "
                                << "Real number of channels: " << img.channels() << "; "
                                << "Expected number of channels: " << expected_channels);
    }
    return image_format;
}

const VImage::data_t * VCVImage_Impl::data() const
{/*
    std::cout << (img.dataend - img.data) / (3) << "\n";
    std::cout << "height: " << (img.dataend - img.data) / width() / 3 << "\n";
    std::cout << "width: " << (img.dataend - img.data) / height() / 3 << "\n";
    std::cout << "Real height: " << height() << "\n";
    std::cout << "Real width: " << width() << "\n";
    std::cout << "Bytes per line: " << bytes_per_line() << "\n";
    std::cout << "Lines: " << (img.dataend - img.data) / bytes_per_line() << "\n";*/
    //vdeb << "Lines: " << (img.dataend - img.data) / bytes_per_line();
    return img.data;
}

VCVImage_Impl::VCVImage_Impl( const cv::Mat &img_, Format format_ )
{
    img = img_.clone();
    image_format = format_;
}

VCVImage_Impl::VCVImage_Impl( cv::Mat &&img_, Format format_ )
    : img( std::move(img_) )
{
    //img = img_.clone();
    image_format = format_;
}

const VImage::data_t *VCVImage_Impl::line( int row ) const
{
    return (data_t*) img.row( row ).data;
}

void VCVImage_Impl::set_format(Format new_format)
{
    image_format = new_format;
}

cv::Mat VCVImage_Impl::convert(const VImage& src)
{
    cv::Mat img( src.height(), // rows
                 src.width(), // cols
                 format_to_VCVImageDepth(src.format()), // type (CV_DEPTH MACROS)
                 const_cast<void*>(static_cast<const void*>(src.data())),
                 src.bytes_per_line() );

    return img;
}
