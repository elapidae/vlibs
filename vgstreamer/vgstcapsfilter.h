#ifndef VGSTCAPSFILTER_H
#define VGSTCAPSFILTER_H

// https://gstreamer.freedesktop.org/data/doc/gstreamer/1.13/gstreamer-plugins/html/gstreamer-plugins-capsfilter.html

//GObject
//   ╰── GInitiallyUnowned
//       ╰── GstObject
//           ╰── GstElement
//               ╰── GstBaseTransform
//                   ╰── GstCapsFilter

#include "vgstelement.h"
#include "vgstcaps.h"

class VGstCapsFilter : public VGstElement
{
public:
    explicit VGstCapsFilter( const std::string& name = {} );
    VGstCapsFilter( const VGstCaps& caps, const std::string& name = {} );

private:
};


#endif // VGSTCAPSFILTER_H
