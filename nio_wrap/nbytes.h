#ifndef NBYTES_H
#define NBYTES_H

#include <memory>
#include <glib.h>



//=======================================================================================
class NBytes final
{
public:
    const void *data() const;
    size_t size() const;

private:
    std::shared_ptr<GBytes> _p;

    friend class NInputStream;
    NBytes( GBytes *raw );
};
//=======================================================================================


#endif // NBYTES_H
