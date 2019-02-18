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


#ifndef VGSTLIBAV_H
#define VGSTLIBAV_H


/* https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gst-libav-plugins/html/
gst-libav-plugins-plugin-libav.html */


#include "vgstelement.h"

class VGstLibAV
{
public:
    static VGstElement avdec_h264( const std::string& name = {} );
};



#endif // VGSTLIBAV_H
