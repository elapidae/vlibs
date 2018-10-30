#include "vgst_init.h"

#include <gst/gst.h>

std::atomic_int VGst_Init::_count {0};

VGst_Init::VGst_Init()
{
    if ( ++_count == 1 )
        gst_init(nullptr,nullptr);
}

