

isEmpty(qi_vgeometry) {
    qi_vgeometry = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vgeometry appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    include( $$VLibs_Dir/vbytearray/vbytearray.pri )

    INCLUDEPATH += $$VLibs_Dir/vgeometry
    HEADERS     += $$files($$VLibs_Dir/vgeometry/*.h)
    SOURCES     += $$files($$VLibs_Dir/vgeometry/*.cpp)

    HEADERS     += $$files($$VLibs_Dir/vgeometry/valgorithms/*.h)
    SOURCES     += $$files($$VLibs_Dir/vgeometry/valgorithms/*.cpp)
}
