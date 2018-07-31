#ifndef ML_HPP
#define ML_HPP

#include <opencv2/opencv.hpp>
#include <vector>

namespace ml
{
    struct Obsatcle
    {
        int x, y;
    };

    void clusterize_points_3d(
            const cv::Mat& points, cv::Mat& cluster_mask,
            const double eps, const int min_samples );

    void quant_dbscan(
            const cv::Mat& mat, const double eps, const int min_samples );
}

#endif // ML_HPP
