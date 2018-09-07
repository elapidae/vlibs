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
