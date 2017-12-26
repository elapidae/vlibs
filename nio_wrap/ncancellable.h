#ifndef NCANCELLABLE_H
#define NCANCELLABLE_H

#include "nobject.h"
#include <gio/gio.h>
#include <memory>

//=======================================================================================
class NCancellable : public NObject
{
public:
    NCancellable();

private:
    NCancellable( GCancellable *c );

    friend class NFile;
    friend class NInputStream;
    friend class NOutputStream;
    friend class NSocket;
    GCancellable *_g_cancellable;
};
//=======================================================================================

#endif // NCANCELLABLE_H
