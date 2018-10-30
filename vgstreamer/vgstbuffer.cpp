#include "vgstbuffer.h"


#include <gst/gst.h>
#include <assert.h>

//=======================================================================================
//static void not_unref(GstBuffer*)
//{}
//=======================================================================================
//VGstBuffer VGstBuffer::loan( GstBuffer *b )
//{
//    return { b, false };
//}
//=======================================================================================
//VGstBuffer::VGstBuffer( GstBuffer *b , bool need_unref )
//    : _raw_gst_buffer( b, need_unref ? gst_buffer_unref : not_unref )
//{}
//=======================================================================================


//=======================================================================================
VGstMapInfo VGstBuffer::map_info_read()
{
    return VGstMapInfo::do_map_read( _raw_gst_buffer );
}
//=======================================================================================
VGstBuffer::VGstBuffer(GstBuffer *b)
    : _raw_gst_buffer( b, gst_buffer_unref )
{}
//=======================================================================================
