# =======================================================================================
#   UPD 2018-07-03
#   VLog -- система базовой сборки логов
# =======================================================================================


# =======================================================================================
isEmpty ( qi_vlog_3 ) {
    qi_vlog_3 = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vlog (v.3) appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    include( $$VLibs_Dir/vcat/vcat.pri )
    include( $$VLibs_Dir/vchrono/vchrono.pri )

    INCLUDEPATH += $$VLibs_Dir/vlog

    HEADERS     += $$VLibs_Dir/vlog/vlogentry.h
    SOURCES     += $$VLibs_Dir/vlog/vlogentry.cpp

    HEADERS     += $$VLibs_Dir/vlog/vlogger.h
    SOURCES     += $$VLibs_Dir/vlog/vlogger.cpp

    HEADERS     += $$VLibs_Dir/vlog/vlog.h

    HEADERS     += $$VLibs_Dir/vlog/vlog_pretty.h

    HEADERS     += $$VLibs_Dir/vlog/verror.h
    SOURCES     += $$VLibs_Dir/vlog/verror.cpp

    HEADERS     += $$VLibs_Dir/vlog/vsyslogger.h
    SOURCES     += $$VLibs_Dir/vlog/vsyslogger.cpp
}
# =======================================================================================



