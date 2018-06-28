#include "profiler.hpp"

#include "vlog_pretty.h"

#include <opencv2/core.hpp>
#include <cstdint>

namespace profiler
{
    void print_delay( const int64_t t0, const char* message )
    {
        double secs = ( cv::getTickCount() - t0 ) / cv::getTickFrequency();
        vdeb << message << "Secs: " << secs;
    }
}
