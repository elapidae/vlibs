#ifndef VGSTAPPSINK_H
#define VGSTAPPSINK_H

// https://gstreamer.freedesktop.org/data/doc/gstreamer/1.13/gst-plugins-base-libs/html/gst-plugins-base-libs-appsink.html

//  В документации по адресу выше нету иерархии наследования, но он точно элемент.


#include "vgstelement.h"
#include "vgstsample.h"

#include "../vsignal/vsignal.h"

typedef struct _GstAppSink GstAppSink;



class VGstAppSink : public VGstElement
{
public:

    VSignal<VGstSample> new_sample;

    VGstAppSink( const std::string& name = {} );

    void set_emit_signals( bool need_emit );
    void set_max_buffers( uint max_bufs );
    void set_drop( bool drop_old_bufs );
    void set_sync( bool do_sync );

    VGstSample pull_sample();

private:
    GstAppSink* _raw_gst_app_sink;
};



#endif // VGSTAPPSINK_H
