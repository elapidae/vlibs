#include "viz.hpp"

#include "clusterizator.hpp"

#include "stereo_pair_builder.hpp"
#include "disparity_calculator.hpp"
#include "projection_creator.hpp"
#include "clusterizator.hpp"

#include "ml.hpp"

#include "vlog_pretty.h"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

#include <list>

namespace cv_viz
{
    void visualize_stereo_pair(
            Stereo_pair_builder::Stereo_pair pair, int saved_image_index )
    {
        auto last_left_frame = pair.left.img;
        auto last_right_frame = pair.right.img;

        if ( saved_image_index >= 0 )
        {
            cv::imwrite( std::string( "left" ) + std::to_string( saved_image_index ) + ".png", last_left_frame );
            cv::imwrite( std::string( "right" ) + std::to_string( saved_image_index ) + ".png", last_right_frame );
        }
        cv::Mat left_small, right_small, concatenated;

        cv::pyrDown( last_left_frame,  left_small );
        cv::pyrDown( left_small,  left_small );

        cv::pyrDown( last_right_frame, right_small );
        cv::pyrDown( right_small, right_small );

        cv::hconcat( left_small, right_small, concatenated );
        cv::imshow( "stereo pair", concatenated );
    }
    void visualize_disparity( Disparity_calculator::Disparity disparity )
    {
        auto disp = disparity.disparity_mat;
        auto left_frame = disparity.left_remapped;
        auto right_frame = disparity.right_remapped;

        // Визуализация карты глубины в формате CV_8UC1 (монохромное 8-битное)
        auto viz_disp = disp.clone();
        cv::normalize( viz_disp, viz_disp, 0, 255, cv::NORM_MINMAX, CV_8UC1 );

        // Нормализация, конвертация цветов(для видеозаписи) и визулизация карты глубины
        cv::cvtColor( viz_disp, viz_disp, cv::COLOR_GRAY2BGR );
        cv::resize( viz_disp, viz_disp, cv::Size( 640, 480 ) );
        cv::imshow( "disp", viz_disp );

        // Визуализация склеенной сетереопары после ремаппинга и программной обработки изображений
        cv::Mat left_small, right_small, concatenated;

        cv::pyrDown( left_frame,  left_small );
        cv::pyrDown( left_small,  left_small );

        cv::pyrDown( right_frame, right_small );
        cv::pyrDown( right_small, right_small );
        cv::hconcat( left_small, right_small, concatenated );
        cv::imshow( "remapped pair", concatenated );
    }
    void visualize_projection( Projection_creator::Projection projection )
    {
        cv::Mat visualized_height;
        cv_viz::create_color_map( projection.height_on_frame_map, visualized_height );

        cv::Mat remapped_left_in_bgr;
        cv::cvtColor( projection.disparity.left_remapped, remapped_left_in_bgr, cv::COLOR_GRAY2BGR );
        cv::addWeighted( visualized_height, 0.5, remapped_left_in_bgr, 0.5, 0, visualized_height );

        cv::pyrDown( visualized_height, visualized_height );
        cv::imshow( "height on frame", visualized_height );

        cv::Mat zx;
        Clusterizator::create_average_matrix( projection.projections, zx );
        cv::imshow( "zx", zx );

    }
    void visualize_clusters_package( Clusterizator::Clusters_package clusters_package )
    {
        cv::Mat plane = cv::Mat::zeros(
                    clusters_package.projection.projections.front().size(),
                    CV_8UC3 );

        cv_viz::display_clusters(
                    plane, clusters_package.clusters, clusters_package.projection.how_much_pixels_in_meter,
                    false, true, true );
        cv::imshow( "Top down projection objects", plane );

    }
    void visualize_all_data( Clusterizator::Clusters_package clusters_package )
    {
        visualize_clusters_package( clusters_package );
        visualize_projection( clusters_package.projection );
        visualize_disparity( clusters_package.projection.disparity );
        visualize_stereo_pair( clusters_package.projection.disparity.original_pair );
    }

    void create_trackbars(
            Disparity_calculator* disparity_calculator_ptr,
            Projection_creator* projection_creator_ptr,
            Clusterizator* clusterizator_ptr,
            std::vector< int > default_values )
    {
        cv::namedWindow("Options");
        auto projection_lambda = []( int, void* ptr )
        {
            auto depth = cv::getTrackbarPos( "Depth", "Options" );
            auto width = cv::getTrackbarPos( "Width", "Options" );
            auto cx = cv::getTrackbarPos( "CX", "Options" );
            auto cy = cv::getTrackbarPos( "CY", "Options" );
            auto min_height = cv::getTrackbarPos( "Min height x10", "Options" );
            auto max_height = cv::getTrackbarPos( "Max height x10", "Options" );
            auto levels_count = cv::getTrackbarPos( "Levels count", "Options" );
            auto meteres_on_pixels_coef = cv::getTrackbarPos( "Meteres on pixel coef", "Options" );
            auto kernel_size = cv::getTrackbarPos( "Kernel size", "Options" );
            auto theta_x = cv::getTrackbarPos( "thetaX x1000", "Options" );
            auto theta_y = cv::getTrackbarPos( "thetaY x1000", "Options" );
            auto theta_z = cv::getTrackbarPos( "thetaZ x1000", "Options" );
            Projection_creator* projection_creator = (Projection_creator*)ptr;
            projection_creator->update_parameters(
                        width, depth,
                        float(min_height)/-10, float(max_height)/10,
                        levels_count, meteres_on_pixels_coef, kernel_size,
                        float( theta_x ) / 1000, float( theta_y ) / 1000, float( theta_z ) / 1000 );
        };
        auto clusterizator_lambda = []( int, void* ptr )
        {
            auto vertical_threshold = cv::getTrackbarPos( "Vertical threshold x100", "Options" );
            Clusterizator* clusterizator = (Clusterizator*)ptr;
            clusterizator->update_parameters( float( vertical_threshold ) / 100 );
        };

        cv::createTrackbar( "Depth", "Options", &default_values[0], 1000, projection_lambda, projection_creator_ptr );
        cv::createTrackbar( "Width", "Options", &default_values[1], 1000, projection_lambda, projection_creator_ptr );
        cv::createTrackbar( "CX", "Options", &default_values[2], 1000, projection_lambda, projection_creator_ptr );
        cv::createTrackbar( "CY", "Options", &default_values[3], 1000, projection_lambda, projection_creator_ptr );
        cv::createTrackbar( "Min height x10", "Options", &default_values[4], 100, projection_lambda, projection_creator_ptr );
        cv::createTrackbar( "Max height x10", "Options", &default_values[5], 100, projection_lambda, projection_creator_ptr );
        cv::createTrackbar( "Levels count", "Options", &default_values[6], 100, projection_lambda, projection_creator_ptr );
        cv::createTrackbar( "Meteres on pixel coef", "Options", &default_values[7], 1000, projection_lambda, projection_creator_ptr );
        cv::createTrackbar( "Kernel size", "Options", &default_values[8], 50, projection_lambda, projection_creator_ptr );
        cv::createTrackbar( "thetaX x1000", "Options", &default_values[9], 6282, projection_lambda, projection_creator_ptr );
        cv::createTrackbar( "thetaY x1000", "Options", &default_values[10], 6282, projection_lambda, projection_creator_ptr );
        cv::createTrackbar( "thetaZ x1000", "Options", &default_values[11], 6282, projection_lambda, projection_creator_ptr );
        cv::createTrackbar( "Vertical threshold x100", "Options", &default_values[12], 100, clusterizator_lambda, clusterizator_ptr );

    }

    void display_clusters(
            cv::Mat& out, std::vector< Clusterizator::Cluster >& clusters, int pixels_on_meter,
            bool fill_color, bool display_blocks, bool display_distance )
    {
        for( size_t i = 0; i < clusters.size(); i++ )
        {
            cv::Scalar color = cv::Scalar( 0, 0, 255 );
            std::vector< cv::Point2d > rect_points = clusters[i].bounding_rect;
            for ( int j = 0; j < 4; j++ )
            {
                cv::line( out, rect_points[j], rect_points[(j+1)%4], color, 2 );
            }
            if ( fill_color )
            {
            }
            if ( display_distance || true )
            {
                cv::Point2d closest_point;
                double closest_dist = 100000000;
                for ( int i = 0; i < 4; i++ )
                {
                    double dist = \
                            std::pow( rect_points[i].x - double(out.size().width) / 2, 2 ) + \
                            std::pow( rect_points[i].y - double(out.size().height), 2 );
                    dist = std::pow( dist, 0.5 );
                    if ( dist < closest_dist )
                    {
                        closest_dist = dist;
                        closest_point = rect_points[i];
                    }
                }
                cv::circle( out, closest_point, 3, cv::Scalar( 0, 255, 0 ), -1 );
                closest_dist /= pixels_on_meter;
                cv::putText( out, std::to_string( closest_dist ), closest_point, cv::FONT_HERSHEY_COMPLEX, 0.5,
                         cv::Scalar(0, 255, 0), 1, 8 );
            }
        }
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
