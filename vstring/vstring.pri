

isEmpty(qi_vstring) {
    qi_vstring = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vstring appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    CONFIG *= c++11

    INCLUDEPATH += $$VLibs_Dir/vstring

    HEADERS     += $$VLibs_Dir/vstring/vstring.h
    SOURCES     += $$VLibs_Dir/vstring/vstring.cpp
    
    HEADERS     += $$VLibs_Dir/vstring/vbufferforwardreader.h
    SOURCES     += $$VLibs_Dir/vstring/vbufferforwardreader.cpp
}

