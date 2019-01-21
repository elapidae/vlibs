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
