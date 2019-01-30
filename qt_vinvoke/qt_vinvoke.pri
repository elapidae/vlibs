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

