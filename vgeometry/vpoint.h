#ifndef VPOINT_H
#define VPOINT_H

#include "vbytearray.h"
#include <vector>
#include <list>


//=======================================================================================
/*  2018-01-25
 *  Резюме: автора задолбало искать годный мат. пакет для работы на уровне геометрии
 *  пятого класса. Нужны координатные точки. Просто точки, чуть умнее зубочисток.
 *
 *  VDecartPoint<T>, VPolarPoint<T>, где T - любой числовой тип.
 *  using VDecPoint = VDecartPoint<float>;  // Алиасы к типу,
 *  using VPolPoint = VPolarPoint<float>;   // используются в 99% случаев.
 *
 *  // TODO: должны уметь себя записывать и читать из VByteArray.
 *
 *  Методы будут дописываться по необходимости.
 *
*/
//=======================================================================================





//=======================================================================================
//      VDecartPoint
//=======================================================================================
template<typename T> class VPolarPoint;         // Для forward definition.
//=======================================================================================
template<typename T>
class VDecartPoint
{
public:
    class Vector;

    T x, y;

    VDecartPoint();
    VDecartPoint( T xx, T yy );

    T angle() const;
    T vector_len() const;

    VPolarPoint<T> to_polar() const;

    const VDecartPoint<T> & operator -= ( const VDecartPoint<T> &rhs );

    T distance_to( const VDecartPoint<T> &rhs ) const;

    template<typename Dst>
    Dst convert_to_any_xy_type() const { return {x, y}; }
};
//=======================================================================================
template<typename T>
class VDecartPoint<T>::Vector : public std::vector<VDecartPoint<T>>
{
public:
    typename VPolarPoint<T>::Vector to_polar() const;
};
//=======================================================================================
using VDecPoint = VDecartPoint<float>;
//=======================================================================================
template<typename T>
VDecartPoint<T> operator - ( const VDecartPoint<T> &lhs, const VDecartPoint<T> &rhs );
//=======================================================================================
//      VDecartPoint
//=======================================================================================



//=======================================================================================
//      VPolarPoint
//=======================================================================================
template<typename T>
class VPolarPoint
{
public:
    class Vector;

    T distance, angle;

    VPolarPoint();
    VPolarPoint( T d, T a );


    T distance_to( const VPolarPoint &rhs ) const;

    VDecartPoint<T> to_decart() const;
};
//=======================================================================================
template<typename T>
class VPolarPoint<T>::Vector : public std::vector<VPolarPoint<T>>
{
public:
    typename VDecartPoint<T>::Vector to_decart() const;

    // Сложность O(n).
    VPolarPoint average_center() const;
};
//=======================================================================================
using VPolPoint = VPolarPoint<float>;
//=======================================================================================
//      VPolarPoint
//=======================================================================================




//=======================================================================================
//      IMPLEMENTATION VDecartPoint
//=======================================================================================
template<typename T>
VDecartPoint<T>::VDecartPoint()
{}
//=======================================================================================
template<typename T>
VDecartPoint<T>::VDecartPoint( T xx, T yy )
    : x(xx), y(yy)
{}
//=======================================================================================
template<typename T>
T VDecartPoint<T>::angle() const
{
    return  std::atan2( y, x );
}
//=======================================================================================
template<typename T>
T VDecartPoint<T>::vector_len() const
{
    return std::hypot(x, y);
}
//=======================================================================================
template<typename T>
VPolarPoint<T> VDecartPoint<T>::to_polar() const
{
    return { vector_len(), angle() };
}
//=======================================================================================
template<typename T>
const VDecartPoint<T> & VDecartPoint<T>::operator -=( const VDecartPoint<T> &rhs )
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}
//=======================================================================================
template<typename T>
T VDecartPoint<T>::distance_to( const VDecartPoint<T> &rhs ) const
{
    return (*this - rhs).vector_len();
}
//=======================================================================================
//=======================================================================================
template<typename T>
typename VPolarPoint<T>::Vector VDecartPoint<T>::Vector::to_polar() const
{
    typename VPolarPoint<T>::Vector res;

    for ( auto & dp: *this )
        res.push_back( dp.to_polar() );

    return res;
}
//=======================================================================================
//=======================================================================================
template<typename T>
VDecartPoint<T> operator - ( const VDecartPoint<T> &lhs, const VDecartPoint<T> &rhs )
{
    auto res = lhs;
    return std::move( res -= rhs );
}
//=======================================================================================
//      IMPLEMENTATION VDecartPoint
//=======================================================================================





//=======================================================================================
//      IMPLEMENTATION VPolarPoint
//=======================================================================================
template<typename T>
VPolarPoint<T>::VPolarPoint()
    : VPolarPoint(NAN, NAN)
{}
//=======================================================================================
template<typename T>
VPolarPoint<T>::VPolarPoint( T d, T a )
    : distance(d)
    , angle(a)
{}
//=======================================================================================
template<typename T>
T VPolarPoint<T>::distance_to( const VPolarPoint &rhs ) const
{
    auto delta_angle = angle - rhs.angle;
    return sqrt( distance * distance
                 + rhs.distance * rhs.distance
                 - 2 * distance * rhs.distance * cos(delta_angle) );
}
//=======================================================================================
template<typename T>
VDecartPoint<T> VPolarPoint<T>::to_decart() const
{
    return { distance * std::cos(angle),
             distance * std::sin(angle) };
}
//=======================================================================================
template<typename T>
VPolarPoint<T> VPolarPoint<T>::Vector::average_center() const
{
    if ( this->empty() ) return {};

    T distance_sum = 0;
    T angle_sum = 0;

    for ( auto pp: *this )
    {
        distance_sum += pp.distance;
        angle_sum    += pp.angle;
    }
    return { distance_sum / this->size(),
                angle_sum / this->size() };
}
//=======================================================================================
template<typename T>
typename VDecartPoint<T>::Vector VPolarPoint<T>::Vector::to_decart() const
{
    typename VDecartPoint<T>::Vector res;

    for ( auto &pp: *this )
        res.push_back( pp.to_decart() );

    return res;
}
//=======================================================================================
//      IMPLEMENTATION VPolarPoint
//=======================================================================================




#endif // VPOINT_H
