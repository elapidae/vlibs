
isEmpty(qi_varg) {
	qi_varg = 1;
	isEmpty(qi_not_print_pri_messages): message("=== varg appended ===")

	isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

        INCLUDEPATH += $$VLibs_Dir/varg

        HEADERS     += $$VLibs_Dir/varg/varg.h
        SOURCES     += $$VLibs_Dir/varg/varg.cpp
}

