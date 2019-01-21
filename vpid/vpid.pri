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
# vpid.pri
#
#
# NB! Этот файл правлен руками, постарайтесь не регенерировать.
#
#   Устаревший класс, будет перенесен в VApplication.
#
#========================================================================================


#========================================================================================
isEmpty(qi_vpid) {
    qi_vpid = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vpid appended ===")

    isEmpty(VLIBS_DIR): error("Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vlog/vlog.pri )
    include( $$VLIBS_DIR/vdir/vdir.pri )
    include( $$VLIBS_DIR/voutfile/voutfile.pri )
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vpid

    
    HEADERS     += $$VLIBS_DIR/vpid/vpid_saver.h 
    
    SOURCES     += $$VLIBS_DIR/vpid/vpid_saver.cpp 
}
# vpid.pri
#========================================================================================
