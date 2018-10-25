#========================================================================================
# vfilelog.pri
#========================================================================================


#========================================================================================
isEmpty(qi_vfilelog) {
    qi_vfilelog = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vfilelog appended ===")

    isEmpty(VLIBS_DIR): error("vfilelog: Need VLIBS_DIR correct path.")


#    include( $$VLIBS_DIR/vgio/keyfile/vgio_keyfile.pri )
    include( $$VLIBS_DIR/vlog/vlog.pri )
    include( $$VLIBS_DIR/vdir/vdir.pri )
    include( $$VLIBS_DIR/vthread/vthread.pri )
    include( $$VLIBS_DIR/voutfile/voutfile.pri )

# 2018-08-07 -- Потом разберусь...
    HEADERS     += $$VLIBS_DIR/vlog/vfilelog_threaded.h
#    HEADERS     += $$VLIBS_DIR/vlog/vfilelog_keyfile.h
    HEADERS     += $$VLIBS_DIR/vlog/vfilelog.h
    
    SOURCES     += $$VLIBS_DIR/vlog/vfilelog_threaded.cpp
#    SOURCES     += $$VLIBS_DIR/vlog/vfilelog_keyfile.cpp
    SOURCES     += $$VLIBS_DIR/vlog/vfilelog.cpp
}
# vfilelog.pri
#========================================================================================
