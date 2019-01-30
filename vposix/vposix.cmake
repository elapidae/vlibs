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
# vposix.cmake
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

if ( NOT  VPOSIX_INCLUDED )
    set ( VPOSIX_INCLUDED TRUE )

    message( "Include vposix..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vmacroses/vmacroses.cmake" )
    include( "${VLIBS_DIR}/vlog/vlog.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vposix/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_core.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_files.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_network.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_signal.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_eventfd.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_epoll.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_serial.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_timerfd.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_network_ip.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_alloca.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_network.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_serial.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_timerfd.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_epoll.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_signal.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_network_ip.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_alloca.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_eventfd.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_files.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_core.cpp") 

    message( "vposix included" )

endif()
# vposix.cmake
#========================================================================================
