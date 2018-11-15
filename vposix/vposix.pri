#========================================================================================
# vposix.pri
#   Edited manually
#========================================================================================


#========================================================================================
isEmpty(qi_vposix) {
    qi_vposix = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vposix appended ===")

    isEmpty(VLIBS_DIR): error("vposix: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    OTHER_FILES += $$VLIBS_DIR/vposix/README
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vposix

    
    HEADERS     += $$VLIBS_DIR/vposix/vposix_errno.h 
    SOURCES     += $$VLIBS_DIR/vposix/vposix_errno.cpp

    HEADERS     += $$VLIBS_DIR/vposix/vposix_files.h
    SOURCES     += $$VLIBS_DIR/vposix/vposix_files.cpp 

    HEADERS     += $$VLIBS_DIR/vposix/vposix_network.h
    SOURCES     += $$VLIBS_DIR/vposix/vposix_network.cpp

    HEADERS     += $$VLIBS_DIR/vposix/vposix_core.h
    SOURCES     += $$VLIBS_DIR/vposix/vposix_core.cpp

    HEADERS     += $$VLIBS_DIR/vposix/vposix_eventfd.h
    SOURCES     += $$VLIBS_DIR/vposix/vposix_eventfd.cpp

    HEADERS     += $$VLIBS_DIR/vposix/vposix_epoll.h
    SOURCES     += $$VLIBS_DIR/vposix/vposix_epoll.cpp

    HEADERS     += $$VLIBS_DIR/vposix/vposix_alloca.h
    SOURCES     += $$VLIBS_DIR/vposix/vposix_alloca.cpp
}
# vposix.pri
#========================================================================================

HEADERS += \
    $$PWD/vposix_timerfd.h

SOURCES += \
    $$PWD/vposix_timerfd.cpp


