

# -----------------------------------------------------------------------
isEmpty(qi_qt_vinvoke) {
    qi_qt_vinvoke = 1
    isEmpty(qi_not_print_pri_messages): message("=== qt_vinvoke appended ===")

    !contains(CONFIG, c++11): CONFIG += c++11

    INCLUDEPATH += $$VLIBS_DIR/qt_vinvoke

    HEADERS  	+= $$VLIBS_DIR/qt_vinvoke/qt_vinvoke.h
    SOURCES  	+= $$VLIBS_DIR/qt_vinvoke/qt_vinvoke.cpp
}
# -----------------------------------------------------------------------

