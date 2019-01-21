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
# keyfile.cmake
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

if ( NOT  VGIO_KEYFILE_INCLUDED )
    set ( VGIO_KEYFILE_INCLUDED TRUE )

    message( "Include VGIO keyfile..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vgio/error/error.cmake" )
    include( "${VLIBS_DIR}/vgio/core/impl/helpers.cmake" )

    include_directories( "${VLIBS_DIR}/vgio/keyfile" )

    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgio/keyfile/vgio_keyfile.h")
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgio/keyfile/vgio_keyfile.cpp")

    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgio/keyfile/vgio_keyfile_schema.h")
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgio/keyfile/vgio_keyfile_schema.cpp")

    add_definitions( -DVGIO_KEYFILE_INCLUDED_ELPD )
    #>>> Stop your code here ------------------------------------------------------------

    message( "VGIO keyfile included" )

endif()
# keyfile.cmake
#========================================================================================
