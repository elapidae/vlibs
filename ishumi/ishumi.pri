

isEmpty(qi_ishumi) {
    qi_ishumi = 1;
    isEmpty(qi_not_print_pri_messages): message("=== appending ishumi... ===")

    isEmpty(VLibs_Dir):  error("Need VLibs_Dir correct path.")
    isEmpty(Ishumi_Dir): error("Need Ishumi_Dir correct path.")


#    include($$VLibs_Dir/varg/varg.pri)
#    include($$VLibs_Dir/vsignal/vsignal.pri)
#    include($$VLibs_Dir/json11/json11.pri)
#    include($$VLibs_Dir/vdatetime/vdatetime.pri)


    INCLUDEPATH += $$Ishumi_Dir

    HEADERS     += $$files($$Ishumi_Dir/*.h)
    SOURCES     += $$files($$Ishumi_Dir/*.cpp)

    HEADERS += $$files($$Ishumi_Dir/ii_network/*.h)
    SOURCES += $$files($$Ishumi_Dir/ii_network/*.cpp)

#    include($$Ishumi_Dir/ii_network/ii_network.pri)
}
