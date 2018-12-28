
#========================================================================================
isEmpty(qi_vbitmessage) {
    qi_vbitmessage = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vbitmessage appended ===")

    isEmpty(VLIBS_DIR): error("vbitmessage: Need VLIBS_DIR correct path.")

    INCLUDEPATH += $$VLIBS_DIR/vbitmessage

    HEADERS     += $$VLIBS_DIR/vbitmessage/voutbitmessage.h
    SOURCES     += $$VLIBS_DIR/vbitmessage/voutbitmessage.cpp
}
#========================================================================================

