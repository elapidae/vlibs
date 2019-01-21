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


#ifndef VSLOT_H
#define VSLOT_H

#include <thread>
#include "vthreadqueue.h"
#include "vsignal.h"

//=======================================================================================
/*
 *      VSlot -- элемент системы синхронизации потоков. Выполняет задачу захвата
 *      очереди текущего потока и последующий "спуск" в нее всех вызовов, выполненных
 *      в других потоках.
 *
 *      class SlotExample
 *      {
 *      private:
 *          VSlot<int> int_slot;
 *
 *          void on_foo(bool);
 *          VSlot<bool> foo;
 *
 *      public:
 *          VSignal<int> int_signal;
 *
 *          SlotExample()
 *              : int_slot( &int_signal )    // сигнал будет эмитирован в текущем потоке.
 *              , foo( this, &SlotExample::on_foo ) // метод вызывается в текущем потоке.
 *          {}
 *
 *          void in_other_thread()  // Пусть выполняется в другом потоке.
 *          {
 *              int_slot( 42 );     // int_signal(42) будет эмитирован в родном потоке.
 *              foo( true );        // on_foo(true) будет вызвана в родном потоке.
 *          }
 *      };
*/
//=======================================================================================




//=======================================================================================
//  Класс-имплементатор предназначен для получения доступа к очереди текущего потока.
//=======================================================================================
class _VSlot_Impl
{
protected:
    _VSlot_Impl();
    const std::thread::id _my_thread_id;
    VThreadQueue* _get_my_queue();

private:
    VThreadQueue *_my_queue;
};
//=======================================================================================
//  Класс-имплементатор предназначен для получения доступа к очереди текущего потока.
//=======================================================================================



//=======================================================================================
//      VSlot
//=======================================================================================
template< typename ... Args >
class VSlot : private _VSlot_Impl
{
public:
    VSlot( VSignal<Args...>* signal );

    template< typename Fn >
    VSlot( Fn fn );

    template< typename Cls, typename Fn >
    VSlot( Cls *cls, Fn fn );

    void call( const Args& ... args );
    void operator()( const Args& ... args );

private:
    using F = std::function<void(Args...)>;
    F _func;
    bool _on = true;
};
//=======================================================================================
//      VSlot
//=======================================================================================



//=======================================================================================
//      IMPLEMENTATION VSlot
//=======================================================================================
template< typename ... Args >
template< typename Fn >
VSlot<Args...>::VSlot( Fn fn )
    : _func( fn )
{}
//=======================================================================================
template< typename ... Args >
template< typename Cls, typename Fn >
VSlot<Args...>::VSlot( Cls *cls, Fn fn )
{
    _func = [cls,fn](Args... args){ (cls->*fn)(args...); };
}
//=======================================================================================
template< typename ... Args >
VSlot<Args...>::VSlot( VSignal<Args...>* signal )
    : VSlot( signal, &VSignal<Args...>::call )
{}
//=======================================================================================
template< typename ... Args >
void VSlot<Args...>::call( const Args& ... args )
{
    if ( !_on ) return;

    auto cur_tid = std::this_thread::get_id();

    if ( cur_tid == _my_thread_id )
        _func( args ... );
    else
        _get_my_queue()->fpush( _func, args... );
}
//=======================================================================================
template< typename ... Args >
void VSlot<Args...>::operator()( const Args& ... args )
{
    call( args... );
}
//=======================================================================================
//      IMPLEMENTATION VSlot
//=======================================================================================


#endif // VSLOT_H
