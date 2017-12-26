#include "ncancellable.h"

#include <impl/ncastinghelper.h>

NCancellable::NCancellable()
    : NCancellable( g_cancellable_new() )
{}

NCancellable::NCancellable( GCancellable *c )
    : NObject( gcast_to_gobject(c) )
    , _g_cancellable( c )
{}
