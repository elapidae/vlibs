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
