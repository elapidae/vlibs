

#========================================================================================
isEmpty(qi_vcat) {
    qi_vcat = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vcat appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/vcat

    HEADERS     += $$VLibs_Dir/vcat/_vcat_iface.h

    HEADERS     += $$VLibs_Dir/vcat/vcat.h
    SOURCES     += $$VLibs_Dir/vcat/vcat.cpp

    HEADERS     += $$VLibs_Dir/vcat/vcat_containers.h
}
#========================================================================================


