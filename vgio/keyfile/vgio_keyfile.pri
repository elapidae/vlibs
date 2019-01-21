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
# keyfile.pri
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
isEmpty(qi_vgio_keyfile) {
    qi_vgio_keyfile = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vgio::keyfile appended ===")

    isEmpty(VLIBS_DIR): error("vgio_keyfile: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vgio/core/impl/vgio_helpers.pri )
    include( $$VLIBS_DIR/vgio/error/vgio_error.pri )

    INCLUDEPATH += $$VLIBS_DIR/vgio/keyfile

    HEADERS     += $$VLIBS_DIR/vgio/keyfile/vgio_keyfile.h
    SOURCES     += $$VLIBS_DIR/vgio/keyfile/vgio_keyfile.cpp

    HEADERS     += $$VLIBS_DIR/vgio/keyfile/vgio_keyfile_schema.h
    SOURCES     += $$VLIBS_DIR/vgio/keyfile/vgio_keyfile_schema.cpp

    OTHER_FILES += $$VLIBS_DIR/vgio/keyfile/README
    #>>> Stop your code here ------------------------------------------------------------

}
# keyfile.pri
#========================================================================================
