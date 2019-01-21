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
# vimage_opencv.cmake
#
# NB! Файл правлен ручками, постарайтесь не перегенерировать.
#
#========================================================================================


#========================================================================================

if ( NOT  VIMAGE_OPENCV_INCLUDED )
    set ( VIMAGE_OPENCV_INCLUDED TRUE )

    message( "Include vimage opencv..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vimage/vimage.cmake" )
    include( "${VLIBS_DIR}/vopencv/vopencv.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vimage/vimage_opencv.h")
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vimage/vimage_opencv.cpp")

    message( "vimage opencv included" )

endif()
# vimage_opencv.cmake
#========================================================================================
