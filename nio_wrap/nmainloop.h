#ifndef NMAINLOOP_H
#define NMAINLOOP_H

#include <glib.h>
#include <memory>

#include "vsignal.h"





//=======================================================================================
class NSource final
{
public:
    NSource( GSource *s );

    void set_callback( GSourceFunc func, void *data, GDestroyNotify notify = nullptr );

private:
    friend class  NMainContext;
    std::shared_ptr<GSource> _g_source;
};
//=======================================================================================


//=======================================================================================
class NMainContext final
{
public:
    static NMainContext default_ctx();

    NMainContext();

    uint attach( const NSource &source );

    //GMainContext *RAW() { return _g_main_context.get(); }

private:
    friend class NMainLoop;
    NMainContext( GMainContext *ctx );
    std::shared_ptr<GMainContext> _g_main_context;
};
//=======================================================================================


//=======================================================================================
class NMainLoop final
{
public:
    explicit NMainLoop();
    explicit NMainLoop( const NMainContext &ctx, bool is_running = false );

    void run();
    void quit();

    NMainContext get_context() const;

private:
    std::shared_ptr<GMainLoop> _g_main_loop;

    friend class NTimer;
    static uint _get_timeout(uint ms, GSourceFunc fn, void *data );
};
//=======================================================================================


//=======================================================================================
class NTimer final
{
public:

    explicit NTimer( uint ms );
    ~NTimer();

    VSignal<> timeout;

    void stop();

    class Pimpl;
private:
    std::shared_ptr<Pimpl> p;
    static int _on_timeout(void*pimpl_);
};
//=======================================================================================



#endif // NMAINLOOP_H
