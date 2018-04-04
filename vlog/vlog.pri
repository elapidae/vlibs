

isEmpty(qi_vlog) {
    qi_vlog = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vlog (v.2) appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    include($$VLibs_Dir/vcat/vcat.pri)
    include($$VLibs_Dir/vstring/vstring.pri)
    include($$VLibs_Dir/vchrono/vchrono.pri)

    INCLUDEPATH += $$VLibs_Dir/vlog

    HEADERS     += $$VLibs_Dir/vlog/vlog.h

    HEADERS     += $$VLibs_Dir/vlog/vlog_pretty.h
    SOURCES     += $$VLibs_Dir/vlog/vlog_pretty.cpp

    HEADERS     += $$VLibs_Dir/vlog/vlogger.h
    SOURCES     += $$VLibs_Dir/vlog/vlogger.cpp
    
    HEADERS     += $$VLibs_Dir/vlog/vlogentry.h
    SOURCES     += $$VLibs_Dir/vlog/vlogentry.cpp

    HEADERS     += $$VLibs_Dir/vlog/vsyslogger.h
    SOURCES     += $$VLibs_Dir/vlog/vsyslogger.cpp
}


