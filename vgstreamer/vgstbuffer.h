#ifndef VGSTBUFFER_H
#define VGSTBUFFER_H


//=======================================================================================
// https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gstreamer/html/GstBuffer.html#GstBufferFlags

//GBoxed
//╰── GstBuffer
//=======================================================================================


//=======================================================================================
#include <memory>
#include <functional>
#include "../vimage/vimage.h"
#include "vgstmapinfo.h"
//=======================================================================================


//=======================================================================================
typedef struct _GstBuffer GstBuffer;
//=======================================================================================


//=======================================================================================
class VGstBuffer
{
public:
    //static VGstBuffer loan( GstBuffer* b );

    VGstMapInfo map_info_read();

private:
    friend class VGstSample;
    //VGstBuffer( GstBuffer* b, bool need_unref );
    VGstBuffer( GstBuffer* b );

    std::shared_ptr<GstBuffer> _raw_gst_buffer;
};
//=======================================================================================


#endif // VGSTBUFFER_H
