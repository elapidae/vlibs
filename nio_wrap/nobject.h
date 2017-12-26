#ifndef NOBJECT_H
#define NOBJECT_H

#include <glib-object.h>
#include <memory>



//=======================================================================================
class NObject
{
public:

    bool is_null() const;

    uint ref_count() const;
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
