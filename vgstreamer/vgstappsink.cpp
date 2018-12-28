#include "vgstappsink.h"

#include <gst/app/app.h>


//g_object_set( appsink,
//              "emit-signals", TRUE,
//              "caps", caps,
//              "max-buffers", 1,
//              "drop", FALSE,
//              "sync", FALSE,
//              NULL );

//gst_app_sink_set_emit_signals(appsink, TRUE);

//g_signal_connect(appsink, "new-sample", G_CALLBACK(on_sample_ready),
//                 static_cast<gpointer>(&decoder));

//=======================================================================================
static GstFlowReturn on_sample_ready(GstAppSink* appSink, gpointer userData)
{
    (void)appSink;
    auto self = static_cast<VGstAppSink*>( userData );
    self->new_sample( self->pull_sample() );
    return GST_FLOW_OK;
}
//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
//====================
VGstAppSink::VGstAppSink( const std::string &name )
    : VGstElement( VGstElement::factory_make("appsink",name) )
{
    _raw_gst_app_sink = GST_APP_SINK( ptr_gst_element() );

    set_emit_signals( true );
    g_signal_connect( _raw_gst_app_sink,
                      "new-sample",
                      G_CALLBACK(on_sample_ready),
                      this );
}
//====================
#pragma GCC diagnostic pop
//=======================================================================================
void VGstAppSink::set_emit_signals( bool need_emit )
{
    gst_app_sink_set_emit_signals( _raw_gst_app_sink, need_emit );
}
//=======================================================================================
void VGstAppSink::set_max_buffers( uint max_bufs )
{
    gst_app_sink_set_max_buffers( _raw_gst_app_sink, max_bufs );
}
//=======================================================================================
void VGstAppSink::set_drop( bool drop_old_bufs )
{
    gst_app_sink_set_drop( _raw_gst_app_sink, drop_old_bufs ? TRUE : FALSE );
}
//=======================================================================================
void VGstAppSink::set_sync( bool do_sync )
{
    set( "sync", do_sync );
}
//=======================================================================================
VGstSample VGstAppSink::pull_sample()
{
    return gst_app_sink_pull_sample( _raw_gst_app_sink );
}
//=======================================================================================

