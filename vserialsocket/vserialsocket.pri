
isEmpty(qi_vserialsocket) {
    qi_vserialsocket = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vserialsocket appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    include($$VLibs_Dir/vthread/vthread.pri)

    INCLUDEPATH += $$VLibs_Dir/vserialsocket

    HEADERS     += $$VLibs_Dir/vserialsocket/vserialport.h
    SOURCES     += $$VLibs_Dir/vserialsocket/vserialport.cpp

    HEADERS     += $$VLibs_Dir/vserialsocket/vserialportoptions.h
    SOURCES     += $$VLibs_Dir/vserialsocket/vserialportoptions.cpp

    HEADERS     += $$VLibs_Dir/vserialsocket/vserialsocket.h
    SOURCES     += $$VLibs_Dir/vserialsocket/vserialsocket.cpp
}

