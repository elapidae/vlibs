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


#ifndef VLINE_H
#define VLINE_H

#include <assert.h>
#include "vpoints.h"


//=======================================================================================
template<typename Point>
class VLine
{
public:
    using point_value_type = typename Point::value_type;

    VLine();
    VLine( const Point& p1, const Point& p2 );

    bool is_valid() const;

    Point projection( const Point& other ) const;

private:
    point_value_type _a = NAN;
    point_value_type _b = NAN;
    point_value_type _c = NAN;
};
//=======================================================================================
using VlineF = VLine<VPointF>;
using VlineD = VLine<VPointD>;
//=======================================================================================



//=======================================================================================
template<typename Point>
VLine<Point>::VLine()
{}
//=======================================================================================
template<typename Point>
VLine<Point>::VLine( const Point& p1, const Point& p2 )
{
    _a = p1.y() - p2.y();
    _b = p2.x() - p1.x();
    _c = p1.x() * p2.y() - p2.x() * p1.y();
}
//=======================================================================================
template<typename Point>
bool VLine<Point>::is_valid() const
{
//    return true;
    return (_a != 0 || _b != 0) &&
           (_a == _a)           &&
           (_b == _b)           &&
           (_c == _c);
}
//=======================================================================================
template<typename Point>
Point VLine<Point>::projection( const Point& other ) const
{
    assert( is_valid() );

    auto a2_b2 = _a * _a + _b * _b;
    auto bx0 = _b * other.x();
    auto ay0 = _a * other.y();
    auto ac = _a * _c;
    auto bc = _b * _c;

    auto x = ( _b*(   bx0 - ay0 ) - ac ) / a2_b2;
    auto y = ( _a*( - bx0 + ay0 ) - bc ) / a2_b2;

    return { x, y };
}
//=======================================================================================

//template<typename Point>
//VLine<Point>::

#endif // VLINE_H
