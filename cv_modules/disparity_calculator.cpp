#include "disparity_calculator.hpp"

#include "calibration.hpp"

Disparity_calculator::Disparity_calculator( std::string path_for_calib_matrix, cv::Size size )
    :
      left_matcher( cv::StereoSGBM::create() )
{
    left_matcher->setBlockSize( 5 );
    left_matcher->setMinDisparity( 0 );
    left_matcher->setNumDisparities( 64 );
    left_matcher->setDisp12MaxDiff( 255 );
    left_matcher->setSpeckleRange( 8 );
    left_matcher->setSpeckleWindowSize( 2048 );
    left_matcher->setP1( 90 );
    left_matcher->setP2( 384 );
    left_matcher->setPreFilterCap( 63 );
    left_matcher->setUniquenessRatio( 21 );
    left_matcher->setMode( cv::StereoSGBM::MODE_HH );

    right_matcher = cv::ximgproc::createRightMatcher( left_matcher );
    wls_filter = cv::ximgproc::createDisparityWLSFilter( left_matcher );

    wls_filter->setLambda( 20.1 );
    wls_filter->setSigmaColor( 0.1 );
    cv_calib::configure_calib_matrix( path_for_calib_matrix, size, Q, leftMatX, leftMatY, rightMatX, rightMatY );
}

void Disparity_calculator::calcualte( Stereo_pair_builder::Stereo_pair pair )
{
    auto left_frame = pair.left.img;
    auto right_frame = pair.right.img;

    cv::Mat remapped_left, remapped_right;

    cv::remap( left_frame, remapped_left, leftMatX, leftMatY, cv::INTER_CUBIC );
    cv::remap( right_frame, remapped_right, rightMatX, rightMatY, cv::INTER_CUBIC );

    cv::equalizeHist( remapped_left, remapped_left );
    cv::equalizeHist( remapped_right, remapped_right );

    if ( !( left_frame.size()     == right_frame.size() &&
            left_frame.channels() == right_frame.channels() &&
            left_frame.channels() == 1/*3*/ ) )
    {
        vdeb << "Different matrix params.";
        vdeb << "Left: "  << left_frame.size()  << left_frame.channels();
        vdeb << "Right: " << right_frame.size() << right_frame.channels();
    }

    // Вычисление карты глубины в формате с плавающей точкой
    // На данном этапе данные должны использоваться для определения расстояния
    // И 3D реконструкции, после нормализации данные пригодны лишь для визуализации
    left_frame = remapped_left.clone();
    right_frame = remapped_right.clone();

    cv::pyrDown( left_frame, left_frame );
    cv::pyrDown( right_frame, right_frame );

    cv::Mat left_disp, right_disp, filtered_disp;
    left_matcher->compute( left_frame, right_frame, left_disp );

    // Фитльтрация карты глубины
    right_matcher->compute( right_frame, left_frame, right_disp );

    wls_filter->filter( left_disp, left_frame, filtered_disp, right_disp );
    left_disp = filtered_disp;
    cv::pyrUp( left_disp, left_disp );

    cv::Mat points;
    cv::reprojectImageTo3D( left_disp, points, Q, false );

    disparity = { pair, remapped_left, remapped_right, left_disp, points };
    disparity_received( disparity );
}
