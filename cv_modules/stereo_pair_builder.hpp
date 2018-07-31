#ifndef STEREO_PAIR_BUILDER_HPP
#define STEREO_PAIR_BUILDER_HPP

#include "basler_gige_driver.h"
#include "vsignal.h"

#include <opencv2/opencv.hpp>

#include <string>

/***
 * Класс для формирования синхронизированной пары кадров от двух разных камер
 *
 * Вариации конструктора содержат опции для сохранения кадров в файловой системе для дальнейшего их использования
 * в процессе калибровки
 *
 * Класс определяет вспомогательные структуры данных для определения местоположения камер (левая или правая), привязки метки времени
 * к данным кадра в формате матрицы OpenCV и структуры содержащей пару кадров для дальнейшей обработки алгоритмами стереозрения
 *
 * Основные действия происходят в методе make_pair, который принимает кадр и метсоположение его камеры, выполняет проверку синхронизации
 * относительно последнего кадра, принятого с другой камеры и формирует структуру стереопары
 *
 ***/
class Stereo_pair_builder
{
public:
    // Относительное местоположение камеры
    enum CAM_LOCATION
    {
        LEFT,
        RIGHT
    };

    // Кадр в формате  матрицы OpenCV и временная метка
    struct Full_frame
    {
        cv::Mat img;
        VTimePoint timestamp;
        CAM_LOCATION location;
        bool freerun_synced;
    };

    // Структура данных для синхронизированной пары кадров
    struct Stereo_pair
    {
        Full_frame left;
        Full_frame right;
    };

    // При выборе данного конструтора кадры не будут сохраняться в файловой системе
    Stereo_pair_builder();

    // Метод вызывается при успешном создании стереопары
    VSignal< Stereo_pair > pair_received;

    // Метод формирования стереопары и вызова метода pair_received
    void make_pair(const Full_frame frame );

private:
    // Структуры последних принятых кадров от левой и правой камеры соответственно
    Full_frame last_left, last_right;
    int index = 0;
};

#endif // STEREO_PAIR_BUILDER_HPP
