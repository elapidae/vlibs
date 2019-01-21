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
# vopencv.cmake
#
# NB! Файл редактирован.
#
#========================================================================================


#========================================================================================

if ( NOT  VOPENCV_INCLUDED )
    set ( VOPENCV_INCLUDED TRUE )

    message( "Include vopencv..." )

    #<<< Start your code here -----------------------------------------------------------

    find_package( OpenCV REQUIRED )

    include_directories( ${OpenCV_INCLUDE_DIRS} )

    set ( V_LIBRARIES ${V_LIBRARIES} ${OpenCV_LIBS} )

    #>>> Stop your code here ------------------------------------------------------------

    message( "vopencv included" )

endif()
# vopencv.cmake
#========================================================================================
