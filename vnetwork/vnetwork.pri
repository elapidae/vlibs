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
# vnetwork.pri
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
isEmpty(qi_vnetwork) {
    qi_vnetwork = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vnetwork appended ===")

    isEmpty(VLIBS_DIR): error("vnetwork: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vsignal/vsignal.pri )
    include( $$VLIBS_DIR/vstring/vstring.pri )
    include( $$VLIBS_DIR/vlog/vlog.pri )
    include( $$VLIBS_DIR/vposix/vposix.pri )
    include( $$VLIBS_DIR/vapplication/vapplication.pri )
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vnetwork

    
    HEADERS     += $$VLIBS_DIR/vnetwork/vtcpsocket.h 
    HEADERS     += $$VLIBS_DIR/vnetwork/vudpsocket.h 
    HEADERS     += $$VLIBS_DIR/vnetwork/vtcpserver.h 
    HEADERS     += $$VLIBS_DIR/vnetwork/vipaddress.h 
    
    SOURCES     += $$VLIBS_DIR/vnetwork/vtcpserver.cpp
    SOURCES     += $$VLIBS_DIR/vnetwork/vudpsocket.cpp 
    SOURCES     += $$VLIBS_DIR/vnetwork/vtcpsocket.cpp 
    SOURCES     += $$VLIBS_DIR/vnetwork/vipaddress.cpp 
}
# vnetwork.pri
#========================================================================================
