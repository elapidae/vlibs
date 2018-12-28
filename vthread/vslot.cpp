#include "vslot.h"

#include <assert.h>
#include "impl/vthreadqueueregistrator_impl.h"


//=======================================================================================
_VSlot_Impl::_VSlot_Impl()
    : _my_thread_id( std::this_thread::get_id() )
{
    _my_queue = VThreadQueueRegistrator_Impl::instance()
                                                .get_queue_for_thread( _my_thread_id );
    assert(_my_queue);
}
//=======================================================================================
VThreadQueue *_VSlot_Impl::_get_my_queue()
{
    return _my_queue;
}
//=======================================================================================
