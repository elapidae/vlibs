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


#ifndef VGOBJECT_H
#define VGOBJECT_H

//=======================================================================================
// https://developer.gnome.org/gobject/stable/gobject-The-Base-Object-Type
//=======================================================================================


#include <memory>
#include "vgstcaps.h"


//=======================================================================================
typedef struct _GObject GObject;
//=======================================================================================




//=======================================================================================
class VGObject
{
public:

protected:
    static GObject* cast( void* any );

    VGObject( GObject *gobj );
    //virtual ~VGObject();

    GObject *my_object();
    const GObject *my_object() const;

    void set( const std::string& prop_name, int val  );
    void set( const std::string& prop_name, bool val );
    void set( const VGstCaps& caps );

private:
    std::shared_ptr<GObject> _g_object;
};
//=======================================================================================


#endif // VGOBJECT_H
