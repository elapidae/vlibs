#========================================================================================
# vchrono.cmake
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

if ( NOT  VCHRONO_INCLUDED )
    set ( VCHRONO_INCLUDED TRUE )

    message( "Include vchrono..." )

    #<<< Start your code here -----------------------------------------------------------    
    include( "${VLIBS_DIR}/vcat/vcat.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vchrono/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vchrono/vtimepoint.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vchrono/vchrono_weeks.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vchrono/vtimepoint.cpp") 

    message( "vchrono included" )

endif()
# vchrono.cmake
#========================================================================================
