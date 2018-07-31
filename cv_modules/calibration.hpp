#ifndef CALIBRATION_HPP
#define CALIBRATION_HPP

#include <opencv2/core.hpp>

#include <list>
#include <vector>

#include <string>
#include <ios>

// Пространство имён содержащее структуру данных для хранения параметров калибровки, а также функции
// для непосредственной калибровки
namespace cv_calib
{
    // Структура параметров камеры содержащая поля необходимых для калибровки матриц и векторов
    struct Camera_Params
    {
        std::vector< std::vector< cv::Point3f > > object_points;
        std::vector< std::vector< cv::Point2f > > image_points;
        cv::Mat camera_matrix;
        cv::Mat dist_coeffs;
        std::vector< cv::Mat > rvecs;
        std::vector< cv::Mat > tvecs;

    };

    // Функция возвращающая структуру параметров камеры по списку изображений с шахматной доской
    Camera_Params calibrate_single_camera( const std::list<cv::Mat> &frames_queue );

    // Функция читающая/записывающая матрицу в файл
    void use_calib_mtx_in_fs( cv::Mat& mtx, const std::string& file_name, std::_Ios_Openmode mode );
    void read_calib_matrix_from_files( cv::Mat& mtx, const std::string file_name );
    void write_calib_matrix_from_files( cv::Mat& mtx, const std::string file_name );
    void configure_calib_matrix(
            std::string path, cv::Size size,
            cv::Mat& Q,
            cv::Mat& leftMatX, cv::Mat& leftMatY,
            cv::Mat& rightMatX, cv::Mat& rightMatY);
    void create_calib_matrix(
            const std::list< cv::Mat >& left_frames_calibrated_queue,
            const std::list< cv::Mat >& right_frames_calibrated_queue );
}

#endif // CALIBRATION_HPP
