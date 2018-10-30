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
