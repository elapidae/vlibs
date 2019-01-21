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


#ifndef VINVOKEQUEUE_H
#define VINVOKEQUEUE_H

#include <functional>
#include "vpoll/vpoll.h"
#include "vstd_atomic_queue.h"
#include "vposix_eventfd.h"


class VInvokeQueue : public VPoll::EventReceiver
{
public:
    using InvokeFunc = std::function<void()>;

    void open_polling( bool *stop_dst );
    void close_polling();

    void enqueue( InvokeFunc &&func );

private:
    void event_received( VPoll::EventFlags flags ) override;
    bool *stop_flag = nullptr;
    vstd::atomic_queue<InvokeFunc> queue;
    vposix::Semaphore semaphore;
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


#endif // VINVOKEQUEUE_H
