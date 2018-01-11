

isEmpty(qi_ii_network) {
    qi_ii_network = 1;
    isEmpty(qi_not_print_pri_messages): message("=== ii network appended ===")

    isEmpty(VLibs_Dir):  error("Need VLibs_Dir correct path.")
    isEmpty(Ishumi_Dir): error("Need Ishumi_Dir correct path.")

    HEADERS += $$files($$Ishumi_Dir/ii_network/*.h)
    SOURCES += $$files($$Ishumi_Dir/ii_network/*.cpp)

ololo
}
