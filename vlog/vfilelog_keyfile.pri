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




isEmpty(qi_vfilelog_keyfile) {
    qi_vfilelog_keyfile = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vfilelog_keyfile appended ===")

    isEmpty(VLIBS_DIR): error("vfilelog_keyfile: Need VLIBS_DIR correct path.")
    include($$VLIBS_DIR/vlog/vfilelog.pri)

    HEADERS     += $$VLIBS_DIR/vlog/vfilelog_keyfile.h
    SOURCES     += $$VLIBS_DIR/vlog/vfilelog_keyfile.cpp
}
