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


#include "vgststructure.h"

#include <assert.h>
#include <gst/gst.h>
#include "impl/vgio_converting_helper.h"
#include "verror.h"

//=======================================================================================
static void not_free( GstStructure* )
{}
//=======================================================================================
VGstStructure::VGstStructure( GstStructure *gstruct, bool call_free )
    : _raw_gst_structure( gstruct, call_free ? gst_structure_free : not_free )
{}
//=======================================================================================
GstStructure *VGstStructure::ptr_gst_structure()
{
    return _raw_gst_structure.get();
}
//=======================================================================================
const GstStructure *VGstStructure::ptr_gst_structure() const
{
    return _raw_gst_structure.get();
}
//=======================================================================================
//bool VGstStructure::has_field( const std::string& fieldname ) const
//{
//    return TRUE == gst_structure_has_field( _raw_gst_structure.get(),
//                                            fieldname.c_str() );
//}
//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
bool VGstStructure::has_int_field( const std::string& fieldname ) const
{
    return TRUE == gst_structure_has_field_typed( _raw_gst_structure.get(),
                                                  fieldname.c_str(),
                                                  G_TYPE_INT );
}
//=======================================================================================
bool VGstStructure::has_string_field( const std::string& fieldname ) const
{
    return TRUE == gst_structure_has_field_typed( _raw_gst_structure.get(),
                                                  fieldname.c_str(),
                                                  G_TYPE_STRING );
}
#pragma GCC diagnostic pop
//=======================================================================================
int VGstStructure::get_int( const std::string& fieldname ) const
{
    assert( has_int_field(fieldname) );
    int res = -1;
    auto ok = gst_structure_get_int( ptr_gst_structure(), fieldname.c_str(), &res );
    assert( ok );
    return res;
}
//=======================================================================================
std::string VGstStructure::get_string(const std::string &fieldname) const
{
    assert( has_string_field(fieldname) );
    const char *res = gst_structure_get_string( ptr_gst_structure(), fieldname.c_str() );
    assert( res );
    return res;
}
//=======================================================================================
int VGstStructure::get_width() const
{
    return get_int( "width" );
}
//=======================================================================================
int VGstStructure::get_height() const
{
    return get_int( "height" );
}
//=======================================================================================
std::string VGstStructure::get_format() const
{
    return get_string( "format" );
}
//=======================================================================================
int VGstStructure::fields_count() const
{
    return gst_structure_n_fields( ptr_gst_structure() );
}
//=======================================================================================
std::string VGstStructure::field_name( uint idx ) const
{
    auto res = gst_structure_nth_field_name( ptr_gst_structure(), idx );
    //return vgio::_impl::convert_and_free( res );
    return res;
}
//=======================================================================================
std::vector<std::string> VGstStructure::field_names() const
{
    std::vector<std::string> res;
    for ( int i = 0; i < fields_count(); ++i )
        res.push_back( field_name(uint(i)) );
    return res;
}
//=======================================================================================
VGstStructure VGstStructure::loan( GstStructure *s )
{
    return {s, false};
}
//=======================================================================================


//=======================================================================================
class VGstStructure::Loaned::Pimpl
{
public:
    Pimpl( std::weak_ptr<GstCaps> w, VGstStructure s )
        : w(w), s(s)
    {}
    std::weak_ptr<GstCaps> w;
    VGstStructure s;
};
//=======================================================================================
VGstStructure &VGstStructure::Loaned::operator()()
{
    if ( p->w.lock() )
    {
        return p->s;
    }
    else
    {
        throw verror( "Cannot lock loaned structure." );
    }
}
//=======================================================================================
VGstStructure::Loaned::Loaned( const std::weak_ptr<GstCaps>& w,
                               const VGstStructure& s )
    : p( std::make_shared<Pimpl>(w, s) )
{}
//=======================================================================================
