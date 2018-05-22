#ifndef VCVIMAGE_IMPL_H
#define VCVIMAGE_IMPL_H

#include "vimage.h"
#include <opencv2/opencv.hpp>

class VCVImage_Impl final : public VImage
{
public:

    VCVImage_Impl();
    VCVImage_Impl( VCVImage_Impl && ) = default;
    VCVImage_Impl( const VCVImage_Impl & ) = default;
    VCVImage_Impl& operator = ( VCVImage_Impl && ) = default;
    VCVImage_Impl& operator = ( const VCVImage_Impl & ) = default;

    static int format_to_VCVImageDepth(VImage::Format f);

    static VCVImage_Impl copy_from( const VImage &src );

    VCVImage_Impl( cv::Mat && img, Format format_ = Format::Invalid );
    VCVImage_Impl( const cv::Mat & img, Format format_ = Format::Invalid );

    VCVImage_Impl convert_to_format( const Format format_ );

    virtual VImage::Format format()             const override;

    virtual int width()                         const override;
    virtual int height()                        const override;
    virtual int bytes_per_line()                const override;

    virtual const VImage::data_t* data()        const override;
    virtual const VImage::data_t* line(int row) const override;

    cv::Mat &image();
    const cv::Mat &image() const;

    void set_format(Format new_format);
    static cv::Mat convert(const VImage& src);


private:
    cv::Mat img;
    Format image_format;
};



#endif // VCVIMAGE_IMPL_H
