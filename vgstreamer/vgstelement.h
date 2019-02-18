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


#ifndef VGSTELEMENT_H
#define VGSTELEMENT_H


/* https://gstreamer.freedesktop.org/data/doc/gstreamer/1.14/gstreamer/
html/GstElement.html */

//GObject
//  ╰── GInitiallyUnowned
//      ╰── GstObject
//          ╰── GstElement
//              ╰── GstBin


#include "vgobject.h"
#include "vgst_init.h"

typedef struct _GstElement GstElement;


class VGstElement : public VGObject
{
public:
    static GstElement* cast( void* any );
    static GstElement* factory_make( const std::string &type,
                                     const std::string &name = {} );

    void set_caps( const VGstCaps& caps );

    //  Возвращает dst.
    VGstElement& link( VGstElement& dst );

    // Должны повторять значения соответствующих перечислений в GStreamer-e.
    enum class State {
        VOID_PENDING    = 0,
        NULL_           = 1,
        READY           = 2,
        PAUSED          = 3,
        PLAYING         = 4
    };

    enum class StateChangeReturn {
        FAILURE         = 0,
        SUCCESS         = 1,
        ASYNC           = 2,
        NO_PREROLL      = 3
    };

    StateChangeReturn set_state( State );
    // Проверяет, чтобы было success|async.
    void set_state_playing();
    void set_state_null();

protected:
    friend class VGstLibAV;
    VGstElement( GstElement* gelem );

    friend class VGstBin;
    GstElement* ptr_gst_element();
    const GstElement* ptr_gst_element() const;

private:
    static StateChangeReturn _set_state( GstElement* elem, State s );
    static void _set_state_null( GstElement* elem );

    std::shared_ptr<GstElement> _raw_gst_element;
    VGst_Init _init;
};

#endif // VGSTELEMENT_H
