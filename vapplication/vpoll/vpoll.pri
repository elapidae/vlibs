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


#========================================================================================
# vpoll.pri
#   Manual edited
#========================================================================================


#========================================================================================
isEmpty(qi_vpoll) {
    qi_vpoll = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vpoll appended ===")

    isEmpty(VLIBS_DIR): error("vpoll: Need VLIBS_DIR correct path.")

    include( $$VLIBS_DIR/vstd/vstd.pri )

    HEADERS     += $$VLIBS_DIR/vapplication/vpoll/vpoll.h
    SOURCES     += $$VLIBS_DIR/vapplication/vpoll/vpoll.cpp
}
# vpoll.pri
#========================================================================================
