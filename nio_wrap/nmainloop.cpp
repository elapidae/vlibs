#include "nmainloop.h"

#include <glib.h>
#include <assert.h>
//#include <vlogger.h>

#include <unordered_map>

using namespace std;

//=======================================================================================
NSource::NSource(GSource *s)
    : _g_source( s, g_source_unref )
{}
//=======================================================================================
void NSource::set_callback( GSourceFunc func, void *data, GDestroyNotify notify )
{
    g_source_set_callback( _g_source.get(), func, data, notify );
}
//=======================================================================================




//=======================================================================================
NMainContext NMainContext::default_ctx()
{
    return g_main_context_default();
}
//=======================================================================================
NMainContext::NMainContext()
    : _g_main_context( g_main_context_new(), g_main_context_unref )
{}
//=======================================================================================
//  Called from main_loop only...
NMainContext::NMainContext( GMainContext *ctx )
    : _g_main_context( ctx, g_main_context_unref )
{
    g_main_context_ref( ctx );
}
//=======================================================================================
uint NMainContext::attach( const NSource &source )
{
    return g_source_attach( source._g_source.get(), _g_main_context.get() );
}
//=======================================================================================


//=======================================================================================
NMainLoop::NMainLoop()
    : _g_main_loop( g_main_loop_new(NULL, FALSE), // default main loop
                    g_main_loop_unref )
{}
//=======================================================================================
NMainLoop::NMainLoop( const NMainContext &ctx, bool is_running )
    : _g_main_loop( g_main_loop_new(ctx._g_main_context.get(), is_running),
                    g_main_loop_unref )
{}
//=======================================================================================
void NMainLoop::run()
{
    g_main_loop_run( _g_main_loop.get() );
}
//=======================================================================================
void NMainLoop::quit()
{
    g_main_loop_quit( _g_main_loop.get() );
}
//=======================================================================================
NMainContext NMainLoop::get_context() const
{
    return g_main_loop_get_context( _g_main_loop.get() );
}
//=======================================================================================
uint NMainLoop::_get_timeout( uint ms, GSourceFunc fn, void *data )
{
    return g_timeout_add( ms, fn, data );
}
//=======================================================================================



//=======================================================================================
//          Timer
//=======================================================================================
class NTimer::Pimpl
{
public:
    using Ptr = shared_ptr<Pimpl>;

    Pimpl(NTimer *owner_) : owner(owner_) {}

    bool detached = false;
    uint id;
    NTimer *owner;
};
//=======================================================================================
static unordered_map<uint,NTimer::Pimpl::Ptr> timers;
//=======================================================================================
int NTimer::_on_timeout( void *pimpl_ )
{
    auto pimpl = static_cast<Pimpl*>( pimpl_ );

    if ( !pimpl->detached )
    {
        //pimpl->owner->timeout();
        return TRUE;
    }

    // detach timeout.
    timers.erase( pimpl->id );
    return FALSE;
}
//=======================================================================================
NTimer::NTimer( uint ms )
    : p( new Pimpl(this) )
{
    p->id = NMainLoop::_get_timeout( ms, &NTimer::_on_timeout, p.get() );
    timers.emplace( p->id, p );
}
//=======================================================================================
NTimer::~NTimer()
{
    stop();
}
//=======================================================================================
void NTimer::stop()
{
    p->detached = true;
}
//=======================================================================================
//          Timer
//=======================================================================================
