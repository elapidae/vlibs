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


#ifndef VGSTSAMPLE_H
#define VGSTSAMPLE_H


//=======================================================================================
//https://gstreamer.freedesktop.org/data/doc/gstreamer/1.14/gstreamer/html/GstSample.html

//GBoxed
//╰── GstSample
//=======================================================================================


//=======================================================================================
#include <memory>
#include "vgstbuffer.h"
#include "vgstcaps.h"
//=======================================================================================

//=======================================================================================
typedef struct _GstSample GstSample;
//=======================================================================================


//=======================================================================================
class VGstSample
{
public:
    using VImageReceiver = std::function<void(const VImage&)>;
    void extract_image( const VImageReceiver& vimg_rec );

    VGstBuffer get_buffer();

    VGstCaps get_caps();

private:
    friend class VGstAppSink;
    VGstSample( GstSample* sample );

    std::shared_ptr<GstSample> _raw_gst_sample;
    GstSample* ptr_gst_sample();
    const GstSample* ptr_gst_sample() const;
};
//=======================================================================================


//=======================================================================================
//GstBuffer * 	gst_sample_get_buffer ()
//GstBufferList * 	gst_sample_get_buffer_list ()
//GstCaps * 	gst_sample_get_caps ()
//const GstStructure * 	gst_sample_get_info ()
//GstSegment * 	gst_sample_get_segment ()
//void 	gst_sample_set_buffer_list ()
//GstSample * 	gst_sample_new ()
//GstSample * 	gst_sample_ref ()
//void 	gst_sample_unref ()
//GstSample * 	gst_sample_copy ()
//=======================================================================================



#endif // VGSTSAMPLE_H
