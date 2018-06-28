#ifndef VIZ_HPP
#define VIZ_HPP

#include <opencv2/core.hpp>

// Пространство имён содержащее функции трансформации данных для более удобной визуализации
namespace cv_viz
{
    // Функция создания проекции трехмерных точек на плоскость XZ, значение пикселя является нормированным значением Y
    void create_height_projections(
            const cv::Mat& img, const cv::Mat& points, cv::Mat &out, const int map_size = 600,
            const int cx = 0, const int cy = 0,
            const int y_min = 0, const int y_max = 0,
            const double scale = 1, const double alpha = 0 );

    // Функция создаёт из изображения в GRAYSCALE цветное изображение, где цвет пикселя соответствует нормализованному
    // значению первоначального изображения в цветовой палитре HSV
    // (теплый цвет - мин. значение, холодный цвет - макс. значение)
    void create_color_map( const cv::Mat& gray_img, cv::Mat& color_img );
}

#endif // VIZ_HPP
