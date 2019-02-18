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


#include "rtp_sink.h"

//#include "../vlog/vlog_pretty.h"


RTP_Sink::RTP_Sink( uint16_t port )
    : udpsrc ( VGstUdpSrc::make(port)  )
    , avdec  ( VGstLibAV::avdec_h264() )
{
    appsink.new_sample.connect( &new_sample );

    {
        auto c1 = VGstCaps::application_x_rtp();
        c1.set_encoding_name("H264");
        c1.set_payload(96);
        capsf1.set_caps( c1 );
    }
    {
        auto c2 = VGstCaps::video_x_raw();
        c2.set_format_RGB();
        capsf2.set_caps( c2 );
    }
    {
        auto c3 = VGstCaps::video_x_raw();
        appsink.set_caps( c3 );
        appsink.set_max_buffers( 1 );
        appsink.set_drop( false );
        appsink.set_sync( false );
    }

    pipeline.add( &udpsrc,
                  &capsf1,
                  &rtph264depay,
                  &avdec,
                  &videoconvert,
                  &capsf2,
                  &appsink );

    udpsrc.link(capsf1)
          .link(rtph264depay)
          .link(avdec)
          .link(videoconvert)
          .link(capsf2)
          .link(appsink);

    pipeline.set_state_playing();
}
