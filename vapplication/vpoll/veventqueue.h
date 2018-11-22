#ifndef VEVENTQUEUE_H
#define VEVENTQUEUE_H

#include "vpoll.h"

class VInvokeQueue : public VPoll::EventReceiver
{
public:

    VInvokeQueue()
    {
        // semaphore
    }

    void open_polling()
    {
        //sem.fd
    }


    virtual void event_received( VPoll::EventFlags flags ) = 0;

};



/*
#include <memory>
#include <functional>

#include <vstd_atomic_map.h>
#include <thread>
#include <vpoll/vpoll_queue_iface.h>

//=======================================================================================
class VPoll_Queue final : public VPoll_Queue_Iface
{
public:
    //-----------------------------------------------------------------------------------

    static void add_queue();
    static VPoll_Queue get_queue();
    static void del_queue();

    static VPoll_Queue init_fds_and_get_queue();
    //-----------------------------------------------------------------------------------
    using InvokeFunc = std::function<void()>;

    size_t invoks_count();

    void do_invoke( InvokeFunc&& func ) override;

private:
    //-----------------------------------------------------------------------------------
    class Pimpl;
    using pimpl_shared = std::shared_ptr<Pimpl>;
    using pimpl_weak = std::weak_ptr<Pimpl>;

    static vstd::atomic_map<std::thread::id, pimpl_shared> _shares;

    pimpl_weak p;

    VPoll_Queue( const pimpl_shared &_p );
    //-----------------------------------------------------------------------------------
}; // VPoll
//=======================================================================================
*/


#endif // VEVENTQUEUE_H
