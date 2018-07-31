#ifndef VIZ_HPP
#define VIZ_HPP

#include "clusterizator.hpp"

#include "stereo_pair_builder.hpp"
#include "disparity_calculator.hpp"
#include "projection_creator.hpp"
#include "clusterizator.hpp"

#include <opencv2/core.hpp>
#include <list>

// Пространство имён содержащее функции трансформации данных для более удобной визуализации
namespace cv_viz
{
    void visualize_disparity( Disparity_calculator::Disparity disparity );
    void visualize_stereo_pair(
            Stereo_pair_builder::Stereo_pair pair , int saved_image_index=-1 );
    void visualize_projection( Projection_creator::Projection projection );
    void visualize_clusters_package( Clusterizator::Clusters_package clusters_package );
    void visualize_all_data( Clusterizator::Clusters_package clusters_package );

    void create_trackbars(Disparity_calculator* disparity_calculator_ptr,
            Projection_creator* projection_creator_ptr,
            Clusterizator* clusterizator_ptr,
            std::vector<int> default_values = {13} );

    // Функция создаёт из изображения в GRAYSCALE цветное изображение, где цвет пикселя соответствует нормализованному
    // значению первоначального изображения в цветовой палитре HSV
    // (теплый цвет - мин. значение, холодный цвет - макс. значение)
    void create_color_map( const cv::Mat& gray_img, cv::Mat& color_img );
    void display_clusters(
            cv::Mat& out , std::vector< Clusterizator::Cluster > &clusters, int pixels_on_meter,
            bool fill_color = false, bool display_blocks = false, bool display_distance = false );
}

#endif // VIZ_HPP
