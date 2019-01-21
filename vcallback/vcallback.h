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


#ifndef VCallBack_H
#define VCallBack_H


#include <functional>
#include <vector>
#include <stdexcept>

//=======================================================================================
/*
 *      VCallBack -- враппер для std::function.
 *
 *      Принцип тот же, но есть отличия:
 *      + объект класса не копируется, следовательно, класс с таким объектом тоже.
 *      + не позволит присоединить новый приемник, пока не снят старый.
 *      + безопасно вызывать без приемника, std::function даст исключение.
 *      + есть синтаксис соединения с методами объектов: cb.link(objptr, &Object::foo);
 *      + [пока не реализовано] будет использоваться для межпоточного взаимодействия.
 *
 *
 *      Принцип использования:
 *      - Объявляем сигнал с сигнатурой вызова в классе:
 *          class AnyEmitter
 *          {
 *          public:
 *              VCallBack<int, std::string> some_cb;
 *
 *              void emit_cb()
 *              {
 *                  some_cb( 42, "Hello world!" );
 *              }
 *          };
 *
 *      - Из внешнего кода соединяемся:
 *          class Receiver
 *          {
 *          public:
 *              void on_some_cb( int a, const std::string &b );
 *          };
 *          AnyEmitter emitter;
 *          Receiver receiver;
 *          emitter.some_cb.link( &receiver, &Receiver::on_some_cb );
 *
 *      - Вызываем приемник:
 *          emitter.emit_cb();
 *
 *      - Можно подключать лямбды и функции:
 *          emitter.some_cb = [](int a, std::string b) {
 *              std::cout << "a = " << a << ", b = " << b << std::endl;
 *          };
 *          emitter.some_cb.link( [](int a, std::string b) {
 *              std::cout << "a = " << a << ", b = " << b << std::endl;
 *          });
 *          void some_func(int a, const std::string &b) {}
 *          emitter.some_cb.link( &some_func );
*/
//=======================================================================================



//=======================================================================================
//      VCallBack
//=======================================================================================
template< typename ... Args >
class VCallBack
{
public:
    VCallBack();

    template< typename Fn >
    void link( Fn fn );

    template< typename Cls, typename Fn >
    void link( Cls *cls, Fn fn );

    template< typename Fn >
    void operator = ( Fn fn );


    void call( Args ... args );
    void operator()( Args ... args );

    void unlink();

private:
    using _func = std::function< void(Args...) >;
    _func _f;

    VCallBack( const VCallBack& ) = delete;
    const VCallBack& operator = ( const VCallBack& ) = delete;
};
//=======================================================================================
//      VCallBack
//=======================================================================================



//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
template< typename ... Args >
VCallBack<Args...>::VCallBack()
{}
//=======================================================================================
template< typename ... Args >
template< typename Fn >
void VCallBack<Args...>::link( Fn fn )
{
    if ( _f ) throw std::runtime_error("VCallBack already linked.");
    _f = std::forward<Fn>(fn);
}
//=======================================================================================
template< typename ... Args >
template< typename Cls, typename Fn >
void VCallBack<Args...>::link( Cls *cls, Fn fn )
{
    link( [cls,fn](Args ... args){ (cls->*fn)(std::forward<Args>(args)...); } );
}
//=======================================================================================
template< typename ... Args >
template< typename Fn >
void VCallBack<Args...>::operator=( Fn fn )
{
    link( std::forward<Fn>(fn) );
}
//=======================================================================================
//=======================================================================================
template< typename ... Args >
void VCallBack<Args...>::call( Args ... args )
{
    if ( _f ) _f( std::forward<Args>(args)... );
}
//=======================================================================================
template< typename ... Args >
void VCallBack<Args...>::operator()( Args ... args )
{
    call( std::forward<Args>(args)... );
}
//=======================================================================================
//=======================================================================================
template< typename ... Args >
void VCallBack<Args...>::unlink()
{
    _f = nullptr;
}
//=======================================================================================
//     /IMPLEMENTATION
//=======================================================================================


#endif // VCallBack_H
