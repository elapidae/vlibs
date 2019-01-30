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
