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
    assert( flags.take_IN()  );
    assert( flags.raw() == 0 );

    auto ok = semaphore.dec();
    assert( ok );

    auto func = queue.dequeue();

    if ( !func )
        *stop_flag = true;
    else
        func();
}
//=======================================================================================
