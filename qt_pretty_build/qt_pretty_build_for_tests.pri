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




isEmpty(qt_pretty_build_for_tests) {
    qt_pretty_build_for_tests = 1;
    isEmpty(qi_not_print_pri_messages): message("=== qt_pretty_build_for_tests ===")

#    system()
    VTEST_BUILD_DIR = ../test_builds

    # каталог, куда загонять результирующий исполняемый файл
    DESTDIR = $$VTEST_BUILD_DIR/$$TARGET

    # промежуточные файлы, созданные moc
    MOC_DIR = $$VTEST_BUILD_DIR/$$TARGET/moc

    # объектные файлы
    OBJECTS_DIR = $$VTEST_BUILD_DIR/$$TARGET/obj

    # промежуточные файлы, созданные компилятором
    # ресурсов Qt (rcc)
    RCC_DIR = $$VTEST_BUILD_DIR/$$TARGET/rcc

    # промежуточные файлы, созданные компилятором
    # файлов форм (.ui) Qt (uic)
    UI_DIR = $$VTEST_BUILD_DIR/$$TARGET/uic
}


