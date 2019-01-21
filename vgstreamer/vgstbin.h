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


#ifndef VGSTBIN_H
#define VGSTBIN_H


//=======================================================================================
// https://gstreamer.freedesktop.org/data/doc/gstreamer/1.13/gstreamer/html/GstBin.html

//GObject
//╰── GInitiallyUnowned
//    ╰── GstObject
//        ╰── GstElement
//            ╰── GstBin
//                ╰── GstPipeline
//=======================================================================================


//=======================================================================================
#include "vgstelement.h"
//=======================================================================================


//=======================================================================================
typedef struct _GstBin GstBin;
//=======================================================================================


//=======================================================================================
class VGstBin : public VGstElement
{
public:
    explicit VGstBin( const std::string& name = {} );

    void add( VGstElement* elem );

    template< typename ... Elems >
    void add( VGstElement* elem1, Elems* ... elems );

protected:
    VGstBin( GstBin* raw );

private:
    GstBin* _raw_gst_bin;
};
//=======================================================================================


//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
template< typename ... Elems >
void VGstBin::add( VGstElement* elem1, Elems* ... elems )
{
    add( elem1 );
    add( elems... );
}
//=======================================================================================


#endif // VGSTBIN_H
