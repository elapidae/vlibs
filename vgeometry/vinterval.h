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

    Point projection(const Point &p) const;

private:
    Point _p1, _p2;
    VLine<Point> _line;
};
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
bool VInterval<Point>::is_normal( const Point &p ) const
{
    auto pr = projection( p );

    auto mmx = std::minmax( _p1.x(), _p2.x() );
    auto mmy = std::minmax( _p1.y(), _p2.y() );

    return pr.x() >= mmx.first && pr.x() <= mmx.second &&
           pr.y() >= mmy.first && pr.y() <= mmy.second;
}
//=======================================================================================
template <typename Point>
Point VInterval<Point>::projection( const Point &p ) const
{
    return _line.projection( {p.x(), p.y()} );
}
//=======================================================================================



#endif //VINTERVAL_H
