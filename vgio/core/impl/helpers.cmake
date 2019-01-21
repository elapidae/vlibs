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
