#include "vthreadqueueregistrator_impl.h"

#include <mutex>
#include <unordered_map>
#include <assert.h>

//#include "vlogger.h"


using namespace std;

//=======================================================================================
class VThreadQueueRegistrator_Impl::Pimpl
{
public:
    std::mutex mutex;
    unordered_map< thread::id, VThreadQueue* > queues;
};
//=======================================================================================
VThreadQueueRegistrator_Impl::VThreadQueueRegistrator_Impl()
    : p( new Pimpl )
{}
//=======================================================================================
VThreadQueueRegistrator_Impl::~VThreadQueueRegistrator_Impl()
{
    //vdeb(vlog("quques dtor, size =", p->queues.size()) );
}
//=======================================================================================
VThreadQueueRegistrator_Impl &VThreadQueueRegistrator_Impl::instance()
{
    static VThreadQueueRegistrator_Impl res;
    return res;
}
//=======================================================================================
VThreadQueue *VThreadQueueRegistrator_Impl::get_queue_for_thread( const thread::id &tid )
{
    unique_lock<mutex> lock( p->mutex );
    return p->queues[tid];
}
//=======================================================================================
std::thread::id
VThreadQueueRegistrator_Impl::register_queue_for_cur_thread( VThreadQueue *q )
{
    auto cur_id = this_thread::get_id();
    unique_lock<mutex> lock( p->mutex );

    // check that current thread was not registered yet.
    //assert( p->queues[cur_id] == nullptr );

    p->queues.emplace( cur_id, q );

    return cur_id;
}
//=======================================================================================
void VThreadQueueRegistrator_Impl::unregister_queue( VThreadQueue *q )
{
    unique_lock<mutex> lock( p->mutex );

    for ( auto it = p->queues.begin(); it != p->queues.end(); ++it )
    {
        if ( (*it).second == q )
        {
            p->queues.erase( it );
            return;
        }
    }
    throw runtime_error("Cannot remove thread queue: not found.");
}
//=======================================================================================
