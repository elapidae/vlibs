#include "data_agregator.hpp"

Data_agregator::Data_agregator()
    :
      does_stereo_pair_exist( false ),
      does_disparity_exist( false ),
      does_projection_exist( false ),
      does_cluster_package_exist( false ),
      does_disparity_calculator_exist( false ),
      does_projection_creator_exist( false ),
      does_clusterizator_exist( false )
{
}

void Data_agregator::agregate()
{
    mtx.lock();
    if ( !does_disparity_exist )
    {
        if ( does_stereo_pair_exist && does_disparity_calculator_exist )
        {
            disparity = disparity_calculator << pair;
            does_disparity_exist = true;
            vdeb << "disparity created...";
        }
    }

    if ( !does_projection_exist )
    {
        if ( does_disparity_exist && does_projection_creator_exist )
        {
            projection = projection_creator << disparity;
            does_projection_exist = true;
            vdeb << "projection created...";
        }
    }

    if ( !does_cluster_package_exist )
    {
        if ( does_projection_exist && does_clusterizator_exist )
        {
            cluster_package = clusterizator << projection;
            does_cluster_package_exist = true;
            vdeb << "clusters package created...";
        }
    }
    mtx.unlock();
}


Data_agregator& Data_agregator::update( Stereo_pair_builder::Stereo_pair pair )
{
    mtx.lock();
    this->pair = pair;
    cv::imwrite(std::string("left") + std::to_string(index) + std::string(".png"), this->pair.left.img);
    cv::imwrite(std::string("right") + std::to_string(index) + std::string(".png"), this->pair.right.img);
    index ++;
    does_stereo_pair_exist = true;
    does_disparity_exist = false;
    does_projection_exist = false;
    does_cluster_package_exist = false;
    mtx.unlock();
    return *this;
}

// Метод update для обновления преобразователей данных, если таковые потребуются
Data_agregator& Data_agregator::update( Disparity_calculator disparity_calculator )
{
    mtx.lock();
    this->disparity_calculator = disparity_calculator;
    does_disparity_calculator_exist = true;
    mtx.unlock();
    return *this;
}

Data_agregator& Data_agregator::update( Projection_creator projection_creator )
{
    mtx.lock();
    this->projection_creator = projection_creator;
    does_projection_creator_exist = true;
    mtx.unlock();
    return *this;
}

Data_agregator& Data_agregator::update( Clusterizator clusterizator )
{
    mtx.lock();
    this->clusterizator = clusterizator;
    does_clusterizator_exist = true;
    mtx.unlock();
    return *this;
}
