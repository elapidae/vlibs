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
# vopencv.pri
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
isEmpty(qi_vopencv) {
    qi_vopencv = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vopencv appended ===")

    isEmpty(VLIBS_DIR): error("vopencv: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    CONFIG    *= link_pkgconfig
    PKGCONFIG *= opencv

    OPENCV_USE_CUDA = 1
    isEmpty(OPENCV_USE_CUDA) {
        DEFINES += V_OPENCV_USE_CUDA
    }

    include( $$VLIBS_DIR/vlog/vlog.pri )
    OTHER_FILES += $$PWD/vopencv.cmake
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vopencv

    
    HEADERS     += $$VLIBS_DIR/vopencv/vcv_image.h 
    
    SOURCES     += $$VLIBS_DIR/vopencv/vcv_image.cpp 
}
# vopencv.pri
#========================================================================================

HEADERS += \
    $$PWD/vcv_includes.h

SOURCES += \
    $$PWD/vcv_includes.cpp
