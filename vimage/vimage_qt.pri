

isEmpty(qi_vimage_qt) {
    qi_vimage_qt = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vimage_qt appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    include( $$VLibs_Dir/vimage/vimage.pri )
    include( $$VLibs_Dir/vlog/vlog.pri )

    HEADERS     += $$VLibs_Dir/vimage/vimage_qt.h
    SOURCES     += $$VLibs_Dir/vimage/vimage_qt.cpp
}

