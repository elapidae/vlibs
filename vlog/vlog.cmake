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
