#include "vgstsample.h"

#include <gst/gst.h>
#include <assert.h>


//=======================================================================================
class VImage_Gst : public VImage
{
    const int w, h, stride;
    const u_char* raw_data;

public:
    VImage_Gst( int w, int h, int stride, const u_char* raw)
        : w(w), h(h), stride(stride), raw_data(raw)
    {}

    virtual Format format() const
    { return Format::RGB_888; }

    virtual int width() const
    { return w; }

    virtual int height() const
    { return h; }

    virtual int bytes_per_line() const
    { return stride; }

    virtual const data_t* data() const
    { return raw_data; }
};
//=======================================================================================


//=======================================================================================
VGstBuffer VGstSample::get_buffer()
{
    auto res = gst_sample_get_buffer( ptr_gst_sample() );
    assert( res );
    gst_buffer_ref( res );
    //return VGstBuffer::loan( res );
    return res;
}
//=======================================================================================
VGstCaps VGstSample::get_caps()
{
    auto res = gst_sample_get_caps( ptr_gst_sample() );
    assert( res );
    gst_caps_ref( res );
    return res;
}
//=======================================================================================
VGstSample::VGstSample( GstSample* sample )
    : _raw_gst_sample( sample, gst_sample_unref )
{
    assert( sample );
}
//=======================================================================================
GstSample *VGstSample::ptr_gst_sample()
{
    return _raw_gst_sample.get();
}
//=======================================================================================
const GstSample *VGstSample::ptr_gst_sample() const
{
    return _raw_gst_sample.get();
}
//=======================================================================================
void VGstSample::extract_image( const VImageReceiver &vimg_rec )
{
    auto caps = get_caps();
    assert( caps.struct_count() == 1 );
    auto struc = caps.struct_at( 0 );

    auto width  = struc().get_width();
    auto height = struc().get_height();
    auto format = struc().get_format();
    assert( width > 0 && height > 0 );
    assert( format == "RGB" );

    auto buffer = get_buffer();
    auto mapinfo = buffer.map_info_read();
    auto stride = width * 3; // 3 is RGB pixel.
    assert( stride * height == mapinfo.ssize() && "!! NEED TO CALC STRIDE !!" );

    auto data = mapinfo.raw_data();
    VImage_Gst vimage( width, height, stride, data );

    vimg_rec( vimage );
}
//=======================================================================================

//auto sample = gst_app_sink_pull_sample(appSink);
//assert (sample != NULL);

//auto sampleBuffer = gst_sample_get_buffer(sample);
//assert(sampleBuffer != NULL);

//auto caps = gst_sample_get_caps(sample);
////g_object_get( G_OBJECT(caps), "width", &w, "height", &h, NULL );
//vdeb << "caps-size:" << gst_caps_get_size(caps);
//auto struc = gst_caps_get_structure(caps,0);
////    auto vs = VGstStructure::loan( struc );
////    vdeb << vs.field_names();
////    vdeb << vs.get_width() << vs.get_height() << vs.get_format();

//gst_buffer_map(sampleBuffer, &mapInfo, GST_MAP_READ);

//const int byteCount = mapInfo.size;
//vdeb << mapInfo.flags;
//vdeb << mapInfo.size << mapInfo.maxsize;

////QImage(uchar *data, int width, int height, Format format
////QImage img( rawData, 484,304,QImage::Format_RGB888);
////img.save("test.jpeg");
//exit(1);
