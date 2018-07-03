#ifndef DISPARITY_CALCULATOR_HPP
#define DISPARITY_CALCULATOR_HPP

#include "stereo_pair_builder.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/ximgproc.hpp>

#include <string>


class Disparity_calculator
{
public:
    struct Disparity
    {
        Stereo_pair_builder::Stereo_pair original_pair;
        cv::Mat left_remapped;
        cv::Mat right_remapped;
        cv::Mat disparity_mat;
        cv::Mat points;
    };
    Disparity_calculator( std::string path_for_calib_matrix , cv::Size size );
    void calcualte( Stereo_pair_builder::Stereo_pair pair );

    VSignal< Disparity > disparity_received;

private:
    cv::Mat Q, leftMatX, leftMatY, rightMatX, rightMatY;
    cv::Ptr< cv::StereoSGBM > left_matcher;
    cv::Ptr< cv::StereoMatcher > right_matcher;
    cv::Ptr< cv::ximgproc::DisparityWLSFilter > wls_filter;

    Disparity disparity;
};

#endif // DISPARITY_CALCULATOR_HPP
