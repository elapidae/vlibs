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


#include "vgstbin.h"

#include <gst/gst.h>

//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
VGstBin::VGstBin( const std::string &name )
    : VGstElement( gst_bin_new(name.c_str()) )
    , _raw_gst_bin( GST_BIN(ptr_gst_element()) )
{}
#pragma GCC diagnostic pop
//=======================================================================================
VGstBin::VGstBin( GstBin *raw )
    : VGstElement( VGstElement::cast(raw) )
    , _raw_gst_bin( raw )
{}
//=======================================================================================
void VGstBin::add( VGstElement *elem )
{
    gst_bin_add( _raw_gst_bin, elem->ptr_gst_element() );
}
//=======================================================================================
