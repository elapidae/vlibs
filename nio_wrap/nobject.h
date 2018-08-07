#ifndef NOBJECT_H
#define NOBJECT_H

#include <glib-object.h>
#include <memory>
#include <string>


//=======================================================================================
class NObject
{
public:

    bool is_null() const;

    static uint ref_count( const GObject *obj );
    uint ref_count() const;

    static std::string type_name( const GObject *obj );
    std::string type_name() const;

protected:
    NObject( GObject *obj );
    ~NObject();

private:
    GObject *_g_object = nullptr;
    std::shared_ptr<GObject> _p;
};
//=======================================================================================


#endif // NOBJECT_H
