
isEmpty(qi_vcat) {
	qi_vcat = 1;
	isEmpty(qi_not_print_pri_messages): message("=== vcat appended ===")

	isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

        INCLUDEPATH += $$VLibs_Dir/vcat

        HEADERS     += $$VLibs_Dir/vcat/vcat.h
        SOURCES     += $$VLibs_Dir/vcat/vcat.cpp
}

HEADERS += \
    $$PWD/vcat_iface.h

SOURCES += \
    $$PWD/vcat_iface.cpp

