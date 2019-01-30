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
# vthread.pri
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
isEmpty(qi_vthread) {
    qi_vthread = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vthread appended ===")

    isEmpty(VLIBS_DIR): error("vthread: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------

    DEFINES += VTHREAD_USE_PTHREAD

    !contains(CONFIG, qt) {
        LIBS += -pthread
        QMAKE_CXXFLAGS += -pthread
    }

    HEADERS     += $$VLIBS_DIR/vthread/vsemaphore/vsemaphore.h
    SOURCES     += $$VLIBS_DIR/vthread/vsemaphore/vsemaphore.cpp

    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vthread

    
    HEADERS     += $$VLIBS_DIR/vthread/vthread.h 
    #HEADERS     += $$VLIBS_DIR/vthread/vslot.h
    HEADERS     += $$VLIBS_DIR/vthread/vsemaphorequeue.h 
    HEADERS     += $$VLIBS_DIR/vthread/vthreadqueue.h 
    

    SOURCES     += $$VLIBS_DIR/vthread/vthread.cpp 
    SOURCES     += $$VLIBS_DIR/vthread/vthreadqueue.cpp
    #SOURCES     += $$VLIBS_DIR/vthread/vslot.cpp
}
# vthread.pri
#========================================================================================
