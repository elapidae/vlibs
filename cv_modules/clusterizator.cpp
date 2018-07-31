#include "clusterizator.hpp"

#include <vector>
#include <algorithm>

Clusterizator::Clusterizator( double threshold_value , std::shared_ptr<dnn::Classificator> classificator, int dataset_count )
    :
      threshold_value( threshold_value ),
      classificator( classificator ),
      dataset_count( dataset_count ),
      projection_morph_kernel( cv::getStructuringElement( cv::MORPH_RECT, cv::Size( 3, 3 ) ) ),
      reprojection_morph_kernel( cv::getStructuringElement( cv::MORPH_RECT, cv::Size( 11, 11 ) ) )
{

}


void Clusterizator::update_parameters(
        double new_threshold_value )
{
    threshold_value = new_threshold_value;
}

void Clusterizator::find_clusters( Projection_creator::Projection projection )
{
    cluster_received( operator <<( projection ) );
}


Clusterizator::Clusters_package Clusterizator::operator<<( Projection_creator::Projection projection )
{
    auto tmp_threshold_value = threshold_value;
    auto tmp_projection_morph_kernel = projection_morph_kernel;
    auto tmp_reprojection_morph_kernel = reprojection_morph_kernel;

    cv::Mat left_remapped = projection.disparity.left_remapped.clone();
    cv::Mat average_by_segments;
    create_average_matrix( projection.projections, average_by_segments, 1 );

    cv::Mat average_threshold;
    cv::inRange( average_by_segments, int( tmp_threshold_value * 255 ), 255, average_threshold );
    cv::morphologyEx(
        average_threshold, average_threshold, cv::MORPH_OPEN,
        tmp_projection_morph_kernel,
        cv::Point( -1, -1 ), 1 );
    cv::morphologyEx(
        average_threshold, average_threshold, cv::MORPH_CLOSE,
        tmp_projection_morph_kernel, cv::Point( -1, -1 ), 3 );
//    cv::imshow( "debug", average_threshold );

    std::vector< Cluster > clusters;
    std::vector< std::vector< cv::Point > > contours;
    cv::findContours( average_threshold, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
    // ограничение на 254 кластера, доделать
    int min_area = 10;
    for( size_t i = 0; i < contours.size(); i++ )
    {
        if ( cv::contourArea( contours[i] ) < min_area ) continue;

        auto bound_box = cv::minAreaRect( contours[i] );
        cv::Point2f rect_points[4];
        bound_box.points( rect_points );
        dnn::Obstacle_prediction prediction = { dnn::Obstacle_class::UNKNOWN, 0.0 };
        std::vector< cv::Point2d > rect_vector( { rect_points[0], rect_points[1], rect_points[2], rect_points[3] } );
        Cluster cluster = { rect_vector, prediction };
        clusters.push_back( cluster );

        auto cluster_id = clusters.size();
        cv::fillPoly( average_threshold, std::vector< std::vector< cv::Point > >( { contours[i] } ), cluster_id );
    }

    cv::Mat sixtel_map = cv::Mat::zeros( projection.disparity.left_remapped.size(), projection.disparity.left_remapped.type() );
    Clusters_package packages = { clusters, sixtel_map, projection };

    return packages;
}

void Clusterizator::create_average_matrix(
        const std::vector< cv::Mat >& input_vector, cv::Mat& out, int iterations, cv::Size kernel_size )
{
    int count = input_vector.size();
    out = cv::Mat::zeros( input_vector[0].size(), input_vector[0].type() );
    cv::Mat kernel = cv::getStructuringElement( cv::MORPH_RECT, kernel_size );
    for ( int i = 0; i < count; i ++ )
    {
        cv::dilate( input_vector[i], input_vector[i], kernel, cv::Point( -1, -1 ), iterations );
        cv::addWeighted( out, 1.0*i / (i + 1), input_vector[i], 1.0 / (i + 1), 0, out );
    }
}
