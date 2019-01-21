/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


#include "vthread.h"

//#include <exception>
//#include <vlogger.h>

#include <future>
#include <assert.h>

#include "vsemaphorequeue.h"
#include "impl/vthreadqueueregistrator_impl.h"

//#include "vlogger.h"

// TODO: Обновить компилятор, он не умеет работать с исключениями между потоками.

using namespace std;
using namespace chrono;



//=======================================================================================
//      VTHREAD INTERFACE
//=======================================================================================
class VThreadInterface::Pimpl
{
public:
    //-------------------------------------------------------------------------------
    Pimpl()
        : let_break      ( false )       // Их нельзя инициировать прямо в классе,
        , has_exception  ( false )       // к сожалению.
        , has_stopped    ( false )
    {}
    //-------------------------------------------------------------------------------
    VThreadQueue     queue;

    atomic_bool let_break;
    atomic_bool has_exception;
    atomic_bool has_stopped;

    string label;
    // TODO: раскомментировать / выкинуть поддержку pthread.
    //exception_ptr except_ptr = nullptr;
    //-------------------------------------------------------------------------------
};
//=======================================================================================
VThreadInterface::VThreadInterface( const string &label )
    : p( new Pimpl )
{    
    _queue = &p->queue;  // необходимо, чтобы методы-шаблоны имели доступ к очереди.
    p->label = label;
}
//=======================================================================================
VThreadInterface::~VThreadInterface()
{
    //vdeb(vlog("~VThreadInterface()", p->label));

    // registered in _run().
    //VThreadQueueRegistrator_Impl::instance().unregister_queue( _queue );
    _queue = nullptr;
}
//=======================================================================================
void VThreadInterface::stop()
{
    if ( p->has_stopped )
        return;

    p->queue.fpush( nullptr );
    _thread_get();

    p->has_stopped = true;

    // TODO: раскомментировать / выкинуть поддержку pthread.
//    if ( p->except_ptr )
//        rethrow_exception( p->except_ptr );
}
//=======================================================================================
void VThreadInterface::break_now()
{
    p->let_break = true;
    stop();
}
//=======================================================================================
bool VThreadInterface::has_exception() const
{
    return p->has_exception;
}
//=======================================================================================
bool VThreadInterface::has_stopped() const
{
    return p->has_stopped;
}
//=======================================================================================
int VThreadInterface::queue_size() const
{
    return _queue->size();
}
//=======================================================================================
void *VThreadInterface::_run(void *self_)
{
    // Чёрти что ради pthread реализации...
    auto self = static_cast<VThreadInterface*>( self_ );

//    VThreadQueueRegistrator_Impl::instance()
//            .register_queue_for_cur_thread( &self->p->queue );

    //vtrace( vlog("Thread queue registered.") );

    while ( self->p &&
            !self->p->has_exception &&
            !self->p->let_break )
    {
        assert( self->_queue );

//        try
//        {
            auto func = self->_queue->pop();

            if ( !func ||
                 self->p->let_break ||
                 self->p->has_exception )
            {
                break;
            }
            func();
//        }
//        catch(...)
//        {
//            self->p->has_exception = true;
//            self->p->has_stopped   = true;

//            throw;
//            // А вот вместо "throw;" ;).
//            // TODO: раскомментировать / выкинуть поддержку pthread.
//            //self->p->except_ptr = current_exception();
//            break;
//        }
    }

    return nullptr;
}
//=======================================================================================
//      VTHREAD INTERFACE
//=======================================================================================



#ifndef VTHREAD_USE_PTHREAD
//=======================================================================================
//      VTHREAD 11 REALIZATION
//=======================================================================================
class _VThread11::Pimpl
{
public:
    template<typename T>
    Pimpl( T && thread )
        : real_thread( move(thread) )
    {}

    std::future<void*> real_thread;
};
//=======================================================================================
_VThread11::_VThread11( const std::string &label )
    : VThreadInterface( label )
    , p( new Pimpl(std::async(std::launch::async, _run, this)) )
{}
//=======================================================================================
//_VThread11::_VThread11( _VThread11::_Detached, const string &label )
//    : VThreadInterface( label )
//    , p( new Pimpl(std::async(std::launch::async, _run, this)) )
//{}
//=======================================================================================
_VThread11::~_VThread11()
{}
//=======================================================================================
void _VThread11::_thread_get()
{
    p->real_thread.get();
}
//=======================================================================================
//      VTHREAD 11 REALIZATION
//=======================================================================================
#else

//=======================================================================================
//      VTHREAD ON PTHREAD REALIZATION
//=======================================================================================
_VThreadP::_VThreadP( const std::string &label )
    : VThreadInterface( label )
{
    static_assert( is_same<decltype(_pthread_handle), pthread_t>::value,
                   "Type pthread_t was changed, correct type of _pthread_handle" );


    pthread_attr_t threadAttr;
    pthread_attr_init( &threadAttr );
    //pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);

    auto vthis = static_cast<void*>(this);
    int result = pthread_create( &_pthread_handle, &threadAttr, &_run, vthis );

    if ( result != 0 )
    {
        //auto log = vlog( "Cannot run pthread, error:", result );
        //vtrace( log );
        throw runtime_error( "Cannot run pthread." );
    }

    //vtrace( vlog("PThread about to be created, pid:", hex, _pthread_handle) );
}
//=======================================================================================
_VThreadP::~_VThreadP()
{
    stop();
}
//=======================================================================================
void _VThreadP::detach()
{
    pthread_detach( _pthread_handle );
}
//=======================================================================================
void _VThreadP::_thread_get()
{
    pthread_join( _pthread_handle, nullptr );
    //vtrace( vlog("PThread joined, pid:")(hex, _pthread_handle) );
    _pthread_handle = 0;
}
//=======================================================================================
//      VTHREAD ON PTHREAD REALIZATION
//=======================================================================================
#endif // VTHREAD_USE_PTHREAD



//=======================================================================================
TimeAccum::TimeAccum()
    : _elapsed(0)
{}
//=======================================================================================
void TimeAccum::start()
{
    _time = high_resolution_clock::now();
}
//=======================================================================================
void TimeAccum::accumulate()
{
    auto now = high_resolution_clock::now();
    _elapsed += duration_cast<nanoseconds>(now - _time).count();
    _time = now;
}
//=======================================================================================
int64_t TimeAccum::elapsed() const
{
    return _elapsed;
}
//=======================================================================================

