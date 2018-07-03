#include "viz.hpp"

#include "vlog_pretty.h"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

#include <list>

#include "ml.hpp"

namespace cv_viz
{
    void create_height_projections(
            const cv::Mat &frame, const cv::Mat &points, const int map_size,
            const int cx, const int cy,
            const int y_min, const int y_max,
            const double scale, const double alpha )
    {
        if (frame.size() == cv::Size(0, 0))
        {
            vdeb << "frame is empty";
            return;
        }
        double real_scale = scale / 10;
        double data_x_max, data_y_max, data_z_max;
        double data_x_min, data_y_min, data_z_min;
        data_x_max = data_y_max = data_z_max = -1 * (unsigned int)-1;
        data_x_min = data_y_min = data_z_min = (unsigned int)-1;

        cv::Mat height_on_frame_mask = cv::Mat::zeros( frame.size(), frame.type() );

        for( int i = 0; i < points.rows; i++ )
        {
            for( int j = 0; j < points.cols; j++ )
            {
                if( points.at< cv::Vec3f >( i, j )[2] > 0 &&
                    points.at< cv::Vec3f >( i, j )[2] < 1000 ) // исправить жесткую привязку
                {
                    double x = points.at< cv::Vec3f >( i, j )[0];
                    double y = points.at< cv::Vec3f >( i, j )[1];
                    double z = points.at< cv::Vec3f >( i, j )[2];

                    data_x_max = x > data_x_max ? x : data_x_max;
                    data_y_max = y > data_y_max ? y : data_y_max;
                    data_z_max = z > data_z_max ? z : data_z_max;

                    data_x_min = x < data_x_min ? x : data_x_min;
                    data_y_min = y < data_y_min ? y : data_y_min;
                    data_z_min = z < data_z_min ? z : data_z_min;
                }
            }
        }

        // TODO DEBUG FLAG
        vdeb << "X range coord in stereo recunstructed points: " << data_x_min << "; " << data_x_max << "\n";
        vdeb << "Y range coord in stereo recunstructed points: " << data_y_min << "; " << data_y_max << "\n";
        vdeb << "Z range coord in stereo recunstructed points: " << data_z_min << "; " << data_z_max << "\n";

        cv::Mat ZX = cv::Mat::zeros( map_size+1, map_size+1, CV_8U );

        // Создаём проекцию вида сверху
        for ( int i = 0; i < points.rows; i++ )
        {
            for ( int j = 0; j < points.cols; j++ )
            {
                if ( points.at< cv::Vec3f >( i, j )[2]*real_scale < map_size - cy &&
                     points.at< cv::Vec3f >( i, j )[2]*real_scale > -cy &&
                     points.at< cv::Vec3f >( i, j )[0]*real_scale < map_size - cx &&
                     points.at< cv::Vec3f >( i, j )[0]*real_scale > -cx &&
                     points.at< cv::Vec3f >( i, j )[1] < y_max &&
                     points.at< cv::Vec3f >( i, j )[1] > y_min )
                {
                    double x_double = ( points.at< cv::Vec3f >( i, j )[0]*real_scale + cx );
                    double y_double = ( points.at< cv::Vec3f >( i, j )[1] - y_min ) / ( y_max - y_min );
                    double z_double = ( points.at< cv::Vec3f >( i, j )[2]*real_scale + cy );

                    y_double *= map_size;

                    int x = x_double;
                    int y = y_double;
                    int z = z_double;

                    ZX.at< uchar >( map_size - z, x ) = \
                            (uchar)(y * 1.0 / map_size * 255.0) > 50 ? (uchar)(y * 1.0 / map_size * 255.0) : 0;
                    height_on_frame_mask.at< uchar >( i, j ) = \
                            (uchar)(y * 1.0 / map_size * 255.0) > 50 ? (uchar)(y * 1.0 / map_size * 255.0) : 0;
                }
            }
        }

        // Выделяем на кадре точки по высоте
        create_color_map( height_on_frame_mask, height_on_frame_mask );

        auto new_img = frame.clone();
        cv::cvtColor( new_img, new_img, cv::COLOR_GRAY2BGR );
        cv::addWeighted( new_img, 0.5, height_on_frame_mask, 0.5, 0, new_img );
        cv::resize( new_img, new_img, cv::Size( 640, 480 ) );
        cv::imshow( "height_on_frame", new_img );


        // Вращаем и изменяем масштаб преокции вида сверху
        cv::Mat lower_mask;
        cv::inRange( ZX, 0, 30, lower_mask );
        create_color_map( ZX, ZX );
        cv::bitwise_and( ZX, ZX, ZX, lower_mask );
        cv::circle( ZX, cv::Point( cx, map_size - cy ), 3, cv::Scalar( 255 ));
        cv::Mat rot_mat( 2, 3, CV_32FC1 );
        rot_mat = cv::getRotationMatrix2D( cv::Point( cx, map_size - cy ), alpha, 1 );
        cv::warpAffine( ZX, ZX, rot_mat, ZX.size(), cv::INTER_NEAREST );

        cv::imshow("ZX", ZX);
    }

    void create_color_map( const cv::Mat &gray_img, cv::Mat& color_img )
    {
        auto degress = gray_img.clone();
        cv::normalize( degress, degress, 0, 179, cv::NORM_MINMAX );
        cv::Mat value_mask;
        cv::inRange( degress, 1, 179, value_mask );

        std::vector< cv::Mat > hsv_vector = {
            degress,
            cv::Mat( gray_img.size(), CV_8U, cv::Scalar(255) ),
            value_mask
        };
        cv::Mat hsv;
        cv::merge( hsv_vector, hsv );
        cv::cvtColor( hsv, color_img, cv::COLOR_HSV2BGR );
    }
}
