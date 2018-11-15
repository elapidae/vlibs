
isEmpty(qi_json11) {
	qi_json11 = 1;
	isEmpty(qi_not_print_pri_messages): message("=== json11 appended ===")

        isEmpty(VLIBS_DIR): error("json11: Need VLIBS_DIR correct path.")

    INCLUDEPATH += $$VLIBS_DIR/json11

    HEADERS     += $$VLIBS_DIR/json11/json11.h
    SOURCES     += $$VLIBS_DIR/json11/json11.cpp
}

