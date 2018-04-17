

# -----------------------------------------------------------------------
isEmpty(qi_qt_vinvoke) {
    qi_qt_vinvoke = 1
    isEmpty(qi_not_print_pri_messages): message("=== qt_vinvoke appended ===")

    !contains(CONFIG, c++11): CONFIG += c++11

    INCLUDEPATH += $$VLibs_Dir/qt_vinvoke

    HEADERS  	+= $$VLibs_Dir/qt_vinvoke/qt_vinvoke.h
    SOURCES  	+= $$VLibs_Dir/qt_vinvoke/qt_vinvoke.cpp
}
# -----------------------------------------------------------------------

