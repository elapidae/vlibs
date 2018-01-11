
# Ежели ругается на отсутствие библиотеки sqlite3:
# aptitude install libsqlite3-dev sqlite3

isEmpty(qi_sqlite3pp) {
    qi_sqlite3pp = 1;
    isEmpty(qi_not_print_pri_messages): message("=== sqlite3pp appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/sqlite3pp

    HEADERS     += $$VLibs_Dir/sqlite3pp/sqlite3pp.h
    SOURCES     += $$VLibs_Dir/sqlite3pp/sqlite3pp.cpp

    HEADERS     += $$VLibs_Dir/sqlite3pp/sqlite3ppext.h
    SOURCES     += $$VLibs_Dir/sqlite3pp/sqlite3ppext.cpp

    LIBS += -lsqlite3
}

