#========================================================================================
# vopencv.cmake
#
# NB! Файл редактирован.
#
#========================================================================================


#========================================================================================

if ( NOT  VOPENCV_INCLUDED )
    set ( VOPENCV_INCLUDED TRUE )

    message( "Include vopencv..." )

    #<<< Start your code here -----------------------------------------------------------

    find_package( OpenCV REQUIRED )

    include_directories( ${OpenCV_INCLUDE_DIRS} )

    set ( V_LIBRARIES ${V_LIBRARIES} ${OpenCV_LIBS} )

    #>>> Stop your code here ------------------------------------------------------------

    message( "vopencv included" )

endif()
# vopencv.cmake
#========================================================================================
