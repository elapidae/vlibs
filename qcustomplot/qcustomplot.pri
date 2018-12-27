
isEmpty(qi_qcustomplot) {
    qi_qcustomplot = 1;
    isEmpty(qi_not_print_pri_messages): message("=== qcustomplot appended ===")

    isEmpty(VLIBS_DIR): error("qcustomplot: Need VLIBS_DIR correct path.")

    include( $$VLIBS_DIR/vgeometry/vgeometry.pri )

    QT      *= printsupport


    INCLUDEPATH += $$VLIBS_DIR/qcustomplot

    HEADERS     += $$VLIBS_DIR/qcustomplot/qcustomplot.h
    SOURCES     += $$VLIBS_DIR/qcustomplot/qcustomplot.cpp

    HEADERS     += $$VLIBS_DIR/qcustomplot/vcustomplot.h
    SOURCES     += $$VLIBS_DIR/qcustomplot/vcustomplot.cpp

    OTHER_FILES += $$VLIBS_DIR/qcustomplot/samples.txt
}
