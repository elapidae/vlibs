#include "vgstcapsfilter.h"




VGstCapsFilter::VGstCapsFilter( const std::string &name )
    : VGstElement( factory_make("capsfilter",name) )
{}

VGstCapsFilter::VGstCapsFilter( const VGstCaps &caps, const std::string &name )
    : VGstCapsFilter(name)
{
    set_caps( caps );
}

