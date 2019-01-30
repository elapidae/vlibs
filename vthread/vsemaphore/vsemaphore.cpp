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


#include "vsemaphore.h"

#include <mutex>
#include <condition_variable>
#include <atomic>

using namespace std;


//=======================================================================================
class VSemaphore::Pimpl
{
public:
    std::mutex          mutex;
    condition_variable  cv;
    atomic_int          count;
};
//=======================================================================================
VSemaphore::VSemaphore( int count )
    : p( make_shared<Pimpl>() )
{
    if ( count < 0 )
        count = 0;

    p->count = count;
}
//=======================================================================================
void VSemaphore::notify()
{
    unique_lock<std::mutex> lock( p->mutex );
    ++p->count;
    p->cv.notify_one();
}
//=======================================================================================
//  Цикл необходим из-за срывов ожидания (см. Мейерса, Современный С++ (11 стандарт)).
void VSemaphore::wait()
{
    unique_lock<std::mutex> lock( p->mutex );
    while( p->count == 0 )
    {
        p->cv.wait( lock );
    }
    --p->count;
}
//=======================================================================================
int VSemaphore::count() const
{
    return p->count;
}
//=======================================================================================
