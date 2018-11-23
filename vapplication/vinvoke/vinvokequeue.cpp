#include "vinvokequeue.h"

#include <assert.h>


//=======================================================================================
void VInvokeQueue::open_polling( bool *stop_dst )
{
    assert( stop_dst    );

    stop_flag = stop_dst;
    VPoll::add_fd( semaphore.fd(), this );
}
//=======================================================================================
void VInvokeQueue::close_polling()
{
    VPoll::del_fd( semaphore.fd() );
}
//=======================================================================================
void VInvokeQueue::enqueue( InvokeFunc && func )
{
    queue.enqueue( std::move(func) );
    semaphore.inc();
}
//=======================================================================================
void VInvokeQueue::event_received( VPoll::EventFlags flags )
{
    assert( flags.IN() );

    auto ok = semaphore.dec();
    assert( ok );

    auto func = queue.dequeue();

    if ( !func )
        *stop_flag = true;
    else
        func();
}
//=======================================================================================
