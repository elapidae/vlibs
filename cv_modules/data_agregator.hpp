#ifndef DATA_AGREGATOR_HPP
#define DATA_AGREGATOR_HPP

#include "stereo_pair_builder.hpp"
#include "disparity_calculator.hpp"
#include "projection_creator.hpp"
#include "clusterizator.hpp"

class Data_agregator
{
public:
    Data_agregator();
    void agregate();

    Data_agregator& update( Stereo_pair_builder::Stereo_pair pair );
    Data_agregator& update( Disparity_calculator disparity_calculator );
    Data_agregator& update( Projection_creator projection_creator );
    Data_agregator& update( Clusterizator clusterizator );

    bool does_stereo_pair_exist;
    Stereo_pair_builder::Stereo_pair pair;

    bool does_disparity_exist;
    Disparity_calculator::Disparity disparity;

    bool does_projection_exist;
    Projection_creator::Projection projection;

    bool does_cluster_package_exist;
    Clusterizator::Clusters_package cluster_package;

private:
    Disparity_calculator disparity_calculator;
    bool does_disparity_calculator_exist;

    Projection_creator projection_creator;
    bool does_projection_creator_exist;

    Clusterizator clusterizator;
    bool does_clusterizator_exist;
    std::mutex mtx;
    int index = 0;
};

#endif // DATA_AGREGATOR_HPP
