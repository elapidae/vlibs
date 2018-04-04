

isEmpty(qi_vimage) {
    qi_vimage = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vimage appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/vimage

    HEADERS     += $$VLibs_Dir/vimage/vimage.h
    SOURCES     += $$VLibs_Dir/vimage/vimage.cpp
}
