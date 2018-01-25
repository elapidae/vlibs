#include "vfloatpoint2d.h"

#include <algorithm>


//=======================================================================================
//VFloatPoint2D VFloatPoint2D::from_back_LE(VByteArray *buf)
//{
//    auto yy = buf->pop_back_little<decltype(y)>();
//    auto xx = buf->pop_back_little<decltype(x)>();

//    return { xx, yy };
//}
////=======================================================================================
//void VFloatPoint2D::to_back_LE(VByteArray *buf) const
//{
//    buf->push_back_little(x);
//    buf->push_back_little(y);
//}
////=======================================================================================

////=======================================================================================
//VFloatPoint2D::VFloatPoint2D()
//    : x(NAN), y(NAN)
//{}
////=======================================================================================
//VFloatPoint2D::VFloatPoint2D( float xx, float yy )
//    : x(xx), y(yy)
//{}
////=======================================================================================
//bool VFloatPoint2D::is_valid() const
//{
//    return x == x && y == y;
//}
////=======================================================================================
//bool VFloatPoint2D::operator ==( const VFloatPoint2D &rhs ) const
//{
//    return x == rhs.x &&
//           y == rhs.y;
//}
////=======================================================================================
//bool VFloatPoint2D::operator !=( const VFloatPoint2D &rhs ) const
//{
//    return !( *this == rhs );
//}
////=======================================================================================
//float VFloatPoint2D::distance_to( const VFloatPoint2D &rhs ) const
//{
//    return std::hypotf( x - rhs.x, y - rhs.y );
//}
////=======================================================================================
