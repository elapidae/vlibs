
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

    HEADERS     += $$VLibs_Dir/cv_modules/stereo_handler.hpp
    SOURCES     += $$VLibs_Dir/cv_modules/stereo_handler.cpp

    HEADERS     += $$VLibs_Dir/cv_modules/viz.hpp
    SOURCES     += $$VLibs_Dir/cv_modules/viz.cpp

    HEADERS     += $$VLibs_Dir/cv_modules/profiler.hpp
    SOURCES     += $$VLibs_Dir/cv_modules/profiler.cpp

    HEADERS     += $$VLibs_Dir/cv_modules/ml.hpp
    SOURCES     += $$VLibs_Dir/cv_modules/ml.cpp
}
