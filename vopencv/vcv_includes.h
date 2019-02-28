/****************************************************************************************
**  
**  VLIBS codebase, NIIAS
**  
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**  
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


#ifndef VCV_INCLUDES_H
#define VCV_INCLUDES_H

#include "vimage.h"

#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>


#ifdef V_OPENCV_USE_CUDA
    #include <opencv2/cudaarithm.hpp>
    #include <opencv2/cudafilters.hpp>
    #include <opencv2/cudaimgproc.hpp>
    #include <opencv2/cudawarping.hpp>
    #include <opencv2/core/cuda.hpp>
    //#include <opencv2/core.hpp>
    //#include <opencv2/features2d.hpp>
    //#include <opencv2/highgui.hpp>
    //#include <opencv2/imgproc.hpp>
    //#include <opencv2/calib3d/calib3d.hpp>
    //#include <opencv2/core/utility.hpp>
    //#include <opencv2/ml.hpp>
    //#include <opencv2/video/tracking.hpp>
    //#include <opencv2/cudaarithm.hpp>
    //#include <opencv2/cudafilters.hpp>
    //#include <opencv2/cudaimgproc.hpp>
    //#include <opencv2/cudawarping.hpp>

#endif



#endif // VCV_INCLUDES_H
