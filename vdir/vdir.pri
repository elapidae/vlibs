

isEmpty(qi_vdir) {
    qi_vdir = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vdir appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/vdir

    HEADERS     += $$VLibs_Dir/vdir/vdir.h
    SOURCES     += $$VLibs_Dir/vdir/vdir.cpp
}

