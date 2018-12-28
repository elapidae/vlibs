

isEmpty(qi_vimage_qt) {
    qi_vimage_qt = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vimage_qt appended ===")

    isEmpty(VLIBS_DIR): error("Need VLIBS_DIR correct path.")

    include( $$VLIBS_DIR/vimage/vimage.pri )
    include( $$VLIBS_DIR/vlog/vlog.pri )

    HEADERS     += $$VLIBS_DIR/vimage/vimage_qt.h
    SOURCES     += $$VLIBS_DIR/vimage/vimage_qt.cpp
}

