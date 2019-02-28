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


#ifndef VCV_IMAGE_H
#define VCV_IMAGE_H

#include <memory>
#include <vector>

#include "vcv_includes.h"


//=======================================================================================
namespace vcv
{
    //===================================================================================
    using Point2f = cv::Point2f;
    using Size    = cv::Size;
    using Interpolation = cv::InterpolationFlags;
    //===================================================================================
    //      Quadrangle  -- четырехугольник на плоскости (для perspective transform)
    //===================================================================================
    class Quadrangle
    {
    public:
        // Генерирует прямоугольник в первой четверти, такой: {(0,h)(w,h)(0,0)(w,0)}
        static Quadrangle rectangle( float width, float height );

        Quadrangle( const Point2f& tl,
                    const Point2f& tr,
                    const Point2f& bl,
                    const Point2f& br );

        const std::vector<Point2f>& operator()() const;

    private:
        std::vector<Point2f> _quadrangle;
    };
    //===================================================================================
    //      Quadrangle
    //===================================================================================


    //===================================================================================
    //      PerspectiveTransform
    //===================================================================================
    class PerspectiveTransform
    {
    public:
        PerspectiveTransform( const Quadrangle& src, const Quadrangle& dst );

    private:
        cv::Mat _transform;
    };
    //===================================================================================
    //      PerspectiveTransform
    //===================================================================================


    //===================================================================================
    //      Image
    //===================================================================================
    //  Методы будем делать виртуальными, чтобы перегружать все возможные в GpuImage.
    class Image
    {
    public:
        enum _need_clone { need_clone, non_clone };
        Image( const VImage& src, _need_clone = need_clone );

        Image( const cv::Mat& mat );

        Image();
        virtual ~Image();
        Image( Image&& rhs );
        Image( const Image& rhs );
        Image& operator = ( Image&& rhs );
        Image& operator = ( const Image& rhs );

        const cv::Mat& mat() const;



        class Projection;

        // https://docs.opencv.org/2.4/modules/imgproc/doc/geometric_transformations.html
        //  find resize there
        Image resize( double fx, double fy, Interpolation i = cv::INTER_LINEAR ) const;
        Image resize( Size dsize, Interpolation i = cv::INTER_LINEAR ) const;

    protected:
        Image _resize( Size dsize, double fx, double fy,
                       Interpolation interpolation ) const;

        // Ручное управление, чтобы перегружать (или нет) содержимое с GpuMat.
        class Pimpl; Pimpl *p = nullptr;
        Image( Pimpl *pp );
    };
    //===================================================================================
    //      Image
    //===================================================================================
    //      GpuImage
    //===================================================================================
    class GpuImage
    {
    public:
        GpuImage( const VImage& src );

        GpuImage();
        virtual ~GpuImage();
        GpuImage( GpuImage&& rhs );
        GpuImage( const GpuImage& rhs );
        GpuImage& operator = ( GpuImage &&rhs );
        GpuImage& operator = ( const GpuImage& rhs );

        GpuImage resize( double fx, double fy, Interpolation i = cv::INTER_LINEAR) const;
        GpuImage resize( Size dsize, Interpolation i = cv::INTER_LINEAR) const;

        Image download() const;

        int channels() const;

    protected:
        GpuImage _resize( Size dsize, double fx, double fy,
                          Interpolation interpolation ) const;

    private:
        class Pimpl; Pimpl *p;
    };
    //===================================================================================
    //      GpuImage
    //===================================================================================


    //===================================================================================
    //      Projection
    //===================================================================================
    class Image::Projection final
    {
    public:
        class ObjectPoints;
        class Rotation;
        class Translation;
        class CameraMatrix;
        class Distortion;

        Projection( const ObjectPoints& ops,
                    const Rotation&     rtn,
                    const Translation&  trn,
                    const CameraMatrix& cmt,
                    const Distortion&   dsn );

        static Projection default_project_1( float left,
                                             float right,
                                             float near,
                                             float far );

        const std::vector<cv::Point2f>& image_points() const;

    private:
        std::vector<cv::Point2f> _image_points;
    };
    //===================================================================================

    class Image::Projection::ObjectPoints final
    {
    public:
        ObjectPoints( float left, float right, float near, float far );

    private:
        friend class Projection;
        std::vector<cv::Point3f> _points;
    };
    //===================================================================================
    class Image::Projection::Rotation
    {
    public:
        static Rotation default_rtn_1();
        Rotation( float x, float y, float z );

    private:
        friend class Projection;
        std::vector<float> _rotation;
    };
    //===================================================================================
    class Image::Projection::Translation
    {
    public:
        static Translation default_trn_1();
        Translation( float x, float y, float z );

    private:
        friend class Projection;
        std::vector<float> _translation;
    };
    //===================================================================================
    // http://devdoc.net/linux/OpenCV-3.2.0/d9/d0c/group__calib3d.html#
    //  ga1019495a2c8d1743ed5cc23fa0daff8c
    class Image::Projection::CameraMatrix
    {
    public:
        static CameraMatrix default_mtx_1();
        CameraMatrix( float Fx, float Cx, float Fy, float Cy );

    private:
        friend class Projection;
        cv::Mat _mat;
    };
    //===================================================================================
    // Input vector of distortion coefficients
    // (k1,k2,p1,p2[,k3[,k4,k5,k6[,s1,s2,s3,s4[,τx,τy]]]]) of 4, 5, 8, 12 or 14 elements.
    // If the vector is empty, the zero distortion coefficients are assumed.
    class Image::Projection::Distortion
    {
    public:
        Distortion( float k1 = 0, float k2 = 0,
                    float p1 = 0, float p2 = 0,
                    float k3 = 0 );

    private:
        friend class Projection;
        std::vector<float> _distortion;
    };
    //===================================================================================
    //      Projection
    //===================================================================================

} // namespace vcv
//=======================================================================================


#endif // VCV_IMAGE_H
