

isEmpty(qi_vsignal) {
    qi_vsignal = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vsignal appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/vsignal

    HEADERS     += $$VLibs_Dir/vsignal/vsignal.h
}

