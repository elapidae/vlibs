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



isEmpty(qi_map2d_widget) {
    qi_map2d_widget = 1;

    isEmpty(qi_not_print_pri_messages): message("=== Map2D widget appended ===")

    QT *= opengl

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    include( $$VLibs_Dir/vsignal/vsignal.pri )

    INCLUDEPATH += $$VLibs_Dir/map2d_widget

    HEADERS     += $$VLibs_Dir/map2d_widget/map2d_widget.h
    SOURCES     += $$VLibs_Dir/map2d_widget/map2d_widget.cpp
}

