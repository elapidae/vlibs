#include "dnn.hpp"

namespace dnn
{

    Classificator::Classificator( void* model )
    {
    }

    Obstacle_prediction Classificator::classify( cv::Mat img )
    {
        return Obstacle_prediction( { Obstacle_class::UNKNOWN, 0.0 } );
    }

}
