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


#include "vgstudpsrc.h"

#include <assert.h>
#include <gst/gst.h>

//#include <gst/net/gstnet.h>


//=======================================================================================
VGstUdpSrc VGstUdpSrc::make( const std::string &name, uint16_t port )
{
    auto udpsrc = factory_make( "udpsrc", name.c_str() );
    assert( udpsrc );
    VGstUdpSrc res( udpsrc );

    if ( port != 0 )
        res.set_port( port );

    return res;
}
//=======================================================================================
VGstUdpSrc VGstUdpSrc::make( uint16_t port )
{
    return make( "", port );
}
//=======================================================================================
void VGstUdpSrc::set_port( uint16_t port )
{
    int iport = port;
    set( "port", iport );
}
//=======================================================================================
VGstUdpSrc::VGstUdpSrc( GstElement *usrc )
    : VGstElement( usrc )
{}
//=======================================================================================
