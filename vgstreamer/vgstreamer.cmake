#========================================================================================
# vgstreamer.cmake
#   Edited manually
#========================================================================================


#========================================================================================

if ( NOT  VGSTREAMER_INCLUDED )
    set ( VGSTREAMER_INCLUDED TRUE )

    message( "Include vgstreamer..." )

    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vgstreamer/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgstreamer/vgstbin.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgstreamer/vgstcaps.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgstreamer/vgstrtph264depay.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgstreamer/vgstmapinfo.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgstreamer/vgststructure.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgstreamer/rtp_sink.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgstreamer/vgstappsink.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgstreamer/vgstsample.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgstreamer/vgstcapsfilter.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgstreamer/vgobject.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgstreamer/vgstpipeline.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgstreamer/vgstvideoconvert.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgstreamer/vgstudpsrc.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgstreamer/vgstelement.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgstreamer/vgstbuffer.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgstreamer/vgstlibav.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgstreamer/src/vgstcaps.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgstreamer/src/vgstelement.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgstreamer/src/vgstpipeline.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgstreamer/src/vgstlibav.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgstreamer/src/vgstrtph264depay.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgstreamer/src/vgstappsink.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgstreamer/src/vgstudpsrc.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgstreamer/src/vgstbin.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgstreamer/src/vgstmapinfo.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgstreamer/src/vgststructure.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgstreamer/src/vgstvideoconvert.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgstreamer/src/vgobject.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgstreamer/src/vgstcapsfilter.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgstreamer/src/vgstbuffer.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgstreamer/src/vgstsample.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgstreamer/src/rtp_sink.cpp") 

    message( "vgstreamer included" )

endif()
# vgstreamer.cmake
#========================================================================================
