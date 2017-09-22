#ifndef VTHREADQUEUEREGISTRATOR_IMPL_H
#define VTHREADQUEUEREGISTRATOR_IMPL_H

#include <thread>



//=======================================================================================
/*
 *       Внутренняя реализация сборщика очередей потоков. Все классы, имеющие отношение к
 * межпоточной синхронизации "допущены к телу", остальным здесь делать особо нечего.
 */
//=======================================================================================





//=======================================================================================
//          THREAD QUEUE REGISTRATOR
//=======================================================================================
//  Класс предназначен для хранения и обслуживания очередей потоков. В каждом потоке
// создается одна очередь, все манипуляции с ними собраны здесь.
class _VSlot_Impl;
class VThreadInterface;
class VApplication;
class VThreadQueue;

class VThreadQueueRegistrator_Impl final
{
    friend class _VSlot_Impl;
    friend class VThreadInterface;
    friend class VApplication;

    VThreadQueueRegistrator_Impl();
    ~VThreadQueueRegistrator_Impl();

    static VThreadQueueRegistrator_Impl& instance();

    VThreadQueue* get_queue_for_thread( const std::thread::id &tid );
    std::thread::id register_queue_for_cur_thread(VThreadQueue *q);
    void unregister_queue(VThreadQueue *q);

    class Pimpl;
    std::unique_ptr<Pimpl> p;
    //Pimpl *p;
};
//=======================================================================================
//          THREAD QUEUE REGISTRATOR
//=======================================================================================


#endif // VTHREADQUEUEREGISTRATOR_IMPL_H
