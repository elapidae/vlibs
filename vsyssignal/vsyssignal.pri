#========================================================================================
#  VSysSignal -- регистратор обработчиков системных сигналов (SIGINT, SIGKILL, SIGTERM).
#========================================================================================


#========================================================================================
isEmpty(qi_vsyssignal) {
    qi_vsyssignal = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vsyssignal appended ===")

    isEmpty(VLIBS_DIR): error("vsyssignal: Need VLIBS_DIR correct path.")

    CONFIG *= c++11

    INCLUDEPATH += $$VLIBS_DIR/vsyssignal

    HEADERS     += $$VLIBS_DIR/vsyssignal/vsyssignal.h
    SOURCES     += $$VLIBS_DIR/vsyssignal/vsyssignal.cpp
}
#========================================================================================
