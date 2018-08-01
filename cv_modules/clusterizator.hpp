#ifndef CLUSTERIZATOR_HPP
#define CLUSTERIZATOR_HPP

#include "dnn.hpp"
#include "projection_creator.hpp"

#include "vsignal.h"

#include <opencv2/opencv.hpp>
#include <vector>
#include <memory>

class Clusterizator
{
public:
    struct Cluster
    {
        std::vector< cv::Point2d > bounding_rect;
        dnn::Obstacle_prediction prediction;
    };

    struct Clusters_package
    {
        std::vector< Cluster > clusters;
        cv::Mat sixtels;
        Projection_creator::Projection projection;
    };

    Clusterizator( double threshold_value = 0.5, std::shared_ptr< dnn::Classificator > classificator = nullptr, int dataset_count = -1 );
    Clusterizator( const Clusterizator& other )
    {
        *this = other;
    }
    Clusterizator& operator=( const Clusterizator& other )
    {
        threshold_value = other.threshold_value;
        classificator = other.classificator;
        dataset_count = other.dataset_count;
        projection_morph_kernel = other.projection_morph_kernel;
        reprojection_morph_kernel = other.reprojection_morph_kernel;

        return *this;
    }

    // Метод вызывается для обработки полученных кластеров
    VSignal< Clusters_package > cluster_received;

    void find_clusters( Projection_creator::Projection projection );
    void update_parameters( double new_threshold_value );
    Clusters_package operator<<( Projection_creator::Projection projection );

    static void create_average_matrix(
            const std::vector< cv::Mat >& input_vector, cv::Mat& out, int iterations = 1, cv::Size kernel_size = cv::Size( 1, 1 ) );

    static int get_train_index();

private:
    double threshold_value;
    std::shared_ptr< dnn::Classificator > classificator;
    int dataset_count;
    cv::Mat projection_morph_kernel;
    cv::Mat reprojection_morph_kernel;
};

#endif // CLUSTERIZATOR_HPP
