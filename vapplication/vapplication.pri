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
# vapplication.pri
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
isEmpty(qi_vapplication) {
    qi_vapplication = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vapplication appended ===")

    isEmpty(VLIBS_DIR): error("vapplication: Need VLIBS_DIR correct path.")

    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vlog/vlog.pri )
    include( $$VLIBS_DIR/vfile/vfile.pri )
    include( $$VLIBS_DIR/vapplication/vpoll/vpoll.pri )

    HEADERS     += $$VLIBS_DIR/vapplication/vinvoke/vinvokequeue.h
    SOURCES     += $$VLIBS_DIR/vapplication/vinvoke/vinvokequeue.cpp

    HEADERS     += $$VLIBS_DIR/vapplication/vinvoke/vinvoke_iface.h

    OTHER_FILES += $$VLIBS_DIR/vapplication/README
    OTHER_FILES += $$VLIBS_DIR/vapplication/vapplication.cmake
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vapplication
    
    HEADERS     += $$VLIBS_DIR/vapplication/vapplication.h 
    SOURCES     += $$VLIBS_DIR/vapplication/vapplication.cpp 
}
# vapplication.pri
#========================================================================================
