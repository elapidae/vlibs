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
# vlog.pri
#
#
# Этот файл сгенерирован автоматически.
#
# Вносить изменения можно между строк:
#   #<<< Start your code here
#   Сохраненный код.
#   #>>> Stop your code here
# Все остальные изменения будут перезаписаны.
#
#========================================================================================


#========================================================================================
isEmpty(qi_vlog) {
    qi_vlog = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vlog appended ===")

    isEmpty(VLIBS_DIR): error("vlog: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    #   NB! Вычищен руками, оставлена только базовая часть. Файловые логгеры подключаются
    #       через include( $$VLIBS_DIR/vlog/vfilelog.pri )

    include( $$VLIBS_DIR/vcat/vcat.pri )
    include( $$VLIBS_DIR/vchrono/vchrono.pri )

    INCLUDEPATH += $$VLIBS_DIR/vlog
    
    HEADERS     += $$VLIBS_DIR/vlog/vlog.h 
    #HEADERS     += $$VLIBS_DIR/vlog/vlog_pretty.h

    HEADERS     += $$VLIBS_DIR/vlog/verror.h
    SOURCES     += $$VLIBS_DIR/vlog/verror.cpp

    HEADERS     += $$VLIBS_DIR/vlog/vlogger.h
    SOURCES     += $$VLIBS_DIR/vlog/vlogger.cpp

    HEADERS     += $$VLIBS_DIR/vlog/vlogentry.h
    SOURCES     += $$VLIBS_DIR/vlog/vlogentry.cpp

    #>>> Stop your code here ------------------------------------------------------------

}
# vlog.pri
#========================================================================================
