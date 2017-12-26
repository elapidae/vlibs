
isEmpty(qi_vgpioleg) {
	qi_vgpioleg = 1;
	isEmpty(qi_not_print_pri_messages): message("=== vgpioleg appended ===")

	isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

	include($$VLibs_Dir/vfile/vfile.pri)

    INCLUDEPATH += $$VLibs_Dir/vgpioleg

    HEADERS     += $$VLibs_Dir/vgpioleg/vgpioleg.h
    SOURCES     += $$VLibs_Dir/vgpioleg/vgpioleg.cpp
}

