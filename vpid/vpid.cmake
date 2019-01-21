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
# vpid.cmake
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

if ( NOT  VPID_INCLUDED )
    set ( VPID_INCLUDED TRUE )

    message( "Include vpid..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vlog/vlog.cmake" )
    include( "${VLIBS_DIR}/vdir/vdir.cmake" )
    include( "${VLIBS_DIR}/voutfile/voutfile.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vpid/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vpid/vpid_saver.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vpid/vpid_saver.cpp") 

    message( "vpid included" )

endif()
# vpid.cmake
#========================================================================================
