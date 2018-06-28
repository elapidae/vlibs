#include "stereo_handler.hpp"

#include "vlog_pretty.h"

#include "vimagewidget.h"

#include "basler_zcm.h"
#include "vimage_zcm.h"
#include "vimage_opencv.h"
#include "vthread.h"

#include "calibration.hpp"
#include "viz.hpp"
#include "profiler.hpp"

#include <fstream>
#include <zcm/zcm-cpp.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/ximgproc.hpp>

#include <opencv2/viz/vizcore.hpp>


Stereo_Handler::Stereo_Handler(
        VImageWidget *left_w, VImageWidget *right_w, VImageWidget *disp_w,
        const std::string video_output_folder_path,
        const int pre_calibration_frames_count )
        :
          left_w( left_w ), right_w( right_w ), disp_w( disp_w ),
          video_output_path( video_output_folder_path ),
          pre_calibration_frames_count( pre_calibration_frames_count ),
          left_matcher( cv::StereoSGBM::create() )

{
    // Установка экспериментально выявленных оптимальных параметров для вычисления карты глубин
    // по-хорошему следует написать метода чтения данных параметров из файла(там же, где и калибровочные матрицы
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

    // Запись видео файла с полученной картой глубины
    // Выставлять частоту кадров и размерв зависимости от реальных параметров
    out_size = cv::Size( 612, 512 );
    original_size = cv::Size( 2448, 2048 );

    disp_video.open(
                video_output_folder_path + "disparity.avi",
                cv::VideoWriter::fourcc( 'X', 'V', 'I', 'D' ), 1, out_size );
    left_video.open(
                video_output_folder_path + "left.avi",
                cv::VideoWriter::fourcc( 'X', 'V', 'I', 'D' ), 1, original_size );
    right_video.open(
                video_output_folder_path + "right.avi",
                cv::VideoWriter::fourcc( 'X', 'V', 'I', 'D' ), 1, original_size );

    map_size = 600;
    map_video.open(
                "/home/user/height_map.avi", cv::VideoWriter::fourcc( 'X', 'V', 'I', 'D' ), 1,
                cv::Size( map_size, map_size ) );

    cv::namedWindow( "height_on_frame" );
    cv::createTrackbar( "neg Y", "height_on_frame", &neg_y_abs, 255, []( int, void* ){} );
    cv::createTrackbar( "pos Y", "height_on_frame", &pos_y_abs, 255, []( int, void* ){} );

    cv::namedWindow( "color_map" );
    cv::createTrackbar( "CX", "color_map", &cx, map_size, []( int, void* ){} );
    cv::createTrackbar( "CY", "color_map", &cy, map_size, []( int, void* ){} );
    cv::createTrackbar( "SCALE / 10", "color_map", &scale, 40, []( int, void* ){} );
    cv::createTrackbar( "ALPHA", "color_map", &alpha, 359, []( int, void* ){} );

    // Конфигурация матриц
    cv_calib::configure_calib_matrix( Q, leftMatX, leftMatY, rightMatX, rightMatY );
}

void Stereo_Handler::stereo_handle( const cv::Mat frame, const CAM_LOCATION location, const int64_t timestamp_ns )
{
    int64 t0 = cv::getTickCount();

    if ( location == CAM_LOCATION::LEFT )
    {
        last_left = { frame, timestamp_ns };
    }
    else if ( location == CAM_LOCATION::RIGHT )
    {
        last_right = { frame, timestamp_ns };
    }

    auto last_left_frame = last_left.frame;
    auto last_right_frame = last_right.frame;

    if ( last_left.timestamp_ns <= 0 || last_right.timestamp_ns <= 0 )
    {
        profiler::print_delay( t0, "Frame without pair." );
        return;
    }

    auto delay = fabs( last_left.timestamp_ns - last_right.timestamp_ns );
    if ( delay >= 0.3 )
    {
        vdeb << "Delay is too big(" << delay << ").";
        profiler::print_delay( t0, "" );

        return;
    }

    // set timestamp as 0 for excepting stereo handling with the same frames
    last_left.timestamp_ns = 0;
    last_right.timestamp_ns = 0;

    if ( pre_calibration_frames_count > 0 )
    {
        pre_calibration_frames_count --;

//        left_frames_calibrated_queue.push_back( last_left_frame );
//        right_frames_calibrated_queue.push_back( last_right_frame );
        cv::imwrite(std::string("left") + std::to_string(index) + ".png", last_left_frame);
        cv::imwrite(std::string("right") + std::to_string(index) + ".png", last_right_frame);
        index ++;

        profiler::print_delay( t0, "Calibration per frame done." );

        return;
    }
    else if ( pre_calibration_frames_count == 0 )
    {
        pre_calibration_frames_count --;
        cv_calib::create_calib_matrix( left_frames_calibrated_queue, right_frames_calibrated_queue );
        cv_calib::configure_calib_matrix( Q, leftMatX, leftMatY, rightMatX, rightMatY );
    }

    // Копирование для сжатия и последующей обработки алгоритмом стереозрения
    cv::cvtColor( last_left_frame, last_left_frame, cv::COLOR_BGR2GRAY );
    cv::cvtColor( last_right_frame, last_right_frame, cv::COLOR_BGR2GRAY );

    // Оптическое преобразование изображения для обработки алгоритмом стереозрения
    cv::remap( last_left_frame, last_left_frame, leftMatX, leftMatY, cv::INTER_CUBIC );
    cv::remap( last_right_frame, last_right_frame, rightMatX, rightMatY, cv::INTER_CUBIC );

    cv::Mat lc, rc;
    cv::cvtColor(last_left_frame, lc, cv::COLOR_GRAY2BGR);
    cv::cvtColor(last_right_frame, rc, cv::COLOR_GRAY2BGR);

    left_video.write( lc );
    right_video.write( rc );

    // Сжатие размера(в пикселях) изображения
    // Можно было использовать resize, но на практике pyrDown гораздо лучше решает проблему
    // Потери пикселей
    cv::pyrDown( last_left_frame, last_left_frame );
    cv::pyrDown( last_left_frame, last_left_frame );
    cv::pyrDown( last_right_frame, last_right_frame );
    cv::pyrDown( last_right_frame, last_right_frame );

    if ( !( last_left_frame.size()     == last_right_frame.size() &&
            last_left_frame.channels() == last_right_frame.channels() &&
            last_left_frame.channels() == 1/*3*/ ) )
    {
        vdeb << "Unchecked.";
        vdeb << "Left: "  << last_left_frame.size()  << last_left_frame.channels();
        vdeb << "Right: " << last_right_frame.size() << last_right_frame.channels();

        profiler::print_delay( t0, "" );
        return;
    }

    // Вычисление карты глубины в формате с плавающей точкой
    // На данном этапе данные должны использоваться для определения расстояния
    // И 3D реконструкции, после нормализации данные пригодны лишь для визуализации

    cv::Mat left_disp, right_disp, filtered_disp;
    left_matcher->compute( last_left_frame, last_right_frame, left_disp );
    right_matcher->compute( last_right_frame, last_left_frame, right_disp );

    wls_filter->filter( left_disp, last_left_frame, filtered_disp, right_disp );
    left_disp = filtered_disp;

    cv::Mat points;

    cv::resize(left_disp, left_disp, cv::Size(2448, 2048)); // жесткая привязка - плохо
    cv::reprojectImageTo3D( left_disp, points, Q, false );
    vdeb << "points size" << points.size();
    cv::Mat height_map, height_frame;

    height_frame = last_left_frame.clone();
    cv::pyrUp( height_frame, height_frame );
    cv::pyrUp( height_frame, height_frame );

    // viz code block
    cv_viz::create_height_projections(
                height_frame, points, height_map, map_size,
                cx, cy,
                -neg_y_abs, pos_y_abs,
                scale, alpha);
    cv_viz::create_color_map( height_map, height_map );
    cv::pyrDown( height_frame, height_frame );
    cv::pyrDown( height_frame, height_frame );
    cv::imshow( "height_on_frame", height_frame );

    cv::imshow("color_map", height_map);
    map_video.write(height_map);

    // Для визуализации
    cv::normalize( left_disp, left_disp, 0, 255, cv::NORM_MINMAX, CV_8UC1 );

    // Нормализация, конвертация цветов и визулизация с помощью Qt
    cv::cvtColor( left_disp, left_disp, cv::COLOR_GRAY2BGR );
    cv::resize( left_disp, left_disp, out_size );
    disp_video.write( left_disp );

    auto vcv = VImage_OpenCV( left_disp );
    auto img = VImage_Qt::convert( vcv.to_rgb888() );
    img.detach();
    qt::vinvoke_queue( disp_w, "set_image", Q_ARG( QImage, img ) );
    profiler::print_delay( t0, "Disparity calculated" );
}

void Stereo_Handler::left_handler( const zcm::ReceiveBuffer*, const std::string&, const ZCM_BaslerFrame *f )
{
    VImage_ZCM<ZCM_Image> zimg( f->image );

    // Конвертация для работы с кадром алгоритмами OpenCV
    auto frame = VImage_OpenCV::convert( zimg );
    stereo_handle_thread.cinvoke(
                this, &Stereo_Handler::stereo_handle,
                frame, Stereo_Handler::CAM_LOCATION::LEFT, f->timestamp_ns );

    // Конвертация для вывода в графический интерфейс через Qt
    auto img = VImage_Qt::convert( zimg );
    img.detach();
    qt::vinvoke_queue( left_w, "set_image", Q_ARG( QImage, img ) );
}

void Stereo_Handler::right_handler( const zcm::ReceiveBuffer*, const std::string&, const ZCM_BaslerFrame *f )
{
    VImage_ZCM<ZCM_Image> zimg( f->image );

    // Конвертация для работы с кадром алгоритмами OpenCV
    auto frame = VImage_OpenCV::convert( zimg );
    stereo_handle_thread.cinvoke(
                this, &Stereo_Handler::stereo_handle,
                frame, Stereo_Handler::CAM_LOCATION::RIGHT, f->timestamp_ns);

    // Конвертация для вывода в графический интерфейс через Qt
    // Был баг с конвертацией через временный объект VImage_OpenCV
    // Программа вылетала, конвертация цветов была верной, разобраться позже
    auto img = VImage_Qt::convert( zimg );
    img.detach();
    qt::vinvoke_queue( right_w, "set_image", Q_ARG( QImage, img ) );
}
