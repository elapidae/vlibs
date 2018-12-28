#include "vgstrtph264depay.h"

VGstRtpH264Depay::VGstRtpH264Depay(const std::string &name)
    : VGstElement( factory_make("rtph264depay", name) )
{}
