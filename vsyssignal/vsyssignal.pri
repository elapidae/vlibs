#========================================================================================
#  VSysSignal -- регистратор обработчиков системных сигналов (SIGINT, SIGKILL, SIGTERM).
#========================================================================================


#========================================================================================
isEmpty(qi_vsyssignal) {
    qi_vsyssignal = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vsyssignal appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    CONFIG *= c++11

    INCLUDEPATH += $$VLibs_Dir/vsyssignal

    HEADERS     += $$VLibs_Dir/vsyssignal/vsyssignal.h
    SOURCES     += $$VLibs_Dir/vsyssignal/vsyssignal.cpp
}
#========================================================================================
