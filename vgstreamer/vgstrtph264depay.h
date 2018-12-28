#ifndef VGSTRTPH264DEPAY_H
#define VGSTRTPH264DEPAY_H


// https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gst-plugins-good/html/gst-plugins-good-plugins-rtph264depay.html


//GObject
//╰── GInitiallyUnowned
//    ╰── GstObject
//        ╰── GstElement
//            ╰── GstRTPBaseDepayload
//                ╰── GstRtpH264Depay

#include "vgstelement.h"

class VGstRtpH264Depay : public VGstElement
{
public:
    explicit VGstRtpH264Depay( const std::string& name = {} );
};

#endif // VGSTRTPH264DEPAY_H
