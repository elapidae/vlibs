#========================================================================================
# vlog.cmake
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

if ( NOT  VLOG_INCLUDED )
    set ( VLOG_INCLUDED TRUE )

    message( "Include vlog..." )

    #<<< Start your code here -----------------------------------------------------------
    #   NB! Файл вычищен от лишнего руками.
    include( "${VLIBS_DIR}/vcat/vcat.cmake" )
    include( "${VLIBS_DIR}/vchrono/vchrono.cmake" )

    include_directories( "${VLIBS_DIR}/vlog/")

    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vlog/vlog.h")
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vlog/verror.h")
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vlog/vlog_pretty.h")
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vlog/vlogentry.h")
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vlog/vlogger.h")

    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vlog/vlogger.cpp")
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vlog/verror.cpp")
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vlog/vlogentry.cpp")
    #>>> Stop your code here ------------------------------------------------------------

    message( "vlog included" )

endif()
# vlog.cmake
#========================================================================================
