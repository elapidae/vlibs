

isEmpty(qi_vimage_opencv) {
    qi_vimage_opencv = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vimage_opencv appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    include( $$VLibs_Dir/vimage/vimage.pri )
    include( $$VLibs_Dir/vopencv/vopencv.pri )
    include( $$VLibs_Dir/vlog/vlog.pri )

    HEADERS     += $$VLibs_Dir/vimage/vimage_opencv_dev1.h
    SOURCES     += $$VLibs_Dir/vimage/vimage_opencv_dev1.cpp
}
