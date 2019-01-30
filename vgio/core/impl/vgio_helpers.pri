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
# impl.pri
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
isEmpty(qi_vgio_core_impl) {
    qi_vgio_core_impl = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vgio_core_impl appended ===")

    isEmpty(VLIBS_DIR): error("Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vgio/core/vgio_core.pri )

    INCLUDEPATH += $$VLIBS_DIR/vgio/core

    HEADERS     += $$VLIBS_DIR/vgio/core/impl/vgio_casting_helper.h

    HEADERS     += $$VLIBS_DIR/vgio/core/impl/vgio_converting_helper.h
    SOURCES     += $$VLIBS_DIR/vgio/core/impl/vgio_converting_helper.cpp
    #>>> Stop your code here ------------------------------------------------------------

}
# impl.pri
#========================================================================================
