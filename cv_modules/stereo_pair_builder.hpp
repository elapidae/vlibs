#ifndef STEREO_PAIR_BUILDER_HPP
#define STEREO_PAIR_BUILDER_HPP

#include "basler_gige_driver.h"
#include "vsignal.h"

#include <opencv2/opencv.hpp>

#include <string>


class Stereo_pair_builder
{
public:
    enum CAM_LOCATION
    {
        LEFT,
        RIGHT
    };

    struct Frame
    {
        cv::Mat img;
        VTimePoint timestamp;
    };

    struct Stereo_pair
    {
        Frame left;
        Frame right;
    };

    Stereo_pair_builder();
    Stereo_pair_builder( int frames_for_saving_count );
    Stereo_pair_builder( int frames_for_saving_count, std::string path_for_saving );

    VSignal<Stereo_pair> pair_received;

    void make_pair( const Basler_GigE_Driver::ReceivedFrame &frame, CAM_LOCATION location );

private:
    Frame last_left, last_right;
    int frames_for_saving_count;
    std::string path_for_saving;
};

#endif // STEREO_PAIR_BUILDER_HPP
