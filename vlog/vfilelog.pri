

isEmpty(qi_vfilelog) {
    qi_vfilelog = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vfilelog appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    include($$VLibs_Dir/vlog/vlog.pri)
    include($$VLibs_Dir/voutfile/voutfile.pri)
    include($$VLibs_Dir/vthread/vthread.pri)

    HEADERS     += $$VLibs_Dir/vlog/vfilelog.h
    SOURCES     += $$VLibs_Dir/vlog/vfilelog.cpp
    
    HEADERS     += $$VLibs_Dir/vlog/vfilelog_threaded.h
    SOURCES     += $$VLibs_Dir/vlog/vfilelog_threaded.cpp
}

