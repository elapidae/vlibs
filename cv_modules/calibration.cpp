#include "calibration.hpp"

#include "vlog_pretty.h"

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>

namespace cv_calib {
    void use_calib_mtx_in_fs( cv::Mat &mtx, const std::string &file_name, std::_Ios_Openmode mode )
    {
        auto mtx_length = mtx.rows * mtx.cols;
        cv::Mat_< float > tmp_mat = cv::Mat_< float >( mtx.rows, mtx.cols );

        std::filebuf fb;
        std::stringstream error_msg;

        if ( fb.open( file_name, mode ) )
        {
            int i = 0;
            std::string string_value;

            if ( mode == std::ios::in )
            {
                std::istream is( &fb );

                while( std::getline( is, string_value, ',' )) // TODO \; read
                {
                    std::stringstream lexical_cast_os;
                    float tmp_float;
                    lexical_cast_os << string_value;
                    lexical_cast_os >> tmp_float;

                    if ( i >= mtx_length )
                    {
                        error_msg << "From file " << file_name << " read more values then size of matrix.";
                        throw( std::runtime_error( error_msg.str() ) );
                    }

                    tmp_mat.at< float >( i ) = tmp_float;
                    i ++;
                }
            }
            else if ( mode == std::ios::out )
            {
                std::ostream os( &fb );
                tmp_mat = mtx;
                for ( int i = 0; i < mtx.rows * mtx.cols; i ++ )
                {
                    if ( i == mtx.rows * mtx.cols - 1 )
                    {
                        os << mtx.at< float >( i );
                    }
                    else
                    {
                        os << mtx.at< float >( i ) << ",";
                    }
                }
            }

            fb.close();
        }
        else
        {
            error_msg << "File \"" << "leftProjection.csv\" " << "doesn't exist";
            throw( std::runtime_error( error_msg.str() ) );
        }

        mtx = tmp_mat;
    }

    Camera_Params calibrate_single_camera( const std::list<cv::Mat>& frames_queue )
    {
        cv::Mat camera_matrix = cv::Mat::eye( 3, 3, CV_64F );
        cv::Mat dist_coeffs = cv::Mat::eye( 3, 3, CV_64F );

        std::vector< cv::Mat > rvecs;
        std::vector< cv::Mat > tvecs;

        std::vector< cv::Point3f > object_points_grid( 49 );
        std::vector< std::vector< cv::Point3f > > object_points;
        std::vector< std::vector< cv::Point2f > > image_points;

        for ( int i = 0; i < 49; i ++ )
        {
            object_points_grid[i].x = i / 7;
            object_points_grid[i].y = i % 7;
            object_points_grid[i].z = 0;
        }

        int debug_prefix_name = 0;
        std::vector< cv::Point2f > corners;

        for ( auto& left_img : frames_queue )
        {
            cv::Mat gray;
            cv::cvtColor( left_img, gray, cv::COLOR_BGR2GRAY );
            bool ok;
            ok = cv::findChessboardCorners( gray, cv::Size( 7, 7 ), corners );

            if ( ok )
            {
                object_points.push_back( object_points_grid );
                cv::cornerSubPix( gray, corners,
                                  cv::Size( 11, 11 ),
                                  cv::Size( -1, -1 ), cv::TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
                image_points.push_back( corners );
                cv::Mat corners_debug_output = gray.clone();
                cv::drawChessboardCorners( corners_debug_output, cv::Size( 7, 7 ), corners, ok );
                cv::imwrite( std::to_string( debug_prefix_name ) + "_debug.png", corners_debug_output );
                debug_prefix_name ++;
            }
        }

        cv::Size size;
        size = frames_queue.front().size();

        object_points.resize( image_points.size(), object_points[0] );
        cv::calibrateCamera( object_points, image_points, size,
                             camera_matrix, dist_coeffs,
                             rvecs,
                             tvecs,
                             CV_CALIB_FIX_K4|CV_CALIB_FIX_K5 );

        return {
            object_points,
            image_points,
            camera_matrix,
            dist_coeffs,
            rvecs,
            tvecs
        };
    }

    void read_calib_matrix_from_files( cv::Mat& mtx, const std::string file_name )
    {
        use_calib_mtx_in_fs( mtx, file_name, std::ios::in );
    }

    void write_calib_matrix_from_files(cv::Mat& mtx, const std::string file_name )
    {
        use_calib_mtx_in_fs( mtx, file_name, std::ios::out );
    }

    // Есть идея переписать функцию с аргументами в виде итераторов, дабы не ограничивать себя
    // использованием одного лишь листа
    // Ещё стоит переписатб обе функции более грамотно, чтобы передавать имена файлов
    // сделать перегрузку для работы с матрицами и т. д. Но это требует отдельного обсуждения с пользователями
    // мне пока норм
    void create_calib_matrix(
            const std::list< cv::Mat >& left_frames_calibrated_queue,
            const std::list< cv::Mat >& right_frames_calibrated_queue )
    {
        // Сохранение калибровочных изображений с камер для логов
        int i = 0;
        for ( auto mat : left_frames_calibrated_queue )
        {
            cv::imwrite( std::string( "left" ) + std::to_string( i ) + ".png", mat );
            i ++;
        }

        i = 0;
        for ( auto& mat : right_frames_calibrated_queue )
        {
            cv::imwrite( std::string( "right" ) + std::to_string( i ) + ".png", mat );
            i ++;
        }
        return;

        vdeb << "calibrate left camera";
        auto left_params = calibrate_single_camera( left_frames_calibrated_queue );

        vdeb << "calibrate right camera";
        auto right_params = calibrate_single_camera( right_frames_calibrated_queue );

        cv::Size size;
        size = left_frames_calibrated_queue.front().size();

        cv::Mat R, T, E, F;

        vdeb << "calibrate stereo camera";
        cv::stereoCalibrate(
                    left_params.object_points,
                    left_params.image_points, right_params.image_points,
                    left_params.camera_matrix, left_params.dist_coeffs,
                    right_params.camera_matrix, right_params.dist_coeffs,
                    size, R, T, E, F
                    );

        cv::Mat R1, R2, P1, P2, Q;

        vdeb << "rectify stereo camera";
        cv::stereoRectify(
                    left_params.camera_matrix, left_params.dist_coeffs,
                    right_params.camera_matrix, right_params.dist_coeffs,
                    size, R, T, R1, R2, P1, P2, Q
                    );

        write_calib_matrix_from_files( left_params.dist_coeffs, "distL2.csv" );
        write_calib_matrix_from_files( left_params.camera_matrix, "mtxL2.csv" );
        write_calib_matrix_from_files( P1, "leftProjection2.csv" );
        write_calib_matrix_from_files( R1, "leftRectification2.csv" );

        write_calib_matrix_from_files( right_params.dist_coeffs, "distR2.csv" );
        write_calib_matrix_from_files( right_params.camera_matrix, "mtxR2.csv" );
        write_calib_matrix_from_files( P2, "rightProjection2.csv" );
        write_calib_matrix_from_files( R2, "rightRectification2.csv" );
    }

    void configure_calib_matrix(
            std::string path, cv::Size size,
            cv::Mat& Q,
            cv::Mat& leftMatX, cv::Mat& leftMatY,
            cv::Mat& rightMatX, cv::Mat& rightMatY )
    {
        Q = cv::Mat_< float >( 4, 4 );
        read_calib_matrix_from_files( Q, path + "Q.csv" );

        cv::Mat distL = cv::Mat_< float >( 1, 5 );
        cv::Mat leftProjection = cv::Mat_< float >( 3, 4 );
        cv::Mat leftRectification = cv::Mat_< float >( 3, 3 );
        cv::Mat mtxL = cv::Mat_< float >( 3, 3 );

        read_calib_matrix_from_files( distL, path + "distL.csv" );
        read_calib_matrix_from_files( leftProjection, path + "leftProjection.csv" );
        read_calib_matrix_from_files( leftRectification, path + "leftRectification.csv" );
        read_calib_matrix_from_files( mtxL, path + "mtxL.csv" );

        cv::Mat distR = cv::Mat_< float >( 1, 5 );
        cv::Mat rightProjection = cv::Mat_< float >( 3, 4 );
        cv::Mat rightRectification = cv::Mat_< float >( 3, 3 );
        cv::Mat mtxR = cv::Mat_< float >( 3, 3 );

        read_calib_matrix_from_files( distR, path + "distR.csv" );
        read_calib_matrix_from_files( rightProjection, path + "rightProjection.csv" );
        read_calib_matrix_from_files( rightRectification, path + "rightRectification.csv" );
        read_calib_matrix_from_files( mtxR, path + "mtxR.csv" );

        // Вычисление параметров для оптического преобразование кадров перед вычислением карты глубин
        cv::initUndistortRectifyMap(
                    mtxL, distL, leftRectification, leftProjection,
                    size, CV_32FC1, leftMatX, leftMatY );
        cv::initUndistortRectifyMap(
                    mtxR, distR, rightRectification, rightProjection,
                    size, CV_32FC1, rightMatX, rightMatY );
    }
}
