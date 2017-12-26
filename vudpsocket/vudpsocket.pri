
isEmpty(qi_vtimer) {
	qi_vtimer = 1;
	isEmpty(qi_not_print_pri_messages): message("=== vtimer appended ===")

	isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/vudpsocket

    HEADERS     += $$VLibs_Dir/vudpsocket/vudpsocket.h
    SOURCES     += $$VLibs_Dir/vudpsocket/vudpsocket.cpp

    HEADERS     += $$VLibs_Dir/vudpsocket/vudpport.h
    SOURCES     += $$VLibs_Dir/vudpsocket/vudpport.cpp

    HEADERS     += $$VLibs_Dir/vudpsocket/vhostaddress.h
    SOURCES     += $$VLibs_Dir/vudpsocket/vhostaddress.cpp
}

