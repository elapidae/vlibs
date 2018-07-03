#include "stereo_pair_builder.hpp"

#include "vimage_opencv.h"
#include "vlog_pretty.h"

Stereo_pair_builder::Stereo_pair_builder()
    : frames_for_saving_count( 0 )
{
}

Stereo_pair_builder::Stereo_pair_builder( int frames_for_saving_count )
    : frames_for_saving_count( frames_for_saving_count )
{
}

Stereo_pair_builder::Stereo_pair_builder( int frames_for_saving_count , std::string path_for_saving )
    : frames_for_saving_count( frames_for_saving_count ),
      path_for_saving( path_for_saving )
{
}

void Stereo_pair_builder::make_pair( const Basler_GigE_Driver::ReceivedFrame& frame, CAM_LOCATION location )
{
    auto basler_frame = frame.frame.convert_mono8();
    VImage_Basler basler_img( basler_frame );

    auto cv_frame = VImage_OpenCV::convert( basler_img );

    if ( location == CAM_LOCATION::LEFT  ) last_left  = { cv_frame.clone(), VTimePoint(frame.frame.nano_sec()) };
    if ( location == CAM_LOCATION::RIGHT ) last_right = { cv_frame.clone(), VTimePoint(frame.frame.nano_sec()) };

    auto delay = abs( ( last_left.timestamp - last_right.timestamp ).milliseconds().count() );
    if ( !frame.freerun_synced || ( delay >= 1000 ) )
    {
        vdeb << "Delay is too big(" << delay << ")";
        vdeb << "LEFT  TS_NS(" << last_left.timestamp.nanoseconds() << ")";
        vdeb << "RIGHT TS_NS(" << last_right.timestamp.nanoseconds() << ")\n";
        return;
    }

    vdeb << "Stereo Pair creation";
    vdeb << "Delay is" << delay << "\n";

    pair_received( {last_left, last_right} );

    if ( frames_for_saving_count > 0 )
    {
        frames_for_saving_count --;
        cv::imwrite(
                    path_for_saving +
                    std::string( "Left" ) +
                    std::to_string( frames_for_saving_count ) +
                    std::string( ".png" ), last_left.img );
        cv::imwrite(
                    path_for_saving +
                    std::string( "Right" ) +
                    std::to_string( frames_for_saving_count ) +
                    std::string( ".png" ), last_right.img );
    }
    // Действия со стереопарой0
}
