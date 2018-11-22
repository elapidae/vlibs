#include "vpoll_queue.h"


//#include "vlog_pretty.h"
#include "verror.h"
//#include "vposix_epoll.h"
//#include "vthread.h"
//#include <thread>

#include <assert.h>
#include "vposix_eventfd.h"
#include <vstd_atomic_queue.h>
#include "vpoll_fds.h"

template<class T> class TD;

//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
class VPoll_Queue::Pimpl : public VEventReceiver
{
public:
    // From semaphore
    void event_received( VPoll_FDs::EventFlags flags ) override;

    vposix::Semaphore semaphore;
    vstd::atomic_queue<InvokeFunc> invoks;

    Pimpl();

    ~Pimpl() override;
};
#pragma GCC diagnostic pop
//=======================================================================================
void VPoll_Queue::Pimpl::event_received( VPoll_FDs::EventFlags flags )
{
    assert( flags.IN() );

    while( semaphore.dec() )
    {
        auto func = invoks.dequeue();
        if (func)
        {
            func();
        }
        else
        {
            break;
            // Need to stop procedure.
            //VPoll_Impl::about_to_stop();
        }
    }
}
//=======================================================================================
VPoll_Queue::Pimpl::Pimpl()
{
    VPoll_FDs::add_fd( semaphore.fd(), this );
}
//=======================================================================================
VPoll_Queue::Pimpl::~Pimpl()
{
    VPoll_FDs::del_fd( semaphore.fd() );
}
//=======================================================================================


//=======================================================================================
VPoll_Queue::VPoll_Queue( const pimpl_shared& _p )
    : p( _p )
{}
//=======================================================================================
vstd::atomic_map<std::thread::id, VPoll_Queue::pimpl_shared> VPoll_Queue::_shares;
//=======================================================================================
void VPoll_Queue::add_queue()
{
    auto th_id = std::this_thread::get_id();
    assert( !_shares.contains(th_id) );
    _shares.emplace( th_id, std::make_shared<Pimpl>() );
}
//=======================================================================================
VPoll_Queue VPoll_Queue::get_queue()
{
    auto th_id = std::this_thread::get_id();
    return _shares.at( th_id );
}
//=======================================================================================
void VPoll_Queue::del_queue()
{
    auto th_id = std::this_thread::get_id();
    auto ok = _shares.erase( th_id );
    assert( ok );
}
//=======================================================================================
VPoll_Queue VPoll_Queue::init_fds_and_get_queue()
{
    VPoll_FDs::add_poll();
    add_queue();
    return get_queue();
}
//=======================================================================================
size_t VPoll_Queue::invoks_count()
{
    if ( auto ptr = p.lock() )
        return ptr->invoks.size();

    throw verror("Bad poll queue.");
}
//=======================================================================================
void VPoll_Queue::do_invoke( InvokeFunc && func )
{
    if ( auto ptr = p.lock() )
    {
        ptr->invoks.enqueue( std::move(func) );
        ptr->semaphore.inc();
        return;
    }
    throw verror("Bad poll queue.");
}
//=======================================================================================
