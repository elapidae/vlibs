#========================================================================================
# vpoll.pri
#   Manual edited
#========================================================================================


#========================================================================================
isEmpty(qi_vpoll) {
    qi_vpoll = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vpoll appended ===")

    isEmpty(VLIBS_DIR): error("vpoll: Need VLIBS_DIR correct path.")

    include( $$VLIBS_DIR/vstd/vstd.pri )

    HEADERS     += $$VLIBS_DIR/vapplication/vpoll/vpoll.h
    SOURCES     += $$VLIBS_DIR/vapplication/vpoll/vpoll.cpp
}
# vpoll.pri
#========================================================================================
