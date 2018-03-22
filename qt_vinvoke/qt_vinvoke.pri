

# -----------------------------------------------------------------------
isEmpty(qi_qt_vinvoke) {
    qi_qt_vinvoke = 1
    message("appended: -= qi_qt_vinvoke =-")

    !contains(CONFIG, c++11): CONFIG += c++11

    INCLUDEPATH += $$VLibs_Dir/qt_vinvoke

    HEADERS  	+= $$VLibs_Dir/qt_vinvoke/qt_vinvoke.h
    SOURCES  	+= $$VLibs_Dir/qt_vinvoke/qt_vinvoke.cpp
}
# -----------------------------------------------------------------------

