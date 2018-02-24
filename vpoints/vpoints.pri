

isEmpty(qi_vpoints) {
    qi_vpoints = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vpoints appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    include( $$VLibs_Dir/vstring/vstring.pri )

    INCLUDEPATH += $$VLibs_Dir/vpoints
    HEADERS     += $$files($$VLibs_Dir/vpoints/vpoints.h)
    #SOURCES     += $$files($$VLibs_Dir/vpoints/vpoints.cpp)
}
