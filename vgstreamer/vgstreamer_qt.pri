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
# vgstreamer.pri
#   Edited manually
#========================================================================================


#========================================================================================
isEmpty(qi_vgstreamer_qt) {
    qi_vgstreamer_qt = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vgstreamer_qt appended ===")

    isEmpty(VLIBS_DIR): error("vgstreamer: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------

    include( $$VLIBS_DIR/vgstreamer/vgstreamer.pri )
    include( $$VLIBS_DIR/vimage/vimage_qt.pri )

    HEADERS     += $$VLIBS_DIR/vgstreamer/rtp_sink_qt.h
    SOURCES     += $$VLIBS_DIR/vgstreamer/rtp_sink_qt.cpp

    #>>> Stop your code here ------------------------------------------------------------
}
# vgstreamer.pri
#========================================================================================
