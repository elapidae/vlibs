

isEmpty(qi_vfilelog_keyfile) {
    qi_vfilelog_keyfile = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vfilelog_keyfile appended ===")

    isEmpty(VLIBS_DIR): error("vfilelog_keyfile: Need VLIBS_DIR correct path.")
    include($$VLIBS_DIR/vlog/vfilelog.pri)

    HEADERS     += $$VLIBS_DIR/vlog/vfilelog_keyfile.h
    SOURCES     += $$VLIBS_DIR/vlog/vfilelog_keyfile.cpp
}
