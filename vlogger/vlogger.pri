

isEmpty(qi_vlogger) {
    qi_vlogger = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vlogger appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    include($$VLibs_Dir/varg/varg.pri)
    include($$VLibs_Dir/vsignal/vsignal.pri)
    include($$VLibs_Dir/json11/json11.pri)

    INCLUDEPATH += $$VLibs_Dir/vlogger

    HEADERS     += $$VLibs_Dir/vlogger/vlogger.h
    SOURCES     += $$VLibs_Dir/vlogger/vlogger.cpp
}

