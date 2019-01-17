#ifndef VCV_INCLUDES_H
#define VCV_INCLUDES_H



#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>



#ifdef V_OPENCV_USE_CUDA
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudafilters.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudawarping.hpp>
#endif



#endif // VCV_INCLUDES_H
