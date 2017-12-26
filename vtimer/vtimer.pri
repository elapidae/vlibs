
isEmpty(qi_vtimer) {
	qi_vtimer = 1;
	isEmpty(qi_not_print_pri_messages): message("=== vtimer appended ===")

	isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/vtimer

    HEADERS     += $$VLibs_Dir/vtimer/vtimer.h
    SOURCES     += $$VLibs_Dir/vtimer/vtimer.cpp
}

