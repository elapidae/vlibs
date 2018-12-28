

isEmpty(qi_vbitarray) {
    qi_vbitarray = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vbitarray appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/vbitarray

    HEADERS     += $$VLibs_Dir/vbitarray/vbitarray.h
    SOURCES     += $$VLibs_Dir/vbitarray/vbitarray.cpp
}
