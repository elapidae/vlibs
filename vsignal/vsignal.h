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


#ifndef VSIGNAL_H
#define VSIGNAL_H


#include <functional>
#include <vector>


//=======================================================================================
/*
 *      VSignal -- некоторый аналог сигналов в Qt. Используется для обеспечения
 *      модульности программ.
 *
 *      Принцип использования:
 *      - Объявляем сигнал с сигнатурой вызова в классе:
 *          class AnyEmitter
 *          {
 *          public:
 *              VSignal<int, std::string> some_signal;
 *
 *              void emit_signal()
 *              {
 *                  some_signal( 42, "Hello world!" );
 *              }
 *          };
 *
 *      - Из внешнего кода соединяемся с сигналом:
 *          class Receiver
 *          {
 *          public:
 *              void on_some_signal( int a, const std::string &b );
 *          };
 *          AnyEmitter emitter;
 *          Receiver receiver;
 *          emitter.some_signal.connect( &receiver, &Receiver::on_some_signal );
 *
 *      - Вызываем приемник:
 *          emitter.emit_signal();
 *
 *      - Можно подключать лямбды и функции:
 *          emitter.some_signal.connect( [](int a, std::string b) {
 *              std::cout << "a = " << a << ", b = " << b << std::endl;
 *          });
 *          void some_func(int a, const std::string &b) {}
 *          emitter.some_signal.connect( &some_func );
 *      - Можно "пробрасывать" сигналы:
 *          VSignal<int, std::string> other_signal;
 *          emitter.some_signal.connect( &other_signal );
 *          // при эмитировании emitter.some_signal(a,b) будет эмитирован и other_signal.
*/
//=======================================================================================



//=======================================================================================
//      VSignal
//=======================================================================================
template< typename ... Args >
class VSignal
{
public:
    VSignal();

    void connect( VSignal<Args...> *repeater );

    template< typename Fn >
    void connect( Fn fn );

    template< typename Cls, typename Fn >
    void connect( Cls *cls, Fn fn );

    void call( const Args& ... args );
    void operator()( const Args& ... args );

    //  Введен для возможности эмитить сигналы из константных методов.
    //  Использование этого способа на плечах программиста, лучше использовать
    //  неконстантный способ эмитирования сигнала.
    void const_call( const Args& ... args ) const;

    void disconnect_all();

    int connections_count() const;

private:
    // do not use this connector.
    void connect( VSignal<Args...> repeater );

    using Func = std::function< void(const Args&...) >;
    std::vector<Func> _funcs;

    VSignal( const VSignal& ) = delete;
    const VSignal& operator = ( const VSignal& ) = delete;
};
//=======================================================================================
//      VSignal
//=======================================================================================



//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
template< typename ... Args >
VSignal<Args...>::VSignal()
{}
//=======================================================================================
//=======================================================================================
template< typename ... Args >
void VSignal<Args...>::connect( VSignal<Args...> *repeater )
{
    connect( repeater, &VSignal<Args...>::call );
}
//=======================================================================================
template< typename ... Args >
template< typename Fn >
void VSignal<Args...>::connect( Fn fn )
{
    _funcs.push_back( fn );
    _funcs.shrink_to_fit();
}
//=======================================================================================
template< typename ... Args >
template< typename Cls, typename Fn >
void VSignal<Args...>::connect( Cls *cls, Fn fn )
{
    connect( [cls,fn](const Args& ... args){ (cls->*fn)(args...); } );
}
//=======================================================================================
//=======================================================================================
template< typename ... Args >
void VSignal<Args...>::call( const Args& ... args )
{
    for( const auto& f: _funcs )
    {
        f( args... );
    }
}
//=======================================================================================
template< typename ... Args >
void VSignal<Args...>::const_call( const Args& ... args ) const
{
    for( const auto& f: _funcs )
    {
        f( args... );
    }
}
//=======================================================================================
template< typename ... Args >
void VSignal<Args...>::operator()( const Args& ... args )
{
    call( args... );
}
//=======================================================================================
//=======================================================================================
template< typename ... Args >
void VSignal<Args...>::disconnect_all()
{
    _funcs.clear();
}
//=======================================================================================
template< typename ... Args >
int VSignal<Args...>::connections_count() const
{
    return _funcs.size();
}
//=======================================================================================
//     /IMPLEMENTATION
//=======================================================================================


#endif // VSIGNAL_H
