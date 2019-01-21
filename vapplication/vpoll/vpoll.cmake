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
# vpoll.cmake
#   Manual edited.
#========================================================================================


#========================================================================================

if ( NOT  VPOLL_INCLUDED )
    set ( VPOLL_INCLUDED TRUE )

    message( "Include vpoll..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vstd/vstd.cmake" )
    #>>> Stop your code here ------------------------------------------------------------
    
    set( V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vapplication/vpoll/vpoll.h" )
    set( V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vapplication/vpoll/vpoll.cpp" )

    message( "vpoll included" )

endif()
# vpoll.cmake
#========================================================================================
