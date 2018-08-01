#ifndef PROJECTION_CREATOR_HPP
#define PROJECTION_CREATOR_HPP

#include "disparity_calculator.hpp"
#include "vsignal.h"

#include <opencv2/opencv.hpp>

#include <vector>

class Projection_creator
{
public:
    struct Projection
    {
        Disparity_calculator::Disparity disparity;
        std::vector< cv::Mat > projections;
        cv::Mat height_on_frame_map;
        double min_height, max_height;
        int cx, cy;
        double angle;
        double how_much_pixels_in_meter;
    };

    Projection_creator(
            unsigned int roi_width = 10, unsigned int roi_depth = 10,
            double min_height = -10, double max_height = 10,
            unsigned int levels_count = 10, double how_much_pixels_in_meter = 10,
            double theta_x = 0, double theta_y = 0, double theta_z = 0 );

    Projection_creator( const Projection_creator& other )
    {
        *this = other;
    }
    Projection_creator& operator=( const Projection_creator& other )
    {
        roi_width = other.roi_width;
        roi_depth = other.roi_depth;
        min_height = other.min_height;
        max_height = other.max_height;
        levels_count = other.levels_count;
        how_much_pixels_in_meter = other.how_much_pixels_in_meter;
        kernel_size = other.kernel_size;
        theta_x = other.theta_x;
        theta_y = other.theta_y;
        theta_z = other.theta_z;

        return *this;
    }

    void update_parameters(
            unsigned int new_roi_width, unsigned int new_roi_depth,
            double new_min_height, double new_max_height,
            unsigned int new_levels_count, double new_meteres_to_pixels_coef, int new_kernel_size,
            double new_theta_x, double new_theta_y, double new_theta_z );

    VSignal< Projection > projection_received;

    void calculate_projections(
            Disparity_calculator::Disparity disparity );
    Projection operator<<( Disparity_calculator::Disparity disparity );
private:
    unsigned int roi_width, roi_depth;
    double min_height, max_height;
    unsigned int levels_count;
    double how_much_pixels_in_meter;
    int kernel_size;
    double theta_x, theta_y, theta_z;
};

#endif // PROJECTION_CREATOR_HPP
