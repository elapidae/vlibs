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


#ifndef VGSTUDPSRC_H
#define VGSTUDPSRC_H


/* https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gst-plugins-good/html/
gst-plugins-good-plugins-udpsrc.html */

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
