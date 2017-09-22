

isEmpty(qi_vthread) {
        qi_vthread = 1;
        isEmpty(qi_not_print_pri_messages): message("=== vthread appended ===")

	isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

	include( $$VLibs_Dir/vsignal/vsignal.pri )


        INCLUDEPATH += $$VLibs_Dir/vthread

        HEADERS     += $$VLibs_Dir/vthread/vsemaphore/vsemaphore.h
        SOURCES     += $$VLibs_Dir/vthread/vsemaphore/vsemaphore.cpp

        HEADERS     += $$VLibs_Dir/vthread/vthreadqueue/vsemaphorequeue.h
        HEADERS     += $$VLibs_Dir/vthread/vthreadqueue/vthreadqueue.h
        SOURCES     += $$VLibs_Dir/vthread/vthreadqueue/vthreadqueue.cpp

        HEADERS     += $$VLibs_Dir/vthread/vslot.h
        SOURCES     += $$VLibs_Dir/vthread/vslot.cpp

        HEADERS     += $$VLibs_Dir/vthread/vthread.h
        SOURCES     += $$VLibs_Dir/vthread/vthread.cpp

        HEADERS     += $$VLibs_Dir/vthread/impl/vthreadqueueregistrator_impl.h
        SOURCES     += $$VLibs_Dir/vthread/impl/vthreadqueueregistrator_impl.cpp
}


