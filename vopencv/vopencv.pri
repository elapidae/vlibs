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
    # NB! use 'DEFINES += V_OPENCV_USE_CUDA' before including for activate cuda section.

    CONFIG    *= link_pkgconfig
    PKGCONFIG *= opencv
    CONFIG *= c++11

    # Check and control this var, please...
    isEmpty(OPENCV_DIR): OPENCV_DIR = /home/nvidia/opencv/build
    message( "OPENCV_DIR sets to $$OPENCV_DIR" )
    INCLUDEPATH += $$OPENCV_DIR/include/

    contains(DEFINES, V_OPENCV_USE_CUDA) {


        LIBS += -L$$OPENCV_DIR/lib \
                    -lopencv_core -lopencv_imgcodecs -lopencv_highgui           \
                    -lopencv_features2d -lopencv_videoio -lopencv_imgproc       \
                    -lopencv_calib3d -lopencv_cudaarithm -lopencv_cudafilters   \
                    -lopencv_cudawarping -lopencv_cudaimgproc -lopencv_ml       \
                    -lopencv_video -lopencv_dnn

    }

    include( $$VLIBS_DIR/vlog/vlog.pri )
    include( $$VLIBS_DIR/vimage/vimage.pri )
    #include( $$VLIBS_DIR/vimage/vimage_opencv.pri )
    OTHER_FILES += $$PWD/vopencv.cmake
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vopencv


    HEADERS     += $$VLIBS_DIR/vopencv/vcv_includes.h
    HEADERS     += $$VLIBS_DIR/vopencv/vcv_image.h

    SOURCES     += $$VLIBS_DIR/vopencv/vcv_image.cpp
    SOURCES     += $$VLIBS_DIR/vopencv/vcv_includes.cpp
}
# vopencv.pri
#========================================================================================
