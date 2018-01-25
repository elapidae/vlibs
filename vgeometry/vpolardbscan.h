#ifndef VPOLARDBSCAN_H
#define VPOLARDBSCAN_H

#include "vpoint.h"


class VPolDBScan
{
public:
    using pol_vector = VPolPoint::Vector;
    using cluster_vector = std::vector<pol_vector>;

    VPolDBScan( pol_vector points,
                float max_angle,
                float k_max_distance,
                int min_cluster_size ); // ctor

    const cluster_vector& clusters() const;
    const pol_vector& missed()       const;


private:
    pol_vector _missed;
    cluster_vector _clusters;
    float _max_angle;
    float _k_max_distance;
    uint  _min_cluster_size;


    static bool _angle_cmp( const VPolPoint &p1, const VPolPoint &p2 )
    { return p1.angle < p2.angle; }

    bool _in_cluster( const pol_vector &cluster, const VPolPoint &p, bool *not_in_beam );
};



#endif // VPOLARDBSCAN_H
