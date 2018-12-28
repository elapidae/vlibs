#ifndef VGSTLIBAV_H
#define VGSTLIBAV_H


// https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gst-libav-plugins/html/gst-libav-plugins-plugin-libav.html


#include "vgstelement.h"

class VGstLibAV
{
public:
    static VGstElement avdec_h264( const std::string& name = {} );
};



#endif // VGSTLIBAV_H
