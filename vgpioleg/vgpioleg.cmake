#========================================================================================
# vgpioleg.cmake
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

if ( NOT  VGPIOLEG_INCLUDED )
    set ( VGPIOLEG_INCLUDED TRUE )

    message( "Include vgpioleg..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vcat/vcat.cmake" )
    include( "${VLIBS_DIR}/vfile/vfile.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vgpioleg/")


    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgpioleg/vgpioleg.h")

    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgpioleg/vgpioleg.cpp")

    message( "vgpioleg included" )

endif()
# vgpioleg.cmake
#========================================================================================
