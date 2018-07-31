
isEmpty(qi_cv_modules) {
    qi_cv_modules = 1;
    isEmpty(qi_not_print_pri_messages): message("=== cv_modules appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    include( $$VLibs_Dir/vimage/vimage.pri )
    include( $$VLibs_Dir/vimage/vimage_opencv.pri )
    include( $$VLibs_Dir/vopencv/vopencv.pri )
    include( $$VLibs_Dir/vlog/vlog.pri )

    !contains(CONFIG, c++11): CONFIG += c++11

    INCLUDEPATH += $$VLibs_Dir/cv_modules

    HEADERS     += $$VLibs_Dir/cv_modules/calibration.hpp
    SOURCES     += $$VLibs_Dir/cv_modules/calibration.cpp

    HEADERS     += $$VLibs_Dir/cv_modules/viz.hpp
    SOURCES     += $$VLibs_Dir/cv_modules/viz.cpp

    HEADERS     += $$VLibs_Dir/cv_modules/ml.hpp
    SOURCES     += $$VLibs_Dir/cv_modules/ml.cpp

    HEADERS     += $$VLibs_Dir/cv_modules/stereo_pair_builder.hpp
    SOURCES     += $$VLibs_Dir/cv_modules/stereo_pair_builder.cpp

    HEADERS     += $$VLibs_Dir/cv_modules/disparity_calculator.hpp
    SOURCES     += $$VLibs_Dir/cv_modules/disparity_calculator.cpp

    HEADERS     += $$VLibs_Dir/cv_modules/clusterizator.hpp
    SOURCES     += $$VLibs_Dir/cv_modules/clusterizator.cpp

    HEADERS     += $$VLibs_Dir/cv_modules/dnn.hpp
    SOURCES     += $$VLibs_Dir/cv_modules/dnn.cpp

    HEADERS     += $$VLibs_Dir/cv_modules/projection_creator.hpp
    SOURCES     += $$VLibs_Dir/cv_modules/projection_creator.cpp

    HEADERS     += $$VLibs_Dir/cv_modules/data_agregator.hpp
    SOURCES     += $$VLibs_Dir/cv_modules/data_agregator.cpp

    HEADERS     += $$VLibs_Dir/cv_modules/range.hpp
    SOURCES     += $$VLibs_Dir/cv_modules/range.cpp
}
