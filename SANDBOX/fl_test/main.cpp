#include "mainwindow.h"
#include <QApplication>

//#include <Eigen/Dense>

#include <cmath>
#include <iostream>

#define fl_USE_DOUBLE
#include <fl/util/types.hpp>

#include <fl/model/transition/binary_transition_density.hpp>
#include <fl/distribution/decorrelated_gaussian.hpp>

fl::Real epsilon  = 0.000000000001;
fl::Real large_dt = 9999999999999.;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    fl::Real p_1to1 = 0.6;
    fl::Real p_0to1 = 0.3;
    fl::BinaryTransitionDensity density(p_1to1, p_0to1);

    fl::Real dt = 0.1;
    int N_steps = 10;
    fl::Real initial_p_1 = 0.5;

    fl::Real p_1 = initial_p_1;
    for(int i = 0; i < N_steps; i++)
    {
        // step-wise computation
        p_1 =     density.probability(1, 1, dt) * p_1
                + density.probability(1, 0, dt) * (1.-p_1);

        // direct computation
        fl::Real p_1_ =
                density.probability(1, 1, (i+1) * dt) * initial_p_1
              + density.probability(1, 0, (i+1) * dt) * (1.-initial_p_1);


        if (std::fabs(p_1 - p_1_) >= epsilon) throw std::runtime_error("ololo");
    }

    return a.exec();
}
