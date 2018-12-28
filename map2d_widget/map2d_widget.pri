
isEmpty(qi_map2d_widget) {
    qi_map2d_widget = 1;

    isEmpty(qi_not_print_pri_messages): message("=== Map2D widget appended ===")

    QT *= opengl

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    include( $$VLibs_Dir/vsignal/vsignal.pri )

    INCLUDEPATH += $$VLibs_Dir/map2d_widget

    HEADERS     += $$VLibs_Dir/map2d_widget/map2d_widget.h
    SOURCES     += $$VLibs_Dir/map2d_widget/map2d_widget.cpp
}

