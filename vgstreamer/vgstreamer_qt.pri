#========================================================================================
# vgstreamer.pri
#   Edited manually
#========================================================================================


#========================================================================================
isEmpty(qi_vgstreamer_qt) {
    qi_vgstreamer_qt = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vgstreamer_qt appended ===")

    isEmpty(VLIBS_DIR): error("vgstreamer: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------

    include( $$VLIBS_DIR/vgstreamer/vgstreamer.pri )
    include( $$VLIBS_DIR/vimage/vimage_qt.pri )

    HEADERS     += $$VLIBS_DIR/vgstreamer/rtp_sink_qt.h
    SOURCES     += $$VLIBS_DIR/vgstreamer/rtp_sink_qt.cpp

    #>>> Stop your code here ------------------------------------------------------------
}
# vgstreamer.pri
#========================================================================================
