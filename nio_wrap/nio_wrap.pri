

isEmpty(qi_nio_wrap) {
    qi_nio_wrap = 1
    isEmpty(qi_not_print_pri_messages): message("=== NIO (GIO wrapper) appended ===")

    isEmpty(Nio_Dir): error("Need Nio_Dir variable.")

    CONFIG *= link_pkgconfig
    PKGCONFIG *= gio-2.0


    INCLUDEPATH += $$Nio_Dir
    INCLUDEPATH += $$Nio_Dir/network

    HEADERS     += $$files($$Nio_Dir/*.h)
    SOURCES     += $$files($$Nio_Dir/*.cpp)

    HEADERS     += $$files($$Nio_Dir/network/*.h)
    SOURCES     += $$files($$Nio_Dir/network/*.cpp)

    HEADERS     += $$files($$Nio_Dir/impl/*.h)
    SOURCES     += $$files($$Nio_Dir/impl/*.cpp)
}



