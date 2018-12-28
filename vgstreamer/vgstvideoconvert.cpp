#include "vgstvideoconvert.h"



VGstVideoConvert::VGstVideoConvert( const std::string &name )
    : VGstElement( factory_make("videoconvert", name) )
{}
