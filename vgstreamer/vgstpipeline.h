#ifndef VGSTPIPELINE_H
#define VGSTPIPELINE_H


// https://gstreamer.freedesktop.org/data/doc/gstreamer/1.9/gstreamer/html/GstPipeline.html


//GObject
// ╰── GInitiallyUnowned
//     ╰── GstObject
//         ╰── GstElement
//             ╰── GstBin
//                 ╰── GstPipeline

#include "vgstbin.h"


class VGstPipeline : public VGstBin
{
public:
    VGstPipeline();
};

#endif // VGSTPIPELINE_H
