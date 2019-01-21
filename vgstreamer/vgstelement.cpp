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


#include "vgstelement.h"

#include <gst/gst.h>
#include <assert.h>

//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
GstElement* VGstElement::cast( void *any )
{
    return GST_ELEMENT( any );
}
#pragma GCC diagnostic pop
//=======================================================================================
GstElement* VGstElement::factory_make( const std::string &type, const std::string &name )
{
    static VGst_Init _init;
    auto nameptr = name.empty() ? nullptr : name.c_str();
    auto res = gst_element_factory_make( type.c_str(), nameptr );
    assert( res );
    return res;
}
//=======================================================================================
void VGstElement::set_caps(const VGstCaps &caps)
{
    // VGObject::
    set( caps );
}
//=======================================================================================
VGstElement &VGstElement::link(VGstElement &dst)
{
    gst_element_link( ptr_gst_element(), dst.ptr_gst_element() );
    return dst;
}
//=======================================================================================
VGstElement::StateChangeReturn VGstElement::set_state( VGstElement::State s )
{
    return _set_state( ptr_gst_element(), s );
}
//=======================================================================================
void VGstElement::set_state_playing()
{
    auto res = set_state( State::PLAYING );

    if ( res != StateChangeReturn::ASYNC &&
         res != StateChangeReturn::SUCCESS )
    {
        throw std::runtime_error("Error during set playing.");
    }
}
//=======================================================================================
void VGstElement::set_state_null()
{
    set_state( State::NULL_ );
}
//=======================================================================================


//=======================================================================================
VGstElement::VGstElement( GstElement *gelem )
    : VGObject( VGObject::cast(gelem) )
    , _raw_gst_element( gelem, _set_state_null )
{}
//=======================================================================================
GstElement *VGstElement::ptr_gst_element()
{
    return _raw_gst_element.get();
}
//=======================================================================================
const GstElement *VGstElement::ptr_gst_element() const
{
    return _raw_gst_element.get();
}
//=======================================================================================
VGstElement::StateChangeReturn
VGstElement::_set_state( GstElement *elem, VGstElement::State s )
{
    auto res = gst_element_set_state( elem, GstState(s) );
    return StateChangeReturn( res );
}
//=======================================================================================
void VGstElement::_set_state_null( GstElement *elem )
{
    auto res = _set_state( elem, State::NULL_ );

    if ( res != StateChangeReturn::ASYNC &&
         res != StateChangeReturn::SUCCESS )
    {
        throw std::runtime_error("Error during set null.");
    }
}
//=======================================================================================
