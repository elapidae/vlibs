
isEmpty(qi_json11) {
	qi_json11 = 1;
	isEmpty(qi_not_print_pri_messages): message("=== json11 appended ===")

	isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/json11

    HEADERS     += $$VLibs_Dir/json11/json11.h
    SOURCES     += $$VLibs_Dir/json11/json11.cpp
}

