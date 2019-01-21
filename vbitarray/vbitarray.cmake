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




message( "Include VBitArray..." )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories( "${VLIBS_PATH}/vbitarray/" )

FILE( GLOB HEADERS_VBitArray "${VLIBS_PATH}/vbitarray/vbitarray.h"   )
FILE( GLOB SOURCES_VBitArray "${VLIBS_PATH}/vbitarray/vbitarray.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_VBitArray} )
set ( SOURCES ${SOURCES} ${SOURCES_VBitArray} )

set ( INC_ALL ${INC_ALL} ${HEADERS_VBitArray} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_VBitArray} )

message( "VBitArray included..." )

