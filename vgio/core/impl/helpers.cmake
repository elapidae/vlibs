#========================================================================================
# impl.cmake
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

if ( NOT  VGIO_CORE_IMPL_INCLUDED )
    set ( VGIO_CORE_IMPL_INCLUDED TRUE )

    message( "Include VGIO core impl..." )

    #<<< Start your code here -----------------------------------------------------------
    include_directories( "${VLIBS_DIR}/vgio/core")

    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgio/core/impl/vgio_casting_helper.h")

    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgio/core/impl/vgio_converting_helper.h")
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgio/core/impl/vgio_converting_helper.cpp")
    #>>> Stop your code here ------------------------------------------------------------

    message( "VGIO core impl included" )

endif()
# impl.cmake
#========================================================================================
