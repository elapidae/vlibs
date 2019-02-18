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


#ifndef VGSTBUFFER_H
#define VGSTBUFFER_H


//=======================================================================================
/* https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gstreamer/html/
GstBuffer.html#GstBufferFlags */

//GBoxed
//╰── GstBuffer
//=======================================================================================


//=======================================================================================
#include <memory>
#include <functional>
#include "../vimage/vimage.h"
#include "vgstmapinfo.h"
//=======================================================================================


//=======================================================================================
typedef struct _GstBuffer GstBuffer;
//=======================================================================================


//=======================================================================================
class VGstBuffer
{
public:
    //static VGstBuffer loan( GstBuffer* b );

    VGstMapInfo map_info_read();

private:
    friend class VGstSample;
    //VGstBuffer( GstBuffer* b, bool need_unref );
    VGstBuffer( GstBuffer* b );

    std::shared_ptr<GstBuffer> _raw_gst_buffer;
};
//=======================================================================================


#endif // VGSTBUFFER_H
