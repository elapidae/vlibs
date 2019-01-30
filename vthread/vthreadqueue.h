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


#ifndef VTHREADQUEUE_H
#define VTHREADQUEUE_H

#include <functional>
#include "vsemaphorequeue.h"
#include <memory>
#include <thread>

//=======================================================================================
/*      VThreadQueue -- очередь задач потока.
 *
 *      Используется потоками (VThread), главным приложением (VApplication), а также
 *      слотами (VSlot).
 *
 *      Вряд ли вам понадобится использовать ее напрямую.
 *
 *
 *      методы:
 *      int  size()  const;
 *      bool empty() const;
 *
 *      Func pop(); -- встает на мьютекс до тех пор, пока не появится новая задача.
 *
 *      void fpush( AnyFunc, Args... )  // проталкивает новую задачу в очередь,
 *                                      // захватывая аргументы по значению.
 *
 *      void cpush( AnyClass *,         // Указатель на объект. NB! захватывается сырой.
 *                  ClassMethodPtr,     // Указатель на метод класса.
 *                  Args... )           // Аргументы метода.
 *
 *      До трех аргументов включительно захватываются за один раз, далее происходит
 *      рекурсивный захват.
*/
//=======================================================================================



//=======================================================================================
class VThreadQueue
{
public:

    using Func  = std::function< void() >;

    int  size()  const;
    bool empty() const;

    Func pop();


    template< typename Fn >
    void fpush( Fn fn );

    template< typename Fn, typename A1 >
    void fpush( Fn fn, const A1& a1 );

    template< typename Fn, typename A1, typename A2 >
    void fpush( Fn fn, const A1& a1, const A2& a2 );

    template< typename Fn, typename A1, typename A2, typename A3 >
    void fpush( Fn fn, const A1& a1, const A2& a2, const A3& a3 );

    template< typename Fn, typename A1, typename A2, typename A3, typename ... Args >
    void fpush( Fn fn, const A1& a1, const A2& a2, const A3& a3, const Args& ... args );


    template< typename Cls, typename Method >
    void cpush( Cls *cls, Method m );

    template< typename Cls, typename Method, typename A1 >
    void cpush( Cls *cls, Method m, const A1& a1 );

    template< typename Cls, typename Method, typename A1, typename A2 >
    void cpush( Cls *cls, Method m, const A1& a1, const A2& a2 );

    template< typename Cls, typename Method, typename A1, typename A2, typename A3 >
    void cpush( Cls *cls, Method m, const A1& a1, const A2& a2, const A3& a3 );

    template< typename Cls, typename Method,
              typename A1, typename A2, typename A3, typename ... Args >
    void cpush( Cls *cls, Method m,
                const A1& a1, const A2& a2, const A3& a3, const Args& ... args );

private:
    VSemaphoreQueue<Func> _queue;
};  // VThreadQueue
//=======================================================================================




//=======================================================================================
//          IMPLEMENTATION
//=======================================================================================
template< typename Fn >
void VThreadQueue::fpush( Fn fn )
{
    _queue.push( fn );
}
//=======================================================================================
template< typename Fn, typename A1 >
void VThreadQueue::fpush( Fn fn, const A1& a1 )
{
    _queue.push( [=](){ fn(a1); } );
}
//=======================================================================================
template< typename Fn, typename A1, typename A2 >
void VThreadQueue::fpush( Fn fn, const A1& a1, const A2& a2 )
{
    _queue.push( [=](){ fn(a1,a2); } );
}
//=======================================================================================
template< typename Fn, typename A1, typename A2, typename A3 >
void VThreadQueue::fpush( Fn fn, const A1& a1, const A2& a2, const A3& a3 )
{
    _queue.push( [=](){ fn(a1,a2,a3); } );
}
//=======================================================================================
template< typename Fn, typename A1, typename A2, typename A3, typename ... Args >
void VThreadQueue::fpush( Fn fn, const A1& a1, const A2& a2, const A3& a3,
                          const Args& ... args )
{
    auto l = [=](const Args& ... args){ fn(a1,a2,a3,args...); };
    fpush(l, args...);
}
//=======================================================================================

//=======================================================================================
template< typename Cls, typename Method >
void VThreadQueue::cpush( Cls *cls, Method m )
{
    _queue.push( [=](){ (cls->*m)(); } );
}
//=======================================================================================
template< typename Cls, typename Method, typename A1 >
void VThreadQueue::cpush( Cls *cls, Method m, const A1& a1 )
{
    _queue.push( [=](){ (cls->*m)(a1); } );
}
//=======================================================================================
template< typename Cls, typename Method, typename A1, typename A2 >
void VThreadQueue::cpush( Cls *cls, Method m, const A1& a1, const A2& a2 )
{
    _queue.push( [=](){ (cls->*m)(a1,a2); } );
}
//=======================================================================================
template< typename Cls, typename Method, typename A1, typename A2, typename A3 >
void VThreadQueue::cpush( Cls *cls, Method m, const A1& a1, const A2& a2, const A3& a3 )
{
    _queue.push( [=](){ (cls->*m)(a1,a2,a3); } );
}
//=======================================================================================
template< typename Cls, typename Method,
          typename A1, typename A2, typename A3, typename ... Args >
void VThreadQueue::cpush( Cls *cls, Method m,
            const A1& a1, const A2& a2, const A3& a3, const Args& ... args )
{
    auto l = [=](Args ... args){ (cls->*m)(a1,a2,a3,args...); };
    fpush( l, args... );
}
//=======================================================================================
//          IMPLEMENTATION
//=======================================================================================



#endif // VTHREADQUEUE_H
