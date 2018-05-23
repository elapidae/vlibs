//=======================================================================================
// vimage_opencv.h
//=======================================================================================
#ifndef VIMAGE_OPENCV_DEV1
#define VIMAGE_OPENCV


#include <opencv2/opencv.hpp>

#include "vimage.h"



//=======================================================================================
class VImage_OpenCV : public VImage
{
public:
    // Конвертирует либо в Gray8 либо в BGR24, в зависимости от аргумента.
    // Если формат не поддерживается, бросается исключение std::logic_error.
    static cv::Mat convert( const VImage &img );

    // Если mat содержит 3 канала, формат воспринимается как BGR24, если один -- Gray8.
    // Иначе -- std::logic_error.
    explicit VImage_OpenCV( const cv::Mat &mat );

    // Количество каналов и формат должны подходить друг к другу, иначе logic_error
    explicit VImage_OpenCV( const cv::Mat &mat, VImage::Format fmt );

    const cv::Mat &mat() const;

    cv::Mat to_format( VImage::Format fmt ) const;


    // Возвращает конвертированную картинку прямо в интерфейсе,
    // без необходимости во временных объектах. По сути, оборачивает to_format()
    VImage_OpenCV to_rgb888() const;
    VImage_OpenCV to_bgr888() const;
    VImage_OpenCV to_gray8()  const;


    virtual Format format()             const override;

    virtual int width()                 const override;
    virtual int height()                const override;

    virtual const data_t* data()        const override;

    virtual int bytes_per_line()        const override;

    virtual ~VImage_OpenCV() = default;

private:
    VImage_OpenCV( cv::Mat && mat, VImage::Format fmt );

    VImage::Format _fmt;
    const cv::Mat  _mat_obj_for_quick_convert;
    const cv::Mat  &_mat_ref;
};
//=======================================================================================



#endif // VIMAGE_OPENCV
//=======================================================================================
// /vimage_opencv.h
//=======================================================================================
