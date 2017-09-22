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
 *          // при эмитировании emitter.some_signal(a,b) будет эмитирован и other_signal.
 *          emitter.some_signal.connect( &other_signal );
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

    void call( const Args& ... args ) const;
    void operator()( const Args& ... args ) const;

private:
    // do not use this connector.
    void connect( VSignal<Args...> repeater );

    VSignal( const VSignal& ) = delete;
    const VSignal& operator = ( const VSignal& ) = delete;

    using Func = std::function< void(Args...) >;
    std::vector<Func> _funcs;
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
    connect( [cls,fn](Args... args){(cls->*fn)(args...);} );
}
//=======================================================================================
template< typename ... Args >
void VSignal<Args...>::call( const Args& ... args ) const
{
    for( const auto& f: _funcs )
    {
        f( args... );
    }
}
//=======================================================================================
template< typename ... Args >
void VSignal<Args...>::operator()( const Args& ... args ) const
{
    call( args... );
}
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================



#endif // VSIGNAL_H
