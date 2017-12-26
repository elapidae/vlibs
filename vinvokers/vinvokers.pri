

isEmpty(qi_vinvokers) {
    qi_vinvokers = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vinvokers appended ===")

	isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")


    INCLUDEPATH += $$VLibs_Dir/vinvokers

    HEADERS     += $$VLibs_Dir/vinvokers/vinvokers.h
    SOURCES     += $$VLibs_Dir/vinvokers/vinvokers.cpp
}


