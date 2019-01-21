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


//=======================================================================================
//      _vcat_iface.h
//=======================================================================================
#ifndef VCAT_IFACE_H_
#define VCAT_IFACE_H_

#include <sstream>
#include <iomanip>
#include <limits>

//=======================================================================================
/*  UPD 2018-07-03  by Elapidae
 *
 *  TODO: сделать нормальное описание принципов работы для разработчиков.
 *  Помогите автору с этим,, чтобы выстроить непротиворечивое описание,
 *  необходимо "объяснить соседу" кухню класса.
 *
 *  Используется CRTP паттерн, наследуемый класс должен определяться ~ так:
 *  class Derived : public _vcat_iface<Derived>
 *  {
 *      template<typename T>
 *      void do_cat(T val)
 *      {
 *          // конкатекация с реальным std::ostream;
 *          // сюда могут прилетать, в т.ч., модификаторы.
 *          // Не будут прилетать доп. флаги (типа Space/NoSpace),
 *          // вместо них прилетит пробел. Т.е. здесь будут "дисситилированные" данные.
 *      }
 *  };
 *
 *  В do_cat будут прилетать "очищенные" типы, логика установки флагов и принятия решений
 *  что писать остается в реализациях cat(...). Не используйте cat(...) для проксирования
 *  интерфейса.
 *
 *  Все методы проксируют вызовы на методы cat(...), которые уже принимают решение
 *  что, как и зачем писать. Передают в испольнителя do_cat(T) из кода наследника.
 *
**/
//=======================================================================================




//=======================================================================================
//      VCAT IFACE
//=======================================================================================
template<typename D>
class _vcat_iface
{
    using _std_modifier_type_ = decltype(std::hex);

public:
    //-----------------------------------------------------------------------------------

    template< typename T >
    D& operator()( T&& val );

    template< typename T, typename ... Ts >
    D& operator()( T&& val, Ts&& ... args );

    //-----------------------------------------------------------------------------------

    template< typename T >
    D& operator << ( T&& val );

    template< typename T >
    D& cat ( T&& val );

    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------
    //  Пробная часть -- сбор модификаторов, пробы по их установке.

    D& oct();                    // equal to std::oct
    D& dec();                    // equal to std::dec
    D& hex();                    // equal to std::hex

    D& precision( int p );       // equal to std::setprecision(p);
    D& max_precision();

    D& fill_char( char ch );     // equal to std::setfill(ch)
    D& field_width( int w );     // equal to std::setw(fieldWidth)

    D& space();                  // Пробелы между аргументами, то же cat(vcat::Space).
    D& nospace();                // Отключает вывод пробелов, cat(vcat::NoSpace)

    D& num( long long val, int field_width, char fill = ' ' );
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------
    //      private / not interest section.
    //-----------------------------------------------------------------------------------
    // Перегрузки нужны, чтобы при этих модификаторах был вызван специфичный код.
    enum   _space   { Space    };
    enum   _nospace { NoSpace  };
    D& cat          ( _std_modifier_type_ );
    D& operator()   ( _std_modifier_type_ );
    D& operator<<   ( _std_modifier_type_ );
    D& cat          ( _space   );
    D& operator()   ( _space   );
    D& operator<<   ( _space   );
    D& cat          ( _nospace );
    D& operator()   ( _nospace );
    D& operator<<   ( _nospace );
    //-----------------------------------------------------------------------------------

protected:
    _vcat_iface();

    template< typename ... Ts >
    explicit _vcat_iface( Ts&& ... args );

    ~_vcat_iface() = default;


private:
    bool _with_spaces  = false;
    bool _is_first_arg = true;
};
//=======================================================================================
//      VCAT IFACE
//=======================================================================================





//=======================================================================================
//          IMPLEMENTATION
//=======================================================================================
//=======================================================================================
template< typename D >
_vcat_iface<D>::_vcat_iface()
{}
//=======================================================================================
template< typename D >
template< typename ... Ts >
_vcat_iface<D>::_vcat_iface( Ts&& ... args )
    : _vcat_iface()
{
    operator()( std::forward<Ts>(args)... );
}
//=======================================================================================
template< typename D >
template< typename T >
D& _vcat_iface<D>::cat( T&& val )
{
    D& d = static_cast<D&>( *this );

    if ( !_is_first_arg && _with_spaces )
        d.do_cat(' ');

    d.do_cat( std::forward<T>(val) );
    _is_first_arg = false;

    return d;
}
//=======================================================================================
template< typename D >
template< typename T >
D& _vcat_iface<D>::operator()( T&& val )
{
    return cat( std::forward<T>(val) );
}
//=======================================================================================
template< typename D >
template< typename T, typename ... Ts >
D& _vcat_iface<D>::operator()( T&& val, Ts&& ... args )
{
    cat( std::forward<T>(val) );
    return operator()( std::forward<Ts>(args)... );
}
//=======================================================================================
template< typename D >
template< typename T >
D& _vcat_iface<D>::operator << ( T&& val )
{
    return cat( std::forward<T>(val) );
}
//=======================================================================================
template< typename D >
D& _vcat_iface<D>::cat ( _std_modifier_type_ modifier )
{
    D& d = static_cast<D&>( *this );
    d.do_cat( modifier );
    return d;
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator << ( _std_modifier_type_ modifier )
{
    return cat( modifier );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator()( _std_modifier_type_ modifier )
{
    return cat( modifier );
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::cat( _nospace )
{
    _with_spaces = false;
    return static_cast<D&>( *this );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator << ( _nospace )
{
    return cat( NoSpace );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator()( _nospace )
{
    return cat( NoSpace );
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::cat ( _space )
{
    _with_spaces = true;
    return static_cast<D&>( *this );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator << ( _space )
{
    return cat( Space );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::operator()( _space )
{
    return cat( Space );
}
//=======================================================================================
template< typename D >
D& _vcat_iface<D>::oct()
{
    return cat( std::oct );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::dec()
{
    return cat( std::dec );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::hex()
{
    return cat( std::hex );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::precision( int p )
{
    D& d = static_cast<D&>( *this );
    d.do_cat( std::setprecision(p) );
    return d;
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::max_precision()
{
    return precision( std::numeric_limits<long double>::digits10 + 1 );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::fill_char( char ch )
{
    D& d = static_cast<D&>( *this );
    d.do_cat( std::setfill(ch) );
    return d;
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::field_width( int w )
{
    D& d = static_cast<D&>( *this );
    d.do_cat( std::setw(w) );
    return d;
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::space()
{
    return cat( Space );
}
//---------------------------------------------------------------------------------------
template< typename D >
D& _vcat_iface<D>::nospace()
{
    return cat( NoSpace );
}
//=======================================================================================
//  2018-06-08 -- проба восстановить справедливость к достаточно важной функции: выводу
//  выровненных целых чисел.
template< typename D >
D& _vcat_iface<D>::num( long long val, int f_width, char fill_ch )
{
    return fill_char(fill_ch).field_width(f_width)(val);
}
//=======================================================================================
//          IMPLEMENTATION
//=======================================================================================


#endif // VCAT_IFACE_H_
//=======================================================================================
//      _vcat_iface.h
//=======================================================================================
