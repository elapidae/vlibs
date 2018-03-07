
isEmpty(qi_vchrono) {
    qi_vchrono = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vchrono appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/vchrono

    HEADERS     += $$VLibs_Dir/vchrono/vchrono.h
    SOURCES     += $$VLibs_Dir/vchrono/vchrono.cpp

    HEADERS     += $$VLibs_Dir/vchrono/vtimepoint.h
    SOURCES     += $$VLibs_Dir/vchrono/vtimepoint.cpp
}


