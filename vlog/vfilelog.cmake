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
#   NB! Ручная правка.
#
# Вносить изменения можно между строк:
#   #<<< Start your code here
#   Сохраненный код.
#   #>>> Stop your code here
# Все остальные изменения будут перезаписаны.
#
#========================================================================================


#========================================================================================

if ( NOT  VFILELOG_INCLUDED )
    set ( VFILELOG_INCLUDED TRUE )

    message( "Include vfilelog..." )

    #<<< Start your code here -----------------------------------------------------------
    #   NB! Файл вычищен от лишнего руками.
    include( "${VLIBS_DIR}/vlog/vlog.cmake" )
    include( "${VLIBS_DIR}/vdir/vdir.cmake" )
    include( "${VLIBS_DIR}/voutfile/voutfile.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vlog/")

    

    #set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vlog/vfilelog_threaded.h")
    #set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vlog/vfilelog_keyfile.h")
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vlog/vfilelog.h") 
    
    #set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vlog/vfilelog_threaded.cpp")
    #set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vlog/vfilelog_keyfile.cpp")
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vlog/vfilelog.cpp") 

    message( "vfilelog included" )

endif()
# vlog.cmake
#========================================================================================
