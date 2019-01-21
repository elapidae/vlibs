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
# vlog_qt.pri
#========================================================================================


#========================================================================================
isEmpty(qi_vlog_qt) {
    qi_vlog_qt = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vlog_qt appended ===")

    isEmpty(VLIBS_DIR): error("vlog_qt: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    #   NB! Вычищен руками, оставлена только базовая часть. Файловые логгеры подключаются
    #       через include( $$VLIBS_DIR/vlog/vfilelog.pri )

    include( $$VLIBS_DIR/vlog/vlog.pri )

    HEADERS     += $$VLIBS_DIR/vlog/vlog_qt.h
    SOURCES     += $$VLIBS_DIR/vlog/vlog_qt.cpp

    #>>> Stop your code here ------------------------------------------------------------

}
# vlog_qt.pri
#========================================================================================
