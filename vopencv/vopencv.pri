

isEmpty(qi_opencv) {
    qi_opencv = 1;
    isEmpty(qi_not_print_pri_messages): message("=== opencv appended ===")

    CONFIG    *= link_pkgconfig
    PKGCONFIG *= opencv
    CONFIG    *= c++11
}
