#ifndef DNN_HPP
#define DNN_HPP

#include <opencv2/opencv.hpp>

namespace dnn
{
    enum Obstacle_class
    {
        UNKNOWN = 0,
        HUMAN = 1,
        CAR = 2,
        TRAIN = 3
    };

    struct Obstacle_prediction
    {
        Obstacle_class label;
        double probability;
    };

    class Classificator
    {
    public:
        Classificator( void* model );
        Obstacle_prediction classify( cv::Mat img );
    };
}

#endif // DNN_HPP
