#========================================================================================
# vgeometry.cmake
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

if ( NOT  VGEOMETRY_INCLUDED )
    set ( VGEOMETRY_INCLUDED TRUE )

    message( "Include vgeometry..." )

    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vgeometry/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgeometry/vline.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgeometry/vtransformation.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgeometry/vpoints.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgeometry/vinterval.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgeometry/vtransformation.cpp") 

    message( "vgeometry included" )

endif()
# vgeometry.cmake
#========================================================================================
