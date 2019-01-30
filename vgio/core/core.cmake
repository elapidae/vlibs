#########################################################################################
##
##  VLIBS codebase, NIIAS
##
##  Authors:
##  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
##  Nadezhda Churikova aka claorisel    claorisel@gmail.com
##  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
##  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
##
##  GNU Lesser General Public License Usage
##  This file may be used under the terms of the GNU Lesser General Public License
##  version 3 as published by the Free Software Foundation and appearing in the file
##  LICENSE.LGPL3 included in the packaging of this file. Please review the following
##  information to ensure the GNU Lesser General Public License version 3 requirements
##  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
#########################################################################################


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

    pkg_search_module( GLib_PKG REQUIRED gio-2.0 )

    if ( NOT GLib_PKG_FOUND )
        message( FATAL_ERROR "gio not found" )
    else()
        message( "=== GLib_PKG was found === " )
    endif()

    set( V_LIBRARIES ${V_LIBRARIES} ${GLib_PKG_LIBRARIES} )

    include_directories( ${GLib_PKG_INCLUDE_DIRS} )

    set( VGIO_DIR "${VLIBS_DIR}/vgio" )
    message("Dont forget use target_link_libraries(\${PROJECT_NAME} \${V_LIBRARIES}) !")
    #>>> Stop your code here ------------------------------------------------------------

    #include_directories( "${VLIBS_PATH}/core/")


    message( "core VGIO included." )
endif()
# core.cmake
#========================================================================================
