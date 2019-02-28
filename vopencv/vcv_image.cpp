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

#include "vcv_image.h"

#include "vlog.h"
#include "verror.h"



using namespace vcv;

//=======================================================================================
static int vformat_to_cvformat( VImage::Format f )
{
    switch (f)
    {
    case VImage::Format::Gray_8:  return CV_8UC1;

    case VImage::Format::RGB_888: return CV_8UC3;   // same,
    case VImage::Format::BGR_888: return CV_8UC3;   // be carefull.
    default: break;
    }
    throw verror( "Cannot detect VImage format: ", int(f) );
}
//=======================================================================================
template<typename T>
static void* nonconst_voidstar(const T* ptr)
{
    return const_cast<void*>( static_cast<const void*>(ptr) );
}
//=======================================================================================


//=======================================================================================
//      Image
//=======================================================================================
// init ctor: Mat(int rows, int cols, int type, void* data, size_t step=AUTO_STEP);
class Image::Pimpl
{
public:
    cv::Mat mat;

    Pimpl() {}

    Pimpl( const cv::Mat& src ) : mat(src) {}

    Pimpl( const VImage& src, _need_clone clone )
        : mat( src.height(),    // rows
               src.width(),     // cols
               vformat_to_cvformat(src.format()),
               nonconst_voidstar(src.data()),
               size_t(src.bytes_per_line()) )
    {
        if ( clone == need_clone )
            mat = mat.clone();
    }
};
//=======================================================================================
Image::Image( Image::Pimpl *pp )
    : p( pp )
{}
//=======================================================================================
Image::Image( const VImage& src , _need_clone cl )
    : p( new Pimpl(src, cl) )
{}
//=======================================================================================
Image::Image( const cv::Mat& mat )
    : p( new Pimpl(mat) )
{}
//=======================================================================================
Image::Image()
    : p( new Pimpl )
{}
//=======================================================================================
Image::~Image()
{
    delete p;
}
//=======================================================================================
Image::Image( Image && rhs )
    : p( nullptr )
{
    std::swap( p, rhs.p );
}
//=======================================================================================
Image::Image( const Image & rhs )
    : p( new Pimpl(*rhs.p) )
{}
//=======================================================================================
Image &Image::operator =( Image && rhs )
{
    std::swap( p, rhs.p );
    return *this;
}
//=======================================================================================
Image &Image::operator =( const Image & rhs )
{
    if ( this != &rhs )
    {
        p->mat = rhs.p->mat;
    }
    return *this;
}
//=======================================================================================
const cv::Mat& Image::mat() const
{
    return p->mat;
}
//=======================================================================================
Image Image::_resize( Size dsize, double fx, double fy, Interpolation i ) const
{
    Image dst;
    cv::resize( p->mat, dst.p->mat, dsize, fx, fy, i );
    return dst;
}
//=======================================================================================
Image Image::resize( double fx, double fy, Interpolation i ) const
{
    return _resize( Size(), fx, fy, i );
}
//=======================================================================================
Image Image::resize( Size dsize, Interpolation i ) const
{
    return _resize( dsize, 0, 0, i );
}
//=======================================================================================
//      Image
//=======================================================================================




//=======================================================================================
//      GpuImage
//=======================================================================================
#ifdef V_OPENCV_USE_CUDA
//=======================================================================================
class GpuImage::Pimpl
{
public:
    cv::cuda::GpuMat mat;

    Pimpl() {}

    Pimpl( const VImage& src )
    {
        cv::Mat m( src.height(), // rows
                   src.width(),  // cols
                   vformat_to_cvformat(src.format()),
                   nonconst_voidstar(src.data()),
                   size_t(src.bytes_per_line()) );

        mat.upload( m );
    }
};
//---------------------------------------------------------------------------------------
static void cuda_resize( const cv::cuda::GpuMat &src, cv::cuda::GpuMat *dst,
                         Size sz, double fx, double fy, Interpolation i )
{
    cv::cuda::resize( src, *dst, sz, fx, fy, i );
}
static Image cuda_download( const cv::cuda::GpuMat &mat )
{
    cv::Mat res;
    mat.download( res );
    return res;
}
#else // if not use CUDA ================================================================
class GpuImage::Pimpl
{
public:
    cv::Mat mat;

    Pimpl() {}
    Pimpl( const VImage& src )
        : mat( src.height(), // rows
               src.width(),  // cols
               vformat_to_cvformat(src.format()),
               nonconst_voidstar(src.data()),
               size_t(src.bytes_per_line()) )
    {}
};
//---------------------------------------------------------------------------------------
static void cuda_resize( const cv::Mat &src, cv::Mat *dst,
                         Size sz, double fx, double fy, Interpolation i )
{
    cv::resize( src, *dst, sz, fx, fy, i );
}
//---------------------------------------------------------------------------------------
static Image cuda_download( const cv::Mat& mat )
{
    return mat;
}
//=======================================================================================
#endif // ifdef V_OPENCV_USE_CUDA
//=======================================================================================


//=======================================================================================
GpuImage::GpuImage( const VImage &src )
    : p( new Pimpl(src) )
{}
//=======================================================================================
GpuImage::GpuImage()
    : p( new Pimpl )
{}
//=======================================================================================
GpuImage::~GpuImage()
{
    delete p;
}
//=======================================================================================
GpuImage::GpuImage( GpuImage && rhs )
    : p( nullptr )
{
    std::swap( p, rhs.p );
}
//=======================================================================================
GpuImage::GpuImage( const GpuImage & rhs )
    : p( new Pimpl(*rhs.p) )
{}
//=======================================================================================
GpuImage& GpuImage::operator = ( GpuImage && rhs )
{
    std::swap( p, rhs.p );
    return *this;
}
//=======================================================================================
GpuImage & GpuImage::operator = ( const GpuImage & rhs )
{
    if ( &rhs != this )
    {
        p->mat = rhs.p->mat;
    }
    return *this;
}
//=======================================================================================
Image GpuImage::download() const
{
    return cuda_download( p->mat );
}
//=======================================================================================
int GpuImage::channels() const
{
    return p->mat.channels();
}
//=======================================================================================
GpuImage GpuImage::resize( double fx, double fy, Interpolation i ) const
{
    return _resize( Size(), fx, fy, i );
}
//=======================================================================================
GpuImage GpuImage::resize( Size dsize, Interpolation i ) const
{
    return _resize( dsize, 0, 0, i );
}
//=======================================================================================
GpuImage GpuImage::_resize( Size dsize, double fx, double fy, Interpolation i ) const
{
    GpuImage dst;
    cuda_resize( p->mat, &dst.p->mat, dsize, fx, fy, i );
    return dst;
}
//=======================================================================================
//      GpuImage
//=======================================================================================




//=======================================================================================
//      Quadrangle
//=======================================================================================
Quadrangle Quadrangle::rectangle( float width, float height )
{
    return { { 0,     height },
             { width, height },
             { 0,     0      },
             { width, 0      } };
}
//=======================================================================================
Quadrangle::Quadrangle( const Point2f &tl,
                        const Point2f &tr,
                        const Point2f &bl,
                        const Point2f &br )
    : _quadrangle{ tl, tr, bl, br }
{}
//=======================================================================================
const std::vector<Point2f> &Quadrangle::operator()() const
{
    return _quadrangle;
}
//=======================================================================================
//      Quadrangle
//=======================================================================================


//=======================================================================================
//      PerspectiveTransform
//=======================================================================================
PerspectiveTransform::PerspectiveTransform( const Quadrangle &src,
                                            const Quadrangle &dst )
    : _transform( cv::getPerspectiveTransform(src(), dst()) )
{}
//=======================================================================================
//      PerspectiveTransform
//=======================================================================================


//=======================================================================================
//      Image::Projection::ObjectPoints
//=======================================================================================
Image::Projection::ObjectPoints::ObjectPoints( float left, float right,
                                               float near, float far )
{
    _points.push_back( cv::Point3f(left,  0, near) );
    _points.push_back( cv::Point3f(right, 0, near) );
    _points.push_back( cv::Point3f(left,  0, far)  );
    _points.push_back( cv::Point3f(right, 0, far)  );
}
//=======================================================================================
//      Image::Projection::Rotation
//=======================================================================================
vcv::Image::Projection::Rotation Image::Projection::Rotation::default_rtn_1()
{
    return { 0.15610699f, 0.03508545f, 0.00604089f };
}
//=======================================================================================
Image::Projection::Rotation::Rotation( float x, float y, float z )
    : _rotation{ x, y, z }
{}
//=======================================================================================
//      Image::Projection::Translation
//=======================================================================================
vcv::Image::Projection::Translation Image::Projection::Translation::default_trn_1()
{
    return { -0.01607784f, 4.92202892f, -1.91157204f };
}
//=======================================================================================
Image::Projection::Translation::Translation( float x, float y, float z )
    : _translation{ x, y, z }
{}
//=======================================================================================
//      Image::Projection::CameraMatrix
//=======================================================================================
vcv::Image::Projection::CameraMatrix Image::Projection::CameraMatrix::default_mtx_1()
{
    return { 3100.884521484375f,
             1068.06743f,
             3451.33646f,
             825.05407f
           };
}
//=======================================================================================
// http://devdoc.net/linux/OpenCV-3.2.0/d9/d0c/group__calib3d.html#
//  ga1019495a2c8d1743ed5cc23fa0daff8c
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
Image::Projection::CameraMatrix::CameraMatrix( float Fx, float Cx, float Fy, float Cy )
{
    _mat = ( cv::Mat_<float>(3, 3) << Fx,   0,  Cx,
                                       0,  Fy,  Cy,
                                       0,   0,   1 );

    assert( _mat.at<float>(0,0) == Fx );
    assert( _mat.at<float>(0,1) == 0 );
    assert( _mat.at<float>(0,2) == Cx );

    assert( _mat.at<float>(1,0) == 0 );
    assert( _mat.at<float>(1,1) == Fy );
    assert( _mat.at<float>(1,2) == Cy );

    assert( _mat.at<float>(2,0) == 0 );
    assert( _mat.at<float>(2,1) == 0 );
    assert( _mat.at<float>(2,2) == 1 );
}
#pragma GCC diagnostic pop
//=======================================================================================
Image::Projection::Distortion::Distortion( float k1, float k2,
                                           float p1, float p2 ,
                                           float k3 )
    : _distortion{ k1, k2, p1, p2, k3 }
{}
//=======================================================================================
Image::Projection::Projection( const ObjectPoints&  ops,
                               const Rotation&      rtn,
                               const Translation&   trn,
                               const CameraMatrix&  cmt,
                               const Distortion&    dsn )
{
    cv::projectPoints( ops._points,
                       rtn._rotation,
                       trn._translation,
                       cmt._mat,
                       dsn._distortion,
                       _image_points );
}
//=======================================================================================
vcv::Image::Projection Image::Projection::default_project_1( float left,
                                                             float right,
                                                             float near,
                                                             float far )
{
    return Projection( {left, right, near, far},
                       Rotation::default_rtn_1(),
                       Translation::default_trn_1(),
                       CameraMatrix::default_mtx_1(),
                       {}
                     );
}
//=======================================================================================
const std::vector<cv::Point2f> &Image::Projection::image_points() const
{
    return _image_points;
}
//=======================================================================================
//      Image::Projection
//=======================================================================================
