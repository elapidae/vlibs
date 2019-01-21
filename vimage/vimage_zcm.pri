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
#   UPD 2018-08-28      by Elapidae
#
#   Файл ручной работы, подтягивает ZCM к VImage.
#   Сделан без каких-либо включений источников, просто через шаблон, работает по полям
#   (см. vimage_zcm.h).
#
#   В общем, это include-отрыжка, т.к. не несет очевидной пользы, но, по крайнем мере,
#   скрашивает знакомство с ZCM_TYPES.
#
#========================================================================================


#========================================================================================
isEmpty(qi_zcm_image) {
    qi_zcm_image = 1;
    isEmpty(qi_not_print_pri_messages): message("=== zcm_image appended ===")

    isEmpty(VLIBS_DIR): error("zcm_image: Need VLIBS_DIR correct path.")
    include( $$VLIBS_DIR/vimage/vimage.pri )
    include( $$VLIBS_DIR/vzcm/vzcm.pri )

    HEADERS += $$VLIBS_DIR/vimage/vimage_zcm.h
}
#========================================================================================
