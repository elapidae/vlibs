#ifndef NEAR_POINTS_H
#define NEAR_POINTS_H

#include "vpoint.h"


//=======================================================================================
/*
 * Edited 2018-01-25, changed VFloatPoint2D::Vector to VDecPoint::vector
 *
 *
 *  Near_Points::select( locality, sources, min_distance );
 *
 *
 *
*/
//=======================================================================================

class Near_Points
{
public:
    /// Возвращает точки из sources, находящиеся в окрестности min_distance от
    /// любой точки из набора locality.
    static VDecPoint::Vector select( const VDecPoint::Vector & locality,
                                     const VDecPoint::Vector & sources,
                                     float min_distance );
};

//=======================================================================================


#endif // NEAR_POINTS_H
