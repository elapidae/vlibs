#========================================================================================
# vopencv.cmake
#
#
# Этот файл сгенерирован автоматически.
#
# Вносить изменения можно между строк:
#   #<<< Start your code here
#   Сохраненный код.
#   #>>> Stop your code here
# Все остальные изменения будут перезаписаны.
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

    include_directories( "${VLIBS_DIR}/vopencv/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vopencv/vcv_image.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vopencv/vcv_image.cpp") 

    message( "vopencv included" )

endif()
# vopencv.cmake
#========================================================================================
