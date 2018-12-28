#include "vgstbin.h"

#include <gst/gst.h>

//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
VGstBin::VGstBin( const std::string &name )
    : VGstElement( gst_bin_new(name.c_str()) )
    , _raw_gst_bin( GST_BIN(ptr_gst_element()) )
{}
#pragma GCC diagnostic pop
//=======================================================================================
VGstBin::VGstBin( GstBin *raw )
    : VGstElement( VGstElement::cast(raw) )
    , _raw_gst_bin( raw )
{}
//=======================================================================================
void VGstBin::add( VGstElement *elem )
{
    gst_bin_add( _raw_gst_bin, elem->ptr_gst_element() );
}
//=======================================================================================
