#ifndef RTP_SINK_H
#define RTP_SINK_H

#include "vgstappsink.h"
#include "vgstpipeline.h"
#include "vgstcapsfilter.h"
#include "vgstudpsrc.h"
#include "vgstrtph264depay.h"
#include "vgstlibav.h"
#include "vgstvideoconvert.h"
#include <stdint.h>

class RTP_Sink
{
public:
    RTP_Sink( uint16_t port );

    VSignal<VGstSample> new_sample;

private:
    VGstUdpSrc          udpsrc;
    VGstCapsFilter      capsf1;
    VGstRtpH264Depay    rtph264depay;
    VGstElement         avdec;
    VGstVideoConvert    videoconvert;
    VGstCapsFilter      capsf2;
    VGstAppSink         appsink;

    VGstPipeline        pipeline;
};

#endif // RTP_SINK_H
