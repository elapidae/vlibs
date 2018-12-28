

isEmpty(qi_vimage_basler) {
    qi_vimage_basler = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vimage_basler appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    include( $$VLibs_Dir/vimage/vimage.pri )

    HEADERS += $$VLibs_Dir/vimage/vimage_basler_impl.h
    SOURCES += $$VLibs_Dir/vimage/vimage_basler_impl.cpp
}
