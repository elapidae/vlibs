#ifndef ML_HPP
#define ML_HPP

#include <vector>
#include <opencv2/opencv.hpp>

namespace ml
{
    void clusterize_points_3d(
            const cv::Mat& points, cv::Mat& cluster_mask,
            const double eps, const int min_samples );
}

#endif // ML_HPP
