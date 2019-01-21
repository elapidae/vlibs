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
# vimagewidget.pri
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
isEmpty(qi_vimagewidget) {
    qi_vimagewidget = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vimagewidget appended ===")

    isEmpty(VLIBS_DIR): error("vimagewidget: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    QT += opengl
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vimagewidget

    
    HEADERS     += $$VLIBS_DIR/vimagewidget/vimagewidget.h 
    
    SOURCES     += $$VLIBS_DIR/vimagewidget/vimagewidget.cpp 
}
# vimagewidget.pri
#========================================================================================
