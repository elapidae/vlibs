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


//
// Created by claorisel on 11/15/18.
//
#ifndef VINTERVAL_H
#define VINTERVAL_H

#include "vline.h"
#include <algorithm>


//=======================================================================================
template <typename Point>
class VInterval
{
public:
    using point_value_type = typename Point::value_type;

    VInterval();
    VInterval( const Point &p1, const Point &p2 );

    point_value_type distance_to( const Point &p ) const;
    point_value_type length() const;

    bool is_normal( const Point &p ) const;
    bool in_rectangle( const Point &p ) const;

    Point projection( const Point &p ) const;

    point_value_type angle() const;
    point_value_type angle_degrees() const;

    //  Возвращает отрезок исходящий из текущего начала (start_point()), повернутый на
    //  angle радиан. Если указана отрицательная длина, то возвращается отрезок
    //  такой же длины как текущий.
    VInterval<Point> rotated( point_value_type angle, point_value_type len = -1 ) const;

    //  Возвращает отрезок той же длины из start_point() с углом angle() + Pi/2.
    //  Отрицательная длина => будет текущая длина отрезка.
    VInterval<Point> normal_1( point_value_type len = -1 ) const;
    //  Возвращает отрезок той же длины из start_point() с углом angle() - Pi/2.
    //  Отрицательная длина => будет текущая длина отрезка.
    VInterval<Point> normal_2( point_value_type len = -1 ) const;

    const Point& start_point()  const;
    const Point& end_point()    const;

private:
    Point _p1, _p2;
    VLine<Point> _line;
};
//=======================================================================================
using VIntervalF = VInterval<VPointF>;
using VIntervalD = VInterval<VPointD>;
//=======================================================================================


//=======================================================================================
template <typename Point>
VInterval<Point>::VInterval()
{}
//=======================================================================================
template <typename Point>
VInterval<Point>::VInterval( const Point &p1, const Point &p2 )
    : _p1( p1 )
    , _p2( p2 )
    , _line( p1, p2 )
{}
//=======================================================================================
template <typename Point> typename Point::value_type
VInterval<Point>::distance_to( const Point &p ) const
{
    assert(false);
}
//=======================================================================================
template <typename Point> typename Point::value_type
VInterval<Point>::length() const
{
    return _p1.distance_to( _p2 );
}
//=======================================================================================
template <typename Point>
bool VInterval<Point>::in_rectangle(const Point &p) const
{
    //  NB!!! Ни в коем случае не пользоваться функцией minmax!!!!!!!
    //  Она не работает! Там UB!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
    //auto mmx = std::minmax( _p1.x(), _p2.x() ); < -- так нельзя!!!!
    //auto mmy = std::minmax( _p1.y(), _p2.y() ); < -- так нельзя!!!!

    auto min_x = std::min( _p1.x(), _p2.x() );
    auto max_x = std::max( _p1.x(), _p2.x() );

    auto min_y = std::min( _p1.y(), _p2.y() );
    auto max_y = std::max( _p1.y(), _p2.y() );

    return min_x <= p.x() && p.x() <= max_x &&
           min_y <= p.y() && p.y() <= max_y;
}
//=======================================================================================
//=======================================================================================
template <typename Point>
bool VInterval<Point>::is_normal( const Point &p ) const
{
    auto pr = projection( p );

    return in_rectangle( pr );
}
//=======================================================================================
template <typename Point>
Point VInterval<Point>::projection( const Point &p ) const
{
    return _line.projection( {p.x(), p.y()} );
}
//=======================================================================================
template <typename Point> typename Point::value_type
VInterval<Point>::angle() const
{
    return (_p2 - _p1).angle();
}
//=======================================================================================
template <typename Point> typename Point::value_type
VInterval<Point>::angle_degrees() const
{
    return (_p2 - _p1).angle_degrees();
}
//=======================================================================================
template<typename Point>
const Point &VInterval<Point>::start_point() const
{
    return _p1;
}
//=======================================================================================
template<typename Point>
const Point &VInterval<Point>::end_point() const
{
    return _p2;
}
//=======================================================================================
//  1. Переносим отрезок в начало координат;
//  2. Выбираем правильную длину;
//  3. Через полярное представление разворачиваем на _a_ радиан;
//  4. Переносим конечную точку в верную позицию относительно стартовой;
//  5. Формируем и возвращаем повернутый отрезок.
template<typename Point>
VInterval<Point> VInterval<Point>::rotated( point_value_type a,
                                            point_value_type len ) const
{
    auto dv = _p2 - _p1;                                                        // [1]
    len = len > 0 ? len : dv.distance();                                        // [2]
    auto rotated_vector = VPolarPoint<point_value_type>( len, dv.angle() + a ); // [3]
    auto endpoint = rotated_vector.to_cartesian() + _p1;                        // [4]
    return { _p1, endpoint };                                                   // [5]
}
//=======================================================================================
template<typename Point>
VInterval<Point> VInterval<Point>::normal_1( point_value_type len ) const
{
    return rotated( + M_PI_2, len );
}
//=======================================================================================
template<typename Point>
VInterval<Point> VInterval<Point>::normal_2( point_value_type len ) const
{
    return rotated( - M_PI_2, len );
}
//=======================================================================================


#endif //VINTERVAL_H
