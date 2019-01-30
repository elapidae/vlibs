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
