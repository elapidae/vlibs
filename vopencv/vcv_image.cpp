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


#include "vlog_pretty.h"

using namespace vcv;

//=======================================================================================
class Image::Pimpl
{
public:
    cv::Mat mat;
};
//=======================================================================================


//=======================================================================================
Image::Image( Image::Pimpl *pp )
    : p( pp )
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
// http://devdoc.net/linux/OpenCV-3.2.0/d9/d0c/group__calib3d.html#ga1019495a2c8d1743ed5cc23fa0daff8c
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




//=======================================================================================
#ifdef V_OPENCV_USE_CUDA
#endif
//=======================================================================================



