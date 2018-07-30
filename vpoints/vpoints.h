#ifndef VPOINTS_H
#define VPOINTS_H

#include "vbufferforwardreader.h"
#include "vstring.h"
#include <vector>
#include <algorithm>
#include <ostream>

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
 *  а полярные -- x() и y().
 *
 *  Декартовы обладают методом to_polar(), полярные -- to_cartesian() (это декартовы
 *  по буржуйски).
 *
 *  Умеют писать и читать себя из VString и VBufferForwardReader
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

    static VPoint<T> from_back_LE( VString * buf );
    static VPoint<T> from_back_BE( VString * buf );

    static VPoint<T> from_reader_LE( VBufferForwardReader * buf );
    static VPoint<T> from_reader_BE( VBufferForwardReader * buf );

    void to_back_LE( VString * buf ) const;
    void to_back_BE( VString * buf ) const;

    VPoint();
    VPoint( const T& xx, const T& yy );

    T x()           const;
    T y()           const;
    T distance()    const;
    T angle()       const;

    T& ref_x();
    T& ref_y();

    VPolarPoint<T> to_polar() const;

    const VPoint<T> & operator += ( const VPoint<T> &rhs );
    const VPoint<T> & operator -= ( const VPoint<T> &rhs );

    T distance_to( const VPoint<T> & other ) const;

    bool is_valid() const                           { return x() == x() && y() == y(); }

    // Конвертирует в указанный тип, если у типа есть соответствующий конструктор.
    //template<typename Dst>
    //Dst convert_to_any() const                      { return {x(), y()}; }


    class Vector : public std::vector<VPoint<T>>
    {
    public:
        using std::vector<VPoint<T>>::vector;

        typename VPolarPoint<T>::Vector to_polar() const;
        VPoint<T> average_center() const;
    };


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

    static VPolarPoint<T> from_back_LE( VString * buf );
    static VPolarPoint<T> from_back_BE( VString * buf );

    static VPolarPoint<T> from_reader_LE( VBufferForwardReader * buf );
    static VPolarPoint<T> from_reader_BE( VBufferForwardReader * buf );

    void to_back_LE( VString * buf ) const;
    void to_back_BE( VString * buf ) const;

    VPolarPoint();
    VPolarPoint( const T& distance, const T& angle );

    T x()           const;
    T y()           const;
    T distance()    const;
    T angle()       const;

    VPoint<T> to_cartesian() const;

    T distance_to( const VPolarPoint & other )
    { return to_cartesian().distance_to(other.to_cartesian()); }

    bool is_valid() const
    { return distance() == distance() && angle() == angle(); }

    class Vector : public std::vector<VPolarPoint<T>>
    {
    public:
        typename VPoint<T>::Vector to_cartesian() const;
    };


private:
    T _distance, _angle;
}; // VPolarPoint class
//=======================================================================================
using VPolarPointF = VPolarPoint<float>;
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
template<typename T>
VPoint<T> VPoint<T>::from_back_LE( VString * buf )
{
    auto y = buf->take_back_LE<T>();
    auto x = buf->take_back_LE<T>();
    return { x, y };
}
//=======================================================================================
template<typename T>
VPoint<T> VPoint<T>::from_back_BE( VString * buf )
{
    auto y = buf->take_back_BE<T>();
    auto x = buf->take_back_BE<T>();
    return { x, y };
}
//=======================================================================================
template<typename T>
VPoint<T> VPoint<T>::from_reader_LE( VBufferForwardReader * buf )
{
    auto xx = buf->take_LE<T>();
    auto yy = buf->take_LE<T>();
    return { xx, yy };
}
//=======================================================================================
template<typename T>
VPoint<T> VPoint<T>::from_reader_BE( VBufferForwardReader * buf )
{
    auto xx = buf->take_BE<T>();
    auto yy = buf->take_BE<T>();
    return { xx, yy };
}
//=======================================================================================
template<typename T>
void VPoint<T>::to_back_LE( VString * buf ) const
{
    buf->append_LE( x() );
    buf->append_LE( y() );
}
//=======================================================================================
template<typename T>
void VPoint<T>::to_back_BE( VString * buf ) const
{
    buf->append_BE( x() );
    buf->append_BE( y() );
}
//=======================================================================================
//=======================================================================================
template<typename T>
VPoint<T>::VPoint()
    : VPoint( NAN, NAN )
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
T &VPoint<T>::ref_x()
{
    return _x;
}
//=======================================================================================
template<typename T>
T &VPoint<T>::ref_y()
{
    return _y;
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
const VPoint<T> & VPoint<T>::operator -=( const VPoint<T> &rhs )
{
    _x -= rhs._x;
    _y -= rhs._y;
    return *this;
}
//=======================================================================================
template<typename T>
T VPoint<T>::distance_to( const VPoint<T> & other ) const
{
    return (*this - other).distance();
}
//=======================================================================================
//=======================================================================================
template<typename T>
VPoint<T> operator + ( const VPoint<T> &lhs, const VPoint<T> &rhs )
{
    auto tmp = lhs;
    return tmp += rhs;
}
//=======================================================================================
template<typename T>
VPoint<T> operator - ( const VPoint<T> &lhs, const VPoint<T> &rhs )
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

    T sx = 0;
    T sy = 0;
    for ( auto && p: *this )
    {
        sx += p.x();
        sy += p.y();
    }
    return { sx/this->size(), sy/this->size() };
}
//=======================================================================================
//      IMPLEMENTATION VPoint
//=======================================================================================





//=======================================================================================
//      IMPLEMENTATION VPolarPoint
//=======================================================================================
template<typename T>
VPolarPoint<T> VPolarPoint<T>::from_back_LE( VString * buf )
{
    auto angle = buf->take_back_LE<T>();
    auto dist  = buf->take_back_LE<T>();
    return { dist, angle };
}
//=======================================================================================
template<typename T>
VPolarPoint<T> VPolarPoint<T>::from_back_BE( VString * buf )
{
    auto angle = buf->take_back_BE<T>();
    auto dist  = buf->take_back_BE<T>();
    return { dist, angle };
}
//=======================================================================================
template<typename T>
VPolarPoint<T> VPolarPoint<T>::from_reader_LE( VBufferForwardReader * buf )
{
    auto angle = buf->take_LE<T>();
    auto dist  = buf->take_LE<T>();
    return { dist, angle };
}
//=======================================================================================
template<typename T>
VPolarPoint<T> VPolarPoint<T>::from_reader_BE( VBufferForwardReader * buf )
{
    auto angle = buf->take_BE<T>();
    auto dist  = buf->take_BE<T>();
    return { dist, angle };
}
//=======================================================================================
template<typename T>
void VPolarPoint<T>::to_back_LE( VString * buf ) const
{
    buf->append_LE( _distance );
    buf->append_LE( _angle    );
}
//=======================================================================================
template<typename T>
void VPolarPoint<T>::to_back_BE( VString * buf ) const
{
    buf->append_BE( _distance );
    buf->append_BE( _angle    );
}
//=======================================================================================
//=======================================================================================
template<typename T>
VPolarPoint<T>::VPolarPoint()
    : VPolarPoint(NAN, NAN)
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
    return _distance * cos(_angle);
}
//=======================================================================================
template<typename T>
T VPolarPoint<T>::y() const
{
    return _distance * sin(_angle);
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
VPoint<T> VPolarPoint<T>::to_cartesian() const
{
    return { x(), y() };
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
