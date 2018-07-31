
isEmpty(qi_qcustomplot) {
    qi_qcustomplot = 1;
    isEmpty(qi_not_print_pri_messages): message("=== qcustomplot appended ===")

    QT      *= printsupport

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/qcustomplot

    HEADERS     += $$VLibs_Dir/qcustomplot/qcustomplot.h
    SOURCES     += $$VLibs_Dir/qcustomplot/qcustomplot.cpp

    HEADERS     += $$VLibs_Dir/qcustomplot/vcustomplot.h
    SOURCES     += $$VLibs_Dir/qcustomplot/vcustomplot.cpp
}


