#ifndef VGSTUDPSRC_H
#define VGSTUDPSRC_H


//=======================================================================================
// https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gst-plugins-good/html/gst-plugins-good-plugins-udpsrc.html

//GObject
//   ╰── GInitiallyUnowned
//       ╰── GstObject
//           ╰── GstElement
//               ╰── GstBaseSrc
//                   ╰── GstPushSrc
//                       ╰── GstUDPSrc
//=======================================================================================


//=======================================================================================
#include "vgstelement.h"
//=======================================================================================


//=======================================================================================
struct GstUDPSrc;
//=======================================================================================


class VGstUdpSrc : public VGstElement
{
public:
    static VGstUdpSrc make( const std::string& name, uint16_t port = 0 );
    static VGstUdpSrc make( uint16_t port );

    void set_port( uint16_t port );

private:
    VGstUdpSrc( GstElement* usrc );

    //GstUDPSrc* gst_udp_src();
    //const GstUDPSrc* gst_udp_src() const;
    //GstUDPSrc* _gst_udp_src;
};
//=======================================================================================


#endif // VGSTUDPSRC_H
