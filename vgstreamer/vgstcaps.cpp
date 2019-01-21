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


#include "vgstcaps.h"

#include <assert.h>
#include <gst/gst.h>
#include "impl/vgio_converting_helper.h"

//=======================================================================================
GstCaps *VGstCaps::new_simple( const std::string &media_name )
{
    auto res = gst_caps_new_empty_simple( media_name.c_str() );
    assert( res );
    return res;
}
//=======================================================================================
VGstCaps VGstCaps::application_x_rtp()
{
    return new_simple( "application/x-rtp" );
}
//=======================================================================================
VGstCaps VGstCaps::video_x_raw()
{
    return new_simple( "video/x-raw" );
}
//=======================================================================================

//=======================================================================================
VGstCaps::VGstCaps( const std::string &media_name )
    : VGstCaps( new_simple(media_name) )
{}
//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
void VGstCaps::set_simple( const std::string &field_name, int val )
{
    gst_caps_set_simple( ptr_gst_caps(),
                         field_name.c_str(), G_TYPE_INT, val, NULL );
}
//=======================================================================================
void VGstCaps::set_simple( const std::string &field_name, const std::string &val )
{
    gst_caps_set_simple( ptr_gst_caps(),
                         field_name.c_str(), G_TYPE_STRING, val.c_str(), NULL );
}
#pragma GCC diagnostic pop
//=======================================================================================
void VGstCaps::set_encoding_name( const std::string &ename )
{
    set_simple( "encoding-name", ename );
}
//=======================================================================================
void VGstCaps::set_payload( int payload )
{
    set_simple( "payload", payload );
}
//=======================================================================================
void VGstCaps::set_format( const std::string &fmt )
{
    set_simple( "format", fmt );
}
//=======================================================================================
void VGstCaps::set_format_RGB()
{
    set_format( "RGB" );
}
//=======================================================================================
uint VGstCaps::struct_count() const
{
    return gst_caps_get_size( ptr_gst_caps() );
}
//=======================================================================================
const VGstStructure::Loaned VGstCaps::struct_at( uint idx ) const
{
    assert( idx < struct_count() );
    auto s = VGstStructure::loan( gst_caps_get_structure(ptr_gst_caps(),idx) );
    return VGstStructure::Loaned( _raw_gst_caps, s );
}
//=======================================================================================
std::string VGstCaps::to_string() const
{
    return vgio::_impl::convert_and_free( gst_caps_to_string(ptr_gst_caps()) );
}
//=======================================================================================
VGstCaps::VGstCaps( GstCaps *caps )
    : _raw_gst_caps( caps, gst_caps_unref )
{}
//=======================================================================================
GstCaps *VGstCaps::ptr_gst_caps()
{
    return _raw_gst_caps.get();
}
//=======================================================================================
const GstCaps *VGstCaps::ptr_gst_caps() const
{
    return _raw_gst_caps.get();
}
//=======================================================================================
