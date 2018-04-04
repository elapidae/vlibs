

isEmpty(qi_vjpeg) {
    qi_vjpeg = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vjpeg appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    include( $$VLibs_Dir/vimage/vimage.pri )
    include( $$VLibs_Dir/vlog/vlog.pri )
    include( $$VLibs_Dir/voutfile/voutfile.pri )

    LIBS *= -ljpeg

    INCLUDEPATH += $$VLibs_Dir/vjpeg

    HEADERS     += $$VLibs_Dir/vjpeg/vjpeg.h
    SOURCES     += $$VLibs_Dir/vjpeg/vjpeg.cpp
}

