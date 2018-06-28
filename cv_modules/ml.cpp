#include "ml.hpp"

#include <cmath>

namespace ml
{
//    void fill_cluster_mask( const cv::Mat& points, cv::Mat& cluster_mask, int x, int y, double eps )
//    {
//        if ( x < 0 || y < 0)
//        {
//            throw( std::logic_error( "X and Y must be non negative. Check your enter point." ) );
//        }

//        auto& pt = points.at< cv::Vec3f >( x, y );
//        auto& cluster_current_pt = cluster_mask.at< uchar >( x, y );

//        if ( x < points.cols - 1 )
//        {
//            auto& cluster_researched_pt = cluster_mask.at< uchar >( x + 1, y );
//            auto& researched_pt = points.at< cv::Vec3f >( x, y );
//            auto dist = \
//                    std::pow( pt[0] - researched_pt[0], 2 ) +
//                    std::pow( pt[1] - researched_pt[1], 2 ) +
//                    std::pow( pt[2] - researched_pt[2], 2 );
//            dist = std::pow( dist, 0.5);
//            cluster_researched_pt = dist < eps ? cluster_current_pt : cluster_researched_pt;
//            fill_cluster_mask( points, cluster_mask, x + 1, y, eps );
//        }
//        if ( y < points.rows - 1 )
//        {
//            auto& cluster_researched_pt = cluster_mask.at< uchar >( x, y + 1 );
//            auto& researched_pt = points.at< cv::Vec3f >( x, y );
//            auto dist = \
//                    std::pow( pt[0] - researched_pt[0], 2 ) +
//                    std::pow( pt[1] - researched_pt[1], 2 ) +
//                    std::pow( pt[2] - researched_pt[2], 2 );
//            dist = std::pow( dist, 0.5);
//            cluster_researched_pt = dist < eps ? cluster_current_pt : cluster_researched_pt;
//            fill_cluster_mask( points, cluster_mask, x, y + 1, eps );
//        }
//    }

//    void clusterize_points_3d(
//            const cv::Mat& points, cv::Mat& cluster_mask,
//            double eps, int min_samples )
//    {
//        cv::Mat new_mask = cv::Mat::zeros( points.size(), CV_8UC1 );
//        fill_cluster_mask( points, new_mask, 0, 0, eps );

//    }
}
