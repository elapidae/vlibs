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
# vcrc.pri
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
isEmpty(qi_vcrc) {
    qi_vcrc = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vcrc appended ===")

    isEmpty(VLIBS_DIR): error("vcrc: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    CONFIG *= c++11
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vcrc

    
    HEADERS     += $$VLIBS_DIR/vcrc/vcrc.h 
    
    SOURCES     += $$VLIBS_DIR/vcrc/vcrc.cpp 
}
# vcrc.pri
#========================================================================================
