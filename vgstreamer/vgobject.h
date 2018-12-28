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
