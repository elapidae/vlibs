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
Image::Projection::ObjectPoints::ObjectPoints( float left, float right,
                                               float near, float far )
{
    _points.push_back( cv::Point3f(left,  0, near) );
    _points.push_back( cv::Point3f(right, 0, near) );
    _points.push_back( cv::Point3f(left,  0, far)  );
    _points.push_back( cv::Point3f(right, 0, far)  );
}
//=======================================================================================
Image::Projection::ObjectPoints::~ObjectPoints()
{}
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
vcv::Image::Projection::Translation Image::Projection::Translation::default_trn_1()
{
    return { -0.01607784f, 4.92202892f, -1.91157204f };
}
//=======================================================================================
Image::Projection::Translation::Translation( float x, float y, float z )
    : _translation{ x, y, z }
{}
//=======================================================================================
class Image::Projection::CameraMatrix::Pimpl
{
public:
    cv::Mat mat;
};
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
    : p( std::make_shared<Pimpl>() )
{
    p->mat = ( cv::Mat_<float>(3, 3) << Fx, 0,  Cx,
                                        0,  Fy, Cy,
                                        0,  0,  1  );

    assert( p->mat.at<float>(0,0) == Fx );
    assert( p->mat.at<float>(0,1) == 0 );
    assert( p->mat.at<float>(0,2) == Cx );

    assert( p->mat.at<float>(1,0) == 0 );
    assert( p->mat.at<float>(1,1) == Fy );
    assert( p->mat.at<float>(1,2) == Cy );

    assert( p->mat.at<float>(2,0) == 0 );
    assert( p->mat.at<float>(2,1) == 0 );
    assert( p->mat.at<float>(2,2) == 1 );
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
                       cmt.p->mat,
                       dsn._distortion,
                       _image_points );
}
//=======================================================================================
Image::Projection::~Projection()
{}
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
void Image::Projection::v_deb() const
{
    vdeb << _image_points;
}
//=======================================================================================
//  Projection
//=======================================================================================




//=======================================================================================
#ifdef V_OPENCV_USE_CUDA
#endif
//=======================================================================================



