#ifndef VPOLARDBSCAN_H
#define VPOLARDBSCAN_H

#include "vpoint.h"


//=======================================================================================
/* 2018-01-2x
 * Кластеризатор точек в полярных координатах.
 *
 *  [1]: Кластеризация производится по близости точек, используя следующие параметры:
 *
 *  max_angle -- угол захвата а радианах, точка может попасть в кластер, если разность
 *      ее угла и к-л точки в кластере будет <= указанного значения.
 *      Т.е. соблюдается неравенство abs(ak - ap) <= max_angle,
 *                   где ak -- угол точки в кластере, ap -- угол точки.
 *
 * k_max_distance -- коэффициент расстояния между точками. Точка попадет в кластер, если
 *      соблюдается неравенство min(dk, dp) * k_max_distance >= abs(dk, dp),
 *                  где dk -- расттояние точки в кластере, dp -- расстояние точки.
 *
 * min_cluster_size -- минимальное кол-во точек в кластере.
*/
//=======================================================================================



//=======================================================================================
class VPolDBScan
{
public:
    using pol_vector = VPolPoint::Vector;
    using cluster_vector = std::vector<pol_vector>;

    VPolDBScan( pol_vector points,                
                float max_angle,            // угол захвата, см. [1].
                float k_max_distance,       // коэф. расстояния, см. [1].
                int   min_cluster_size );   // минимальное кол-во точек в кластере.

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
//=======================================================================================



#endif // VPOLARDBSCAN_H
