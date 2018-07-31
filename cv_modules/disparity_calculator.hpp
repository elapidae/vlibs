#ifndef DISPARITY_CALCULATOR_HPP
#define DISPARITY_CALCULATOR_HPP

#include "stereo_pair_builder.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/ximgproc.hpp>

#include <string>

/***
 * Класс для вычисления карты глубины по синхронизированной стерео паре
 *
 * Конструктор принимает путь в файловой системе для чтения калибровочных матриц камер, а также размер изображения, необходимый
 * для инициализации фильтра карты глубины. Кроме того в конструкторе происходит установка параметров объекта алгоритмической
 * обработки стерепары. В дальнейшем при разработке следует вынести эти параметры и задавать их в конструкторе наиболее удобным способом.
 *
 * Класс определяет вспомогательную структура Disparity, которая содержит в себе структуру стереопары из класса Stereo_pair_builder
 * Кадры левой и правой камеры в формате матриц OpenCV после ремаппинга
 * Матрицу в формате OpenCV содержащую в себе объекты класса cv::Point3f содержащих в себе мировые коордаинаты точек кадра XYZ
 * в формате чисел с плавающей запятой. Ось Y является высотой относительно камеры, ось X смещением по горизонтали, ось Z глубиной(дальностью).
 *
 * Метод calculate принимет синхронизированную стереопару и вызывает дальнейший обработчик полученной карты глубины disparity_received.
 *
 * */
class Disparity_calculator
{
public:
    // Структура данных хранящая в себе оригинальную стереопару и различные результаты работы алгоритма обработки стереопары
    struct Disparity
    {
        Stereo_pair_builder::Stereo_pair original_pair;
        cv::Mat left_remapped;
        cv::Mat right_remapped;
        cv::Mat disparity_mat;
        cv::Mat points;
    };

    // Конструктор принимает путь в файловой системе к калибровочным матрицам и ожидаемый размер кадра
    // Матрицы должны быть приведены к размерности 1xN, значения в файле отделяются запятыми, каждая матрица имеет жесткую привязку к имени
    Disparity_calculator( std::string path_for_calib_matrix = "", cv::Size size = cv::Size( 0, 0 ) );
    Disparity_calculator( const Disparity_calculator& other )
    {
        *this = other;
    }
    Disparity_calculator& operator=( const Disparity_calculator& other )
    {
        Q = other.Q;
        leftMatX = other.leftMatX;
        leftMatY = other.leftMatY;
        rightMatX = other.rightMatX;
        rightMatY = other.rightMatY;

        left_matcher = other.left_matcher;
        right_matcher = other.right_matcher;
        wls_filter = other.wls_filter;

        disparity = other.disparity;

        return *this;
    }

    // Метод вызывается при успешном вычислении карты глубины и реконструкции точек в мировых координатах
    VSignal< Disparity > disparity_received;

    // Метод копирует стереопару и выполняет вычисление карты глубины и 3D реконструкцию точек в мировых координатах
    void calcualte( Stereo_pair_builder::Stereo_pair pair );
    Disparity operator<<( Stereo_pair_builder::Stereo_pair );

private:
    // Переменные калибровочных матриц, необходимы дял предварительной обработки изображения перед вычислением карты глубыны
    cv::Mat Q, leftMatX, leftMatY, rightMatX, rightMatY;

    // Классы стереоматчеров и фильтра карты глубины
    cv::Ptr< cv::StereoBM > left_matcher;
    cv::Ptr< cv::StereoMatcher > right_matcher;
    cv::Ptr< cv::ximgproc::DisparityWLSFilter > wls_filter;

    // Структура вычисленной карты глубины и других результатов работы алгоритма
    Disparity disparity;
};

#endif // DISPARITY_CALCULATOR_HPP
