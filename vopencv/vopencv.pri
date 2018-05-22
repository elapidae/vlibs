

isEmpty(qi_opencv) {
    qi_opencv = 1;
    isEmpty(qi_not_print_pri_messages): message("=== opencv appended ===")

    #isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    #INCLUDEPATH += /usr/include
    LIBS += `pkg-config --libs opencv` #-lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_calib3d
    QMAKE_CXXFLAGS *= -std=c++11
}
