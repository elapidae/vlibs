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
# vfilelog.pri
#========================================================================================


#========================================================================================
isEmpty(qi_vfilelog) {
    qi_vfilelog = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vfilelog appended ===")

    isEmpty(VLIBS_DIR): error("vfilelog: Need VLIBS_DIR correct path.")


#    include( $$VLIBS_DIR/vgio/keyfile/vgio_keyfile.pri )
    include( $$VLIBS_DIR/vlog/vlog.pri )
    include( $$VLIBS_DIR/vdir/vdir.pri )
    include( $$VLIBS_DIR/vthread/vthread.pri )
    include( $$VLIBS_DIR/voutfile/voutfile.pri )

# 2018-08-07 -- Потом разберусь...
    HEADERS     += $$VLIBS_DIR/vlog/vfilelog_threaded.h
#    HEADERS     += $$VLIBS_DIR/vlog/vfilelog_keyfile.h
    HEADERS     += $$VLIBS_DIR/vlog/vfilelog.h
    
    SOURCES     += $$VLIBS_DIR/vlog/vfilelog_threaded.cpp
#    SOURCES     += $$VLIBS_DIR/vlog/vfilelog_keyfile.cpp
    SOURCES     += $$VLIBS_DIR/vlog/vfilelog.cpp
}
# vfilelog.pri
#========================================================================================
