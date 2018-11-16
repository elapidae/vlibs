
isEmpty(qi_qcustomplot) {
    qi_qcustomplot = 1;
    isEmpty(qi_not_print_pri_messages): message("=== qcustomplot appended ===")

    QT      *= printsupport

    isEmpty(VLIBS_DIR): error("qcustomplot: Need VLIBS_DIR correct path.")

    INCLUDEPATH += $$VLIBS_DIR/qcustomplot

    HEADERS     += $$VLIBS_DIR/qcustomplot/qcustomplot.h
    SOURCES     += $$VLIBS_DIR/qcustomplot/qcustomplot.cpp

    HEADERS     += $$VLIBS_DIR/qcustomplot/vcustomplot.h
    SOURCES     += $$VLIBS_DIR/qcustomplot/vcustomplot.cpp
}


