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


#ifndef VPOINTS_H
#define VPOINTS_H

#include <math.h>
#include <vector>
#include <ostream>
#include <algorithm>
#include <numeric>

//=======================================================================================
/*
 *  2018-01-25
 *  Резюме: автора задолбало искать годный мат. пакет для работы на уровне геометрии
 *  пятого класса. Нужны координатные точки. Просто точки, чуть умнее зубочисток.
 *
 *  UDP 2018-02-24
 *  Первая версия была комом, переделывается на новую основу: во-первых, точки это не
 *  часть геометрии, это просто точки. Во-вторых, принимается следующее именование:
 *  По умолчанию, точки декартовы.
 *  VPoint<T>, VPolarPoint<T>, где T - любой числовой тип.
 *  VPointF, VPolarPointF -- с типом float (99% использования).
 *
 *  И декартовы и полярные точки имеют методы:
 *  T x();          // Координаты в декарте.
 *  T y();          // Единицы измерения -- на выбор пользователя.
 *  T distance();   // Расстояние до точки из декартового (0,0).
 *  T angle();      // Угол -- в радианах.
 *  Разница только в том, что декартовы точки вычисляют distance() и angle(),
 *  а полярные вычисляют x() и y().
 *
 *  Декартовы обладают методом to_polar(), полярные -- to_cartesian() (это декартовы
 *  по буржуйски).
*/
//=======================================================================================




//=======================================================================================
//      VPoint // Cartesian
//=======================================================================================
template<typename T> class VPolarPoint;         // Для forward definition.
//=======================================================================================
template<typename T>
class VPoint
{
public:

    using value_type = T;

    //-----------------------------------------------------------------------------------
    VPoint();
    VPoint( const T& xx, const T& yy );

    T x()               const;
    T y()               const;
    T distance()        const;
    T angle()           const;
    T angle_degrees()   const;

    VPolarPoint<T> to_polar() const;

    const VPoint<T> & operator += ( const VPoint<T> &rhs );
    const VPoint<T> & operator -= ( const VPoint<T> &rhs );

    bool operator == ( const VPoint<T> &rhs ) const;        //  Вещественные сравнивает
    bool operator != ( const VPoint<T> &rhs ) const;        //  через эпсилон.

    bool is_valid() const;

    T distance_to( const VPoint<T> & other ) const;

    //-----------------------------------------------------------------------------------
    class Vector : public std::vector<VPoint<T>>
    {
    public:
        using std::vector<VPoint<T>>::vector;

        typename VPolarPoint<T>::Vector to_polar() const;
        VPoint<T> average_center() const;
    };

    //-----------------------------------------------------------------------------------
private:
    T _x, _y;
}; // VPoint class
//=======================================================================================
template<typename T>
VPoint<T> operator + ( const VPoint<T> &lhs, const VPoint<T> &rhs );

template<typename T>
VPoint<T> operator - ( const VPoint<T> &lhs, const VPoint<T> &rhs );
//=======================================================================================
using VPointF = VPoint<float>;
using VPointD = VPoint<double>;
//=======================================================================================
//      VPoint // Cartesian
//=======================================================================================



//=======================================================================================
//      VPolarPoint
//=======================================================================================
template<typename T>
class VPolarPoint
{
public:
    //-----------------------------------------------------------------------------------
    VPolarPoint();
    VPolarPoint( const T& distance, const T& angle );

    T x()               const;
    T y()               const;
    T distance()        const;
    T angle()           const;
    T angle_degrees()   const;

    VPoint<T> to_cartesian() const;

    bool operator == ( const VPolarPoint<T> &rhs ) const;   // Вещественные сравнивает
    bool operator != ( const VPolarPoint<T> &rhs ) const;   // через эпсилон.

    bool is_valid() const;

    T distance_to( const VPolarPoint & other );

    //-----------------------------------------------------------------------------------
    class Vector : public std::vector<VPolarPoint<T>>
    {
    public:
        typename VPoint<T>::Vector to_cartesian() const;
    };

    //-----------------------------------------------------------------------------------
private:
    T _distance, _angle;
}; // VPolarPoint class
//=======================================================================================
using VPolarPointF = VPolarPoint<float>;
using VPolarPointD = VPolarPoint<double>;
//=======================================================================================
//      VPolarPoint
//=======================================================================================


//=======================================================================================
//      Streaming
//=======================================================================================
template<typename T>
std::ostream & operator << (std::ostream &os, const VPoint<T> &p )
{
    os << "(x=" << p.x() << ",y=" << p.y() << ")";
    return os;
}
//=======================================================================================
template<typename T>
std::ostream & operator << (std::ostream &os, const VPolarPoint<T> &p )
{
    os << "(d=" << p.distance() << ",a=" << p.angle() << ")";
    return os;
}
//=======================================================================================
//      Streaming
//=======================================================================================


//=======================================================================================
//      IMPLEMENTATION VPoint
//=======================================================================================
//=======================================================================================
template<typename T>
VPoint<T>::VPoint()
    : VPoint( T(NAN), T(NAN) )
{}
//=======================================================================================
template<typename T>
VPoint<T>::VPoint( const T& xx, const T& yy )
    : _x(xx), _y(yy)
{}
//=======================================================================================
//=======================================================================================
template<typename T>
T VPoint<T>::x() const
{
    return _x;
}
//=======================================================================================
template<typename T>
T VPoint<T>::y() const
{
    return _y;
}
//=======================================================================================
template<typename T>
T VPoint<T>::distance() const
{
    return std::hypot( _x, _y );
}
//=======================================================================================
template<typename T>
T VPoint<T>::angle() const
{
    return std::atan2( _y, _x ); // Здесь Y и X НЕ ПЕРЕПУТАНЫ. См. документацию к atan2.
}
//=======================================================================================
template<typename T>
T VPoint<T>::angle_degrees() const
{
    return angle() * 180 / M_PI;
}
//=======================================================================================
template<typename T>
VPolarPoint<T> VPoint<T>::to_polar() const
{
    return { distance(), angle() };
}
//=======================================================================================
//=======================================================================================
template<typename T>
const VPoint<T> & VPoint<T>::operator +=( const VPoint<T> &rhs )
{
    _x += rhs._x;
    _y += rhs._y;
    return *this;
}
//=======================================================================================
template<typename T>
const VPoint<T> & VPoint<T>::operator -=( const VPoint<T>& rhs )
{
    _x -= rhs._x;
    _y -= rhs._y;
    return *this;
}
//=======================================================================================
template<typename T>
bool VPoint<T>::operator == ( const VPoint<T>& rhs ) const
{
    if ( !std::is_floating_point<T>::value )
    {
        return _x == rhs._x && _y == rhs._y;
    }
    else
    {
        auto xx = std::abs( _x - rhs._x );
        auto yy = std::abs( _y - rhs._y );

        return xx <= std::numeric_limits<T>::epsilon() &&
               yy <= std::numeric_limits<T>::epsilon();
    }
}
//=======================================================================================
template<typename T>
bool VPoint<T>::operator != ( const VPoint<T> &rhs ) const
{
    return !( *this == rhs );
}
//=======================================================================================
template<typename T>
T VPoint<T>::distance_to( const VPoint<T>& other ) const
{
    return (*this - other).distance();
}
//=======================================================================================
template<typename T>
bool VPoint<T>::is_valid() const
{
    return x() == x() &&    //  Проверки на NaN.
           y() == y();      //
}
//=======================================================================================
template<typename T>
VPoint<T> operator + ( const VPoint<T>& lhs, const VPoint<T>& rhs )
{
    auto tmp = lhs;
    return tmp += rhs;
}
//=======================================================================================
template<typename T>
VPoint<T> operator - ( const VPoint<T>& lhs, const VPoint<T>& rhs )
{
    auto tmp = lhs;
    return tmp -= rhs;
}
//=======================================================================================
//=======================================================================================
template<typename T>
typename VPolarPoint<T>::Vector VPoint<T>::Vector::to_polar() const
{
    typename VPolarPoint<T>::Vector res;
    res.reserve( this->size() );

    for ( auto && p: *this )
        res.push_back( p.to_polar() );

    return res;
}
//=======================================================================================
template<typename T>
VPoint<T> VPoint<T>::Vector::average_center() const
{
    // Чтобы потом на 0 не поделить.
    if ( this->empty() ) return {NAN, NAN};

    VPoint<T> init(0,0);
    auto acc = std::accumulate( this->cbegin(), this->cend(), init );
    return { acc.x()/this->size(), acc.y()/this->size() };
}
//=======================================================================================
//      IMPLEMENTATION VPoint
//=======================================================================================





//=======================================================================================
//      IMPLEMENTATION VPolarPoint
//=======================================================================================
template<typename T>
VPolarPoint<T>::VPolarPoint()
    : VPolarPoint( NAN, NAN )
{}
//=======================================================================================
template<typename T>
VPolarPoint<T>::VPolarPoint( const T& distance, const T& angle )
    : _distance ( distance )
    , _angle    ( angle    )
{}
//=======================================================================================
//=======================================================================================
template<typename T>
T VPolarPoint<T>::x() const
{
    return _distance * std::cos(_angle);
}
//=======================================================================================
template<typename T>
T VPolarPoint<T>::y() const
{
    return _distance * std::sin(_angle);
}
//=======================================================================================
template<typename T>
T VPolarPoint<T>::distance() const
{
    return _distance;
}
//=======================================================================================
template<typename T>
T VPolarPoint<T>::angle() const
{
    return _angle;
}
//=======================================================================================
template<typename T>
T VPolarPoint<T>::angle_degrees() const
{
    return angle() * 180 / M_PI;
}
//=======================================================================================
template<typename T>
VPoint<T> VPolarPoint<T>::to_cartesian() const
{
    return { x(), y() };
}
//=======================================================================================
template<typename T>
bool VPolarPoint<T>::operator == ( const VPolarPoint<T> &rhs ) const
{
    if ( !std::is_floating_point<T>::value )
    {
        return _distance == rhs._distance && _angle == rhs._angle;
    }
    else
    {
        auto d = std::abs( _distance - rhs._distance );
        auto a = std::abs( _angle - rhs._angle );

        return d < std::numeric_limits<T>::epsilon() &&
               a < std::numeric_limits<T>::epsilon();
    }
}
//=======================================================================================
template<typename T>
bool VPolarPoint<T>::operator != ( const VPolarPoint<T> &rhs ) const
{
    return !( *this == rhs );
}
//=======================================================================================
template<typename T>
T VPolarPoint<T>::distance_to( const VPolarPoint& other )
{
    auto d1 = _distance;
    auto d2 = other._distance;
    auto cos_a = std::cos( _angle - other._angle );

    return std::sqrt( d1*d1 + d2*d2 - 2 * d1 * d2 * cos_a );
}
//=======================================================================================
template<typename T>
bool VPolarPoint<T>::is_valid() const
{
    return distance() == distance() &&
           angle()    == angle();
}
//=======================================================================================
template<typename T>
typename VPoint<T>::Vector VPolarPoint<T>::Vector::to_cartesian() const
{
    typename VPoint<T>::Vector res;

    for ( auto & pp: *this )
        res.push_back( pp.to_cartesian() );

    return res;
}
//=======================================================================================
//      IMPLEMENTATION VPolarPoint
//=======================================================================================


#endif // VPOINTS_H
