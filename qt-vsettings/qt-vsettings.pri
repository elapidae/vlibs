#########################################################################################
##
##  VLIBS codebase, NIIAS
##
##  Authors:
##  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
##  Nadezhda Churikova aka claorisel    claorisel@gmail.com
##  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
##  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
##
##  GNU Lesser General Public License Usage
##  This file may be used under the terms of the GNU Lesser General Public License
##  version 3 as published by the Free Software Foundation and appearing in the file
##  LICENSE.LGPL3 included in the packaging of this file. Please review the following
##  information to ensure the GNU Lesser General Public License version 3 requirements
##  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
#########################################################################################


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
