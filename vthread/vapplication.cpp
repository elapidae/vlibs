#include "vapplication.h"

#include <thread>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>

#include <signal.h>
#include <algorithm>

#include "vthreadqueue/vthreadqueue.h"
#include "vthread.h"
#include "impl/vthreadqueueregistrator_impl.h"

//#include "vlogger.h"


using namespace std;



//=======================================================================================
static void sigterm( int )
{
    VApplication::app()->quit( 0 );
}
//=======================================================================================


//=======================================================================================
class VApplication::Pimpl
{
public:
    string program_name;
    vector<string> args;

    VThreadQueue app_queue;

    thread::id my_thread_id;

    int retcode = 0;
};
//=======================================================================================
static VApplication *app_instance = nullptr;
VApplication *VApplication::app()
{
    if (!app_instance)
        throw std::runtime_error("VApplication not instanced.");

    return app_instance;
}
//=======================================================================================
VApplication::VApplication()
    : p( new Pimpl )
{
    // Этот мьютекс встроен, чтобы не отстрелить себе ногу. Объект класса VApplication
    // должен быть создан в одном экземпляре в начале программы. Он, как минимум,
    // заворачивает главный поток в очередь синхронизации.
    static mutex once_guard;
    if ( !once_guard.try_lock() )
        throw std::runtime_error( "Try to run two VApplication instances." );

    app_instance = this;

//    signal( SIGKILL, sigterm );
    signal( SIGTERM, sigterm );
    signal( SIGHUP,  sigterm );
    signal( SIGINT,  sigterm );

    p->my_thread_id = VThreadQueueRegistrator_Impl::instance()
                                        .register_queue_for_cur_thread( &p->app_queue );
}
//=======================================================================================
VApplication::VApplication( int argc, char **argv )
    : VApplication()
{
    p->program_name = argv[0];

    for ( int i = 1; i < argc; ++i )
        p->args.push_back( argv[i] );

    p->args.shrink_to_fit();
}
//=======================================================================================
VApplication::~VApplication()
{
    app_instance = nullptr;
    VThreadQueueRegistrator_Impl::instance().unregister_queue( &p->app_queue );
}
//=======================================================================================
int VApplication::exec()
{
    while (1)
    {
        auto fn = p->app_queue.pop();
        if ( !fn )
        {
            //vdeb(vlog("break"));
            break;
        }
        fn();
    }
    //VThreadQueueRegistrator_Impl::instance().unregister_queue( &p->app_queue );
    return p->retcode;
}
//=======================================================================================
void VApplication::quit( int retcode )
{
    p->retcode = retcode;
    p->app_queue.fpush( nullptr );
}
//=======================================================================================
thread::id VApplication::app_thread_id() const
{
    return p->my_thread_id;
}
//=======================================================================================
int VApplication::queue_size() const
{
    return p->app_queue.size();
}
//=======================================================================================
string VApplication::series_param( const string &param_name ) const
{
    Pimpl* pp = p.get();
    int args_size = pp->args.size();
    for ( int i = 0; i < args_size; ++i )
    {
        if ( pp->args[i] == param_name &&
             i + 1 < args_size )
        {
            return pp->args[i + 1];
        }
    }
    return {};
}
//=======================================================================================
bool VApplication::has_param( const string &pname ) const
{
    Pimpl *pp = p.get();
    auto it = find( pp->args.begin(), pp->args.end(), pname );
    return it != pp->args.end();
}
//=======================================================================================
