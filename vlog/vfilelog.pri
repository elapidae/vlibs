#========================================================================================
# vfilelog.pri
#========================================================================================


#========================================================================================
isEmpty(qi_vlog) {
    qi_vlog = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vlog appended ===")

    isEmpty(VLIBS_DIR): error("Need VLIBS_DIR correct path.")

    include( $$VLIBS_DIR/vlog/vlog.pri )

# 2018-08-07 -- Потом разберусь...
#    HEADERS     += $$VLIBS_DIR/vlog/vsyslogger.h
#    HEADERS     += $$VLIBS_DIR/vlog/vfilelog_threaded.h
#    HEADERS     += $$VLIBS_DIR/vlog/vlog.h
#    HEADERS     += $$VLIBS_DIR/vlog/verror.h
#    HEADERS     += $$VLIBS_DIR/vlog/vlog_pretty.h
#    HEADERS     += $$VLIBS_DIR/vlog/vlogentry.h
#    HEADERS     += $$VLIBS_DIR/vlog/vfilelog_keyfile.h
#    HEADERS     += $$VLIBS_DIR/vlog/vlogger.h
#    HEADERS     += $$VLIBS_DIR/vlog/vfilelog.h
    
#    SOURCES     += $$VLIBS_DIR/vlog/vlogger.cpp
#    SOURCES     += $$VLIBS_DIR/vlog/verror.cpp
#    SOURCES     += $$VLIBS_DIR/vlog/vfilelog_threaded.cpp
#    SOURCES     += $$VLIBS_DIR/vlog/vsyslogger.cpp
#    SOURCES     += $$VLIBS_DIR/vlog/vfilelog_keyfile.cpp
#    SOURCES     += $$VLIBS_DIR/vlog/vlogentry.cpp
#    SOURCES     += $$VLIBS_DIR/vlog/vfilelog.cpp
}
# vfilelog.pri
#========================================================================================
