#========================================================================================
# vimage_opencv.cmake
#
# NB! Файл правлен ручками, постарайтесь не перегенерировать.
#
#========================================================================================


#========================================================================================

if ( NOT  VIMAGE_OPENCV_INCLUDED )
    set ( VIMAGE_OPENCV_INCLUDED TRUE )

    message( "Include vimage opencv..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vimage/vimage.cmake" )
    include( "${VLIBS_DIR}/vopencv/vopencv.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vimage/vimage_opencv.h")
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vimage/vimage_opencv.cpp")

    message( "vimage opencv included" )

endif()
# vimage_opencv.cmake
#========================================================================================
