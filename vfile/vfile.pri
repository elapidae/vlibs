
isEmpty(qi_vfile) {
	qi_vfile = 1;
	isEmpty(qi_not_print_pri_messages): message("=== vfile appended ===")

	isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/vfile

    HEADERS     += $$VLibs_Dir/vfile/vfile.h
    SOURCES     += $$VLibs_Dir/vfile/vfile.cpp
}

