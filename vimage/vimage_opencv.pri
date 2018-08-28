#========================================================================================
#   UPD 2018-08-28      by Elapidae
#
#   Файл ручной работы, подтягивает opencv-шную реализацию к VImage.
#   Умеет всякие конвертеры, но пока код под карантинным надзором.
#
#========================================================================================


#========================================================================================
isEmpty(qi_vimage_opencv) {
    qi_vimage_opencv = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vimage_opencv appended ===")

    isEmpty(VLIBS_DIR): error("vimage_opencv: Need VLIBS_DIR correct path.")

    include( $$VLIBS_DIR/vlog/vlog.pri       )
    include( $$VLIBS_DIR/vimage/vimage.pri   )
    include( $$VLIBS_DIR/vopencv/vopencv.pri )

    HEADERS     += $$VLIBS_DIR/vimage/vimage_opencv.h
    SOURCES     += $$VLIBS_DIR/vimage/vimage_opencv.cpp
}
#========================================================================================
