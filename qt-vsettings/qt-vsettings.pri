#---------------------------------------------------------
#   Адекватная работа с настройками программы.
#   Изначально заточена исключительно для работы с
#   ini - файлами.
#---------------------------------------------------------


!contains(qi_vsettings, 1) {
    qi_vsettings = 1
    message("appended: -= vsettings =-")

    #include($$Libs_Dir/vdeb/vdeb.pri)

    !contains(CONFIG, c++11): CONFIG += c++11

    INCLUDEPATH += $$VLibs_Dir/qt-vsettings

    HEADERS  	+= $$VLibs_Dir/qt-vsettings/vsettings.h
    SOURCES  	+= $$VLibs_Dir/qt-vsettings/vsettings.cpp
}
# -----------------------------------------------------------------------
