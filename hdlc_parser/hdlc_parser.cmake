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
# hdlc_parser.cmake
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

if ( NOT  HDLC_PARSER_INCLUDED )
    set ( HDLC_PARSER_INCLUDED TRUE )

    message( "Include hdlc_parser..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vstring/vstring.cmake" )
    include( "${VLIBS_DIR}/vcallback/vcallback.cmake" )
    include( "${VLIBS_DIR}/vlog/vlog.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/hdlc_parser/")


    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/hdlc_parser/hdlc_parser.h")

    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/hdlc_parser/hdlc_parser.cpp")

    message( "hdlc_parser included" )

endif()
# hdlc_parser.cmake
#========================================================================================
