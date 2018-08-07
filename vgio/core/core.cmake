#========================================================================================
# core.cmake
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
if ( NOT  VGIO_CORE_INCLUDED )
    set ( VGIO_CORE_INCLUDED TRUE )

    message( "Include VGIO core..." )

    #<<< Start your code here -----------------------------------------------------------
    find_package(PkgConfig)

    if( NOT PKG_CONFIG_FOUND )
        message( FATAL_ERROR "Нужен pkgconfig для подключения glib." )
    endif()

    pkg_search_module( GLib_PKG REQUIRED glib-2.0 )

    if ( NOT GLib_PKG_FOUND )
        message( FATAL_ERROR "glib not found" )
    else()
        message( "=== GLib_PKG was found === " )
    endif()

    set( V_LIBRARIES ${V_LIBRARIES} ${GLib_PKG_LIBRARIES} )

    include_directories( ${GLib_PKG_INCLUDE_DIRS} )

    set( VGIO_DIR "${VLIBS_DIR}/vgio" )
    message( "Dont forget use  target_link_libraries({PROJECT_NAME} {V_LIBRARIES}) !!!" )
    #>>> Stop your code here ------------------------------------------------------------

    #include_directories( "${VLIBS_PATH}/core/")


    message( "core VGIO included." )
endif()
# core.cmake
#========================================================================================
