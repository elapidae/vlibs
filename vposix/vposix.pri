#========================================================================================
# vposix.pri
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
isEmpty(qi_vposix) {
    qi_vposix = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vposix appended ===")

    isEmpty(VLIBS_DIR): error("vposix: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    OTHER_FILES += $$VLIBS_DIR/vposix/README
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vposix

    
    HEADERS     += $$VLIBS_DIR/vposix/vposix_core.h
    HEADERS     += $$VLIBS_DIR/vposix/vposix_files.h
    HEADERS     += $$VLIBS_DIR/vposix/vposix_network.h
    HEADERS     += $$VLIBS_DIR/vposix/vposix_network_ip.h
    HEADERS     += $$VLIBS_DIR/vposix/vposix_signal.h
    HEADERS     += $$VLIBS_DIR/vposix/vposix_eventfd.h
    HEADERS     += $$VLIBS_DIR/vposix/vposix_epoll.h
    HEADERS     += $$VLIBS_DIR/vposix/vposix_timerfd.h
    HEADERS     += $$VLIBS_DIR/vposix/vposix_alloca.h
    
    SOURCES     += $$VLIBS_DIR/vposix/vposix_network.cpp
    SOURCES     += $$VLIBS_DIR/vposix/vposix_timerfd.cpp
    SOURCES     += $$VLIBS_DIR/vposix/vposix_epoll.cpp
    SOURCES     += $$VLIBS_DIR/vposix/vposix_signal.cpp
    SOURCES     += $$VLIBS_DIR/vposix/vposix_alloca.cpp
    SOURCES     += $$VLIBS_DIR/vposix/vposix_eventfd.cpp
    SOURCES     += $$VLIBS_DIR/vposix/vposix_files.cpp
    SOURCES     += $$VLIBS_DIR/vposix/vposix_core.cpp
    SOURCES     += $$VLIBS_DIR/vposix/vposix_network_ip.cpp

}
# vposix.pri
#========================================================================================


