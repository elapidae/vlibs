#include "vpolardbscan.h"


#include "vlogger.h"
#include "vdatetime.h"

//=======================================================================================
VPolDBScan::VPolDBScan( VPolDBScan::pol_vector points,
                        float max_angle,
                        float k_max_distance,
                        int min_cluster_size )
    : _max_angle( max_angle )
    , _k_max_distance( k_max_distance )
    , _min_cluster_size( min_cluster_size )
{
    assert(min_cluster_size > 0);

//    auto start_now = VDateTime::now();

    //vtrace(vlog("BEGIN"));
    std::sort( points.begin(), points.end(), _angle_cmp );

    //vtrace(vlog(1));
    while ( !points.empty() )
    {
        //vtrace(vlog("b while"));
        pol_vector cluster;
        cluster.push_back( points.back() );
        points.pop_back();


        for ( auto it = points.rbegin(); it != points.rend(); ++it )
        {
            bool in_beam;
            if ( !_in_cluster(cluster, *it, &in_beam) )
            {
                if ( !in_beam ) break;
                continue;
            }

            cluster.push_back( *it );
            points.erase( it.base() + 1 );
            it = points.rbegin();
        } // for all points to compare

        if ( cluster.size() >= _min_cluster_size )
            _clusters.push_back( std::move(cluster) );
        else
            _missed.insert( _missed.end(), cluster.begin(), cluster.end() );
    } // while ( !points.empty() )

//    auto elapsed = VDateTime::now() - start_now;
//    vtrace(vlog("pol db scan elapsed = ", elapsed.milliseconds(), "ms"));
}
//=======================================================================================
const VPolDBScan::pol_vector &VPolDBScan::missed() const
{
    return _missed;
}
//=======================================================================================
const VPolDBScan::cluster_vector &VPolDBScan::clusters() const
{
    return _clusters;
}
//=======================================================================================
bool VPolDBScan::_in_cluster( const VPolDBScan::pol_vector &cluster,
                              const VPolPoint &p,
                              bool *in_beam )
{
    *in_beam = false;
    for ( auto &cp: cluster )
    {
        auto delta_angle = std::abs( p.angle - cp.angle );
        if ( delta_angle > _max_angle )
            continue;
        else
            *in_beam = true;

        auto delta_distance = std::abs( p.distance - cp.distance );

        auto min_distance   = std::min( p.distance, cp.distance );
        if ( delta_distance > _k_max_distance * min_distance )
            continue;

        return true;
    }
    return false;
}
//=======================================================================================


