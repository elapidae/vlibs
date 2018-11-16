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
    VInterval(const Point &p1, const Point &p2);

    point_value_type distance_to(const Point &p) const;
//    typename Point::value_type distance_to(const Point &p, bool *is_normal) const;
    point_value_type length() const;

    bool is_normal(const Point &p) const;
    bool in_rectangle(const Point &p) const;

    Point projection(const Point &p) const;

    point_value_type angle() const;

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
    //auto mmx = std::minmax( _p1.x(), _p2.x() );
    //auto mmy = std::minmax( _p1.y(), _p2.y() );
    auto min_x = _p1.x() < _p2.x() ? _p1.x() : _p2.x();
    auto max_x = _p1.x() > _p2.x() ? _p1.x() : _p2.x();
    auto min_y = _p1.y() < _p2.y() ? _p1.y() : _p2.y();
    auto max_y = _p1.y() > _p2.y() ? _p1.y() : _p2.y();

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
    auto dp = _p1 - _p2;
    return dp.angle();
}
//=======================================================================================


#endif //VINTERVAL_H
