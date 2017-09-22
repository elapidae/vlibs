
isEmpty(qi_vdatetime) {
	qi_vdatetime = 1;
	isEmpty(qi_not_print_pri_messages): message("=== vdatetime appended ===")

	isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/vdatetime

    HEADERS     += $$VLibs_Dir/vdatetime/vdatetime.h
    SOURCES     += $$VLibs_Dir/vdatetime/vdatetime.cpp
}

