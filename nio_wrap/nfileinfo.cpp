#include "nfileinfo.h"


#include "impl/ncastinghelper.h"



NFileInfo::NFileInfo( GFileInfo *fi )
    : NObject( gcast_to_gobject(fi) )
    , _g_file_info( fi )
{}
