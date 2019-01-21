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
# vfile.cmake
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

if ( NOT  VFILE_INCLUDED )
    set ( VFILE_INCLUDED TRUE )

    message( "Include vfile..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vposix/vposix.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vfile/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vfile/vfile.h") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vfile/vfile.cpp") 

    message( "vfile included" )

endif()
# vfile.cmake
#========================================================================================
