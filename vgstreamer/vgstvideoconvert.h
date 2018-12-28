#ifndef VGSTVIDEOCONVERT_H
#define VGSTVIDEOCONVERT_H

// https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gst-plugins-base-plugins/html/gst-plugins-base-plugins-videoconvert.html

//GObject
//╰── GInitiallyUnowned
//    ╰── GstObject
//        ╰── GstElement
//            ╰── GstBaseTransform
//                ╰── GstVideoFilter
//                    ╰── GstVideoConvert

#include "vgstelement.h"


class VGstVideoConvert : public VGstElement
{
public:
    VGstVideoConvert( const std::string& name = {} );
};


#endif // VGSTVIDEOCONVERT_H
