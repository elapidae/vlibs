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


#include "vgstbuffer.h"


#include <gst/gst.h>
#include <assert.h>

//=======================================================================================
//static void not_unref(GstBuffer*)
//{}
//=======================================================================================
//VGstBuffer VGstBuffer::loan( GstBuffer *b )
//{
//    return { b, false };
//}
//=======================================================================================
//VGstBuffer::VGstBuffer( GstBuffer *b , bool need_unref )
//    : _raw_gst_buffer( b, need_unref ? gst_buffer_unref : not_unref )
//{}
//=======================================================================================


//=======================================================================================
VGstMapInfo VGstBuffer::map_info_read()
{
    return VGstMapInfo::do_map_read( _raw_gst_buffer );
}
//=======================================================================================
VGstBuffer::VGstBuffer(GstBuffer *b)
    : _raw_gst_buffer( b, gst_buffer_unref )
{}
//=======================================================================================
