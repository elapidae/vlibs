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
# vgeometry.cmake
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

if ( NOT  VGEOMETRY_INCLUDED )
    set ( VGEOMETRY_INCLUDED TRUE )

    message( "Include vgeometry..." )

    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vgeometry/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgeometry/vline.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgeometry/vtransformation.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgeometry/vpoints.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgeometry/vinterval.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgeometry/vtransformation.cpp") 

    message( "vgeometry included" )

endif()
# vgeometry.cmake
#========================================================================================
