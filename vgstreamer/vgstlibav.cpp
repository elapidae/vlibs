#include "vgstlibav.h"


VGstElement VGstLibAV::avdec_h264(const std::string &name)
{
    return VGstElement::factory_make( "avdec_h264", name );
}
