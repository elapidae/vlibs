

isEmpty(qi_vbytearray) {
    qi_vbytearray = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vbytearray appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/vbytearray

    HEADERS     += $$VLibs_Dir/vbytearray/vbytearray.h
    SOURCES     += $$VLibs_Dir/vbytearray/vbytearray.cpp
}

