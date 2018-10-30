#========================================================================================
# vgstreamer.pri
#   Edited manually
#========================================================================================


#========================================================================================
isEmpty(qi_vgstreamer) {
    qi_vgstreamer = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vgstreamer appended ===")

    isEmpty(VLIBS_DIR): error("vgstreamer: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    CONFIG *= link_pkgconfig
    PKGCONFIG += gstreamer-1.0
    PKGCONFIG += gstreamer-app-1.0
    #INCLUDEPATH += /usr/local/include/gstreamer-1.0

    include( $$VLIBS_DIR/vlog/vlog.pri )
    include( $$VLIBS_DIR/vgio/core/impl/vgio_helpers.pri )
    include( $$VLIBS_DIR/vimage/vimage.pri )
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vgstreamer

    HEADERS     += $$VLIBS_DIR/vgstreamer/vgst_init.h
    SOURCES     += $$VLIBS_DIR/vgstreamer/vgst_init.cpp
    
    HEADERS     += $$VLIBS_DIR/vgstreamer/vgstbin.h 
    HEADERS     += $$VLIBS_DIR/vgstreamer/vgstcaps.h 
    HEADERS     += $$VLIBS_DIR/vgstreamer/vgstrtph264depay.h 
    HEADERS     += $$VLIBS_DIR/vgstreamer/vgstmapinfo.h 
    HEADERS     += $$VLIBS_DIR/vgstreamer/vgststructure.h 
    HEADERS     += $$VLIBS_DIR/vgstreamer/rtp_sink.h 
    HEADERS     += $$VLIBS_DIR/vgstreamer/vgstappsink.h 
    HEADERS     += $$VLIBS_DIR/vgstreamer/vgstsample.h 
    HEADERS     += $$VLIBS_DIR/vgstreamer/vgstcapsfilter.h 
    HEADERS     += $$VLIBS_DIR/vgstreamer/vgobject.h 
    HEADERS     += $$VLIBS_DIR/vgstreamer/vgstpipeline.h 
    HEADERS     += $$VLIBS_DIR/vgstreamer/vgstvideoconvert.h 
    HEADERS     += $$VLIBS_DIR/vgstreamer/vgstudpsrc.h 
    HEADERS     += $$VLIBS_DIR/vgstreamer/vgstelement.h 
    HEADERS     += $$VLIBS_DIR/vgstreamer/vgstbuffer.h 
    HEADERS     += $$VLIBS_DIR/vgstreamer/vgstlibav.h 
    
    SOURCES     += $$VLIBS_DIR/vgstreamer/vgstcaps.cpp
    SOURCES     += $$VLIBS_DIR/vgstreamer/vgstelement.cpp
    SOURCES     += $$VLIBS_DIR/vgstreamer/vgstpipeline.cpp
    SOURCES     += $$VLIBS_DIR/vgstreamer/vgstlibav.cpp
    SOURCES     += $$VLIBS_DIR/vgstreamer/vgstrtph264depay.cpp
    SOURCES     += $$VLIBS_DIR/vgstreamer/vgstappsink.cpp
    SOURCES     += $$VLIBS_DIR/vgstreamer/vgstudpsrc.cpp
    SOURCES     += $$VLIBS_DIR/vgstreamer/vgstbin.cpp
    SOURCES     += $$VLIBS_DIR/vgstreamer/vgstmapinfo.cpp
    SOURCES     += $$VLIBS_DIR/vgstreamer/vgststructure.cpp
    SOURCES     += $$VLIBS_DIR/vgstreamer/vgstvideoconvert.cpp
    SOURCES     += $$VLIBS_DIR/vgstreamer/vgobject.cpp
    SOURCES     += $$VLIBS_DIR/vgstreamer/vgstcapsfilter.cpp
    SOURCES     += $$VLIBS_DIR/vgstreamer/vgstbuffer.cpp
    SOURCES     += $$VLIBS_DIR/vgstreamer/vgstsample.cpp
    SOURCES     += $$VLIBS_DIR/vgstreamer/rtp_sink.cpp
}
# vgstreamer.pri
#========================================================================================

