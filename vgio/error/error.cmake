#========================================================================================
# error.cmake
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

if ( NOT  ERROR_INCLUDED )
    set ( ERROR_INCLUDED TRUE )

    message( "Include error..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vgio/core/core.cmake" )
    include( "${VLIBS_DIR}/vcat/vcat.cmake" )
    include( "${VLIBS_DIR}/vlog/vlog.cmake" )

    include_directories( "${VLIBS_DIR}/vgio/error/" )

    set( V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgio/error/vgio_error.h" )
    set( V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgio/error/vgio_error.cpp" )
    #>>> Stop your code here ------------------------------------------------------------

    message( "error included" )

endif()
# error.cmake
#========================================================================================
