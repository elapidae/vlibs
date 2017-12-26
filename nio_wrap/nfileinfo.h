#ifndef NFILEINFO_H
#define NFILEINFO_H

#include "nobject.h"
#include <gio/gio.h>

class NFileInfo : public NObject
{
public:


private:
    GFileInfo *_g_file_info = nullptr;

    friend class NFile;
    NFileInfo( GFileInfo *fi );
};



#endif // NFILEINFO_H
