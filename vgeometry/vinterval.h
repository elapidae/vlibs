//
// Created by claorisel on 11/15/18.
//

#ifndef LOCALIZATION_VINTERVAL_H
#define LOCALIZATION_VINTERVAL_H

#include "vpoints.h"
#include <eigen3/Eigen/Geometry>


template <typename Point>
class VInterval
{
public:
    using point_value_type = typename Point::value_type;

    VInterval();
    VInterval(const Point &p1, const Point &p2);

    point_value_type distance_to(const Point &p) const;
//    typename Point::value_type distance_to(const Point &p, bool *is_normal) const;
    point_value_type lenght() const;

    bool is_normal(const Point &p) const;

    Point projection(const Point &p) const;

private:
    Eigen::Matrix<point_value_type,1,2> _p1, _p2;
    Eigen::ParametrizedLine<point_value_type, 2> _line;
//    Point _p1, _p2;
};


template <typename Point>
VInterval<Point>::VInterval()
{}

template <typename Point>
VInterval<Point>::VInterval( const Point &p1, const Point &p2 )
    : _p1( p1.x(), p1.y() )
    , _p2( p2.x(), p2.y() )
    , _line( _p1, _p2 )
{}

template <typename Point>
typename Point::value_type
VInterval<Point>::distance_to(const Point &p) const
{}

template <typename Point>
typename Point::value_type
VInterval<Point>::lenght() const
{}

template <typename Point>
bool VInterval<Point>::is_normal(const Point &p) const
{}

template <typename Point>
Point VInterval<Point>::projection(const Point &p) const
{
    auto res = _line.projection( {p.x(), p.y()} );

    return { res.x(), res.y() };
}



#endif //LOCALIZATION_VINTERVAL_H
