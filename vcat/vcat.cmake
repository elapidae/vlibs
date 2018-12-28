#========================================================================================
# vcat.cmake
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

if ( NOT  VCAT_INCLUDED )
    set ( VCAT_INCLUDED TRUE )

    message( "Include vcat..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/c++11/c++11.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vcat/")

    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vcat/vcat.cpp")
    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vcat/vcat_containers.h")
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vcat/vcat.h")
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vcat/_vcat_iface.h")

    message( "vcat included" )

endif()
# vcat.cmake
#========================================================================================
