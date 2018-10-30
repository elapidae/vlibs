#include "vgobject.h"

#include <glib-object.h>


//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
GObject *VGObject::cast( void *any )
{
    return G_OBJECT( any );
}
#pragma GCC diagnostic pop
//=======================================================================================
VGObject::VGObject( GObject *gobj )
    : _g_object( gobj, g_object_unref )
{}
//=======================================================================================
//VGObject::~VGObject()
//{
//    g_object_unref( _g_object );
//}
//=======================================================================================
GObject *VGObject::my_object()
{
    return _g_object.get();
}
//=======================================================================================
const GObject *VGObject::my_object() const
{
    return _g_object.get();
}
//=======================================================================================
void VGObject::set( const std::string &prop_name, int val )
{
    g_object_set( my_object(), prop_name.c_str(), val, NULL );
}
//=======================================================================================
void VGObject::set( const std::string &prop_name, bool val )
{
    gboolean b = val ? TRUE : FALSE;
    g_object_set( my_object(), prop_name.c_str(), b, NULL );
}
//=======================================================================================
void VGObject::set( const VGstCaps& caps )
{
    g_object_set( my_object(), "caps", caps.ptr_gst_caps(), NULL );
}
//=======================================================================================
