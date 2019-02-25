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
# vstd.pri
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
isEmpty(qi_vstd) {
    qi_vstd = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vstd appended ===")

    isEmpty(VLIBS_DIR): error("vstd: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vstd

    
    HEADERS     += $$VLIBS_DIR/vstd/vstd_atomic_queue.h 
    HEADERS     += $$VLIBS_DIR/vstd/vstd_atomic_map.h 
    
    SOURCES     += $$VLIBS_DIR/vstd/vstd_atomic_queue.cpp 
}
# vstd.pri
#========================================================================================

HEADERS += \
    $$PWD/vstd_set.h

SOURCES +=
