#include "near_points.h"


//=======================================================================================
VDecPoint::Vector Near_Points::select( const VDecPoint::Vector &locality,
                                       const VDecPoint::Vector &sources,
                                       float min_distance )
{
    VDecPoint::Vector res;

    for ( auto & s: sources )
    {
        for ( auto & n: locality )
        {
            if ( n.distance_to(s) <= min_distance )
            {
                res.push_back( s );
                break;
            }
        } // for all nears
    } // for all sources

    return move(res);
}
//=======================================================================================
