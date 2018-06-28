#ifndef STEREO_HANDLER_HPP
#define STEREO_HANDLER_HPP

#include "vimagewidget.h"
#include <zcm/zcm-cpp.hpp>

#include "basler_zcm.h"
#include "vthread.h"
#include "vimage_qt.h"
#include "qt_vinvoke.h"

#include <opencv2/opencv.hpp>
#include <opencv2/ximgproc.hpp>
#include <opencv2/viz/vizcore.hpp>

// Класс отвечающий за обработку изображений со стереопары
// для дальнейшего создания относительной карты глубины и облака точек в кадре, а также вывода изображений с камер.
// Кроме того в конструкторе для большего удобства заложена возможность автоматической калибровки пары
// путём показа под разными ракурсами N кадров с шахматной доской,
// где N является параметром pre_calibration_frames_count
class Stereo_Handler
{
public:
    Stereo_Handler(
            VImageWidget *left_w, VImageWidget *right_w, VImageWidget *disp_w,
            const std::string video_output_path,
            const int pre_calibration_frames_count = -1 );

    enum CAM_LOCATION
    {
        LEFT,
        RIGHT
    };

    struct Frame_with_ts
    {
        cv::Mat frame;
        size_t timestamp_ns;
    };

    // Метод проверяет наличие калибровочных матриц, наличие пары кадров, в случае успеха вычисляет карту глубины
    // картинки и выводит её на экран
    void stereo_handle( const cv::Mat frame, const CAM_LOCATION location, const int64_t timestamp_ns );

    // Захват и сохранение кадров с камер
    void left_handler ( const zcm::ReceiveBuffer*, const std::string&, const ZCM_BaslerFrame *f );
    void right_handler( const zcm::ReceiveBuffer*, const std::string&, const ZCM_BaslerFrame *f );

    // Функция создания калибровочных матриц из первых N кадров завхвата видеопотока
    // предполагается, что в случае создания экземпляра класса с данным ключем, в первых N кадрах
    // будет производиться калибровка камер с помощью шахматной доски
    void configure_calib_matrix();
    void create_calib_matrix();

private:
    // Окна для вывода изображений
    VImageWidget *left_w, *right_w, *disp_w;

    // Счётчик и контейнер для предварительной калибровки камеры
    int pre_calibration_frames_count;
    std::deque< cv::Mat > pre_calibration_frames_left;
    std::deque< cv::Mat > pre_calibration_frames_right;

    // Стереоматчер, матрицы калибровки стереопары, wls фильтр
    cv::Ptr< cv::StereoSGBM > left_matcher;
    cv::Ptr< cv::StereoMatcher > right_matcher;
    cv::Ptr< cv::ximgproc::DisparityWLSFilter > wls_filter;
    cv::Mat leftMatX, leftMatY;
    cv::Mat rightMatX, rightMatY;
    cv::Mat Q;

    // поток для обработки стереопары
    VThread stereo_handle_thread;

    // кадры для сохранения последних кадров камеры, использовать только в функции обработки стерео пары
    Frame_with_ts last_left, last_right;

    // Очереди для хранения кадров для калибровки, а также промежуточные матрицы калибровки
    std::list< cv::Mat > left_frames_calibrated_queue, right_frames_calibrated_queue;

    // Вывод видео
    cv::VideoWriter disp_video;
    cv::VideoWriter left_video;
    cv::VideoWriter right_video;
    std::string video_output_path;
    cv::Size out_size;
    cv::Size original_size;

    cv::VideoWriter map_video;

    // Интерфейс анализа реконструкции
    int map_size;
    int cx, cy, neg_y_abs, pos_y_abs, scale, alpha;
    int index = 0;

};

#endif // STEREO_HANDLER_HPP
