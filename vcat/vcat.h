#ifndef vcat_H
#define vcat_H

#include <sstream>
#include <iomanip>
#include <limits>

//=======================================================================================
/* 20-03-2018       VCAT
 *
 * Класс предназначен для составления сообщений в строку.
 * Имя берет по аналогии с программой cat, делает, в принципе, то же.
 * Раньше назывался varg (по аналогии с методом Qt::QString::arg()), теперь буду
 * переходить на этот.
 *
 * Принцип работы: можете использовать его просто перечисляя нужные поля подряд:
 * vcat("one", 2, "three").str();
 *
 * Можно ставить друг за другом произвольное количество скобок:
 * vcat(vcat::Space)("one", 2, "three");
 *
 * Можно пользовать как стандартный поток:
 * vcat cat;
 * cat << "one" << "two" << std::setw(10) << 3;
 *
 * Действуют все модификаторы потоков. Часть из них перенесена в методы класса
 * (просто чтобы были под рукой), с частью автор не разобрался, вообще, их как грязи
 * /ниже приведены ссылки на документацию по части модификаторов/.
 *
 * Введено еще два модификатора: vcat::Space & vcat::NoSpace, которые позволяют
 * автоматически вставлять пробелы между агрументами. Дублируются методами [no]space().
 *
 *
 * Если будет непонятно или неудобно, прошу сообщить, помогите сделать описание и
 * код лучше. Если поможете с юнит-тестированием -- цены вам не будет!
 *
 * Вопросы, пожелания, предложения, просьба добавить к/л модификатор или
 * его эффект -- *WELCOME!*
*/
//=======================================================================================
//http://en.cppreference.com/w/cpp/io/manip         -- list of manips.
//http://en.cppreference.com/w/cpp/io/manip/setw
//http://en.cppreference.com/w/cpp/io/manip/setfill
//http://en.cppreference.com/w/cpp/io/manip/put_money
//http://en.cppreference.com/w/cpp/io/manip/put_time
//http://en.cppreference.com/w/cpp/io/manip/skipws
//http://en.cppreference.com/w/cpp/io/manip/ws
//http://en.cppreference.com/w/cpp/io/manip/ends
//http://en.cppreference.com/w/cpp/io/manip/showpos
//http://en.cppreference.com/w/cpp/io/manip/boolalpha
//http://en.cppreference.com/w/cpp/io/manip/showbase
//http://en.cppreference.com/w/cpp/io/manip/setprecision
//http://en.cppreference.com/w/cpp/io/manip/showpoint
//=======================================================================================



//=======================================================================================
//          VCAT -- Составитель строк - сообщений методами STL (stringstream)
//=======================================================================================
class vcat
{
    using _std_modifier_t = decltype(std::hex);

public:
    //-----------------------------------------------------------------------------------

    vcat();

    template< typename ... Ts >
    explicit vcat( const Ts& ... args );

    template< typename T >
    vcat& operator()( const T& val );

    template< typename T, typename ... Ts >
    vcat& operator()( const T& val, const Ts& ... args );

    //-----------------------------------------------------------------------------------

    template< typename T >
    vcat& operator << ( const T& val );

    template< typename T >
    vcat& cat ( const T& val );

    // Вывод целочисленного значения специальными способами.
    // Сохраняет модификаторы неизменными (точнее, их восстанавливает :).
    // Синтаксис стараюсь копировать из Qt::QString::arg().
    vcat& cat( long a, int fieldWidth = 0, int base = 10, char fillChar = ' ' );

    //-----------------------------------------------------------------------------------

    std::string str() const;
    operator std::string() const;

    //-----------------------------------------------------------------------------------
    //  Пробная часть -- сбор модификаторов, пробы по их установке.

    vcat& oct();                    // equal to std::oct
    vcat& dec();                    // equal to std::dec
    vcat& hex();                    // equal to std::hex

    vcat& precision( int p );       // equal to std::setprecision(p);
    vcat& max_precision();

    vcat& fill_char( char ch );     // equal to std::setfill(ch)
    vcat& field_width( int w );     // equal to std::setw(fieldWidth)

    vcat& space();                  // Пробелы между аргументами, то же cat(vcat::Space).
    vcat& nospace();                // Отключает вывод пробелов, cat(vcat::NoSpace)

    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------------------
    // Рабочая лошадка класса, вся работа происходит через этот экземпляр.
    // Нет смысла делать его приватным, пользователь может манипулировать потоком,
    // если, конечно, знает что делает /и готов нести ответственность/.
    std::stringstream stream;
    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------------------
    //      private / not interest section.
    //-----------------------------------------------------------------------------------
    // Перегрузки нужны, чтобы при этих модификаторах был вызван специфичный код.
    enum   _space    { Space    };
    enum   _nospace  { NoSpace  };
    vcat& operator() ( _std_modifier_t );
    vcat& operator<< ( _std_modifier_t );
    vcat& operator() ( _space   );
    vcat& operator() ( _nospace );
    vcat& operator<< ( _space   );
    vcat& operator<< ( _nospace );
    //-----------------------------------------------------------------------------------

    //virtual ~vcat() = default;

private:
    bool _with_spaces  = false;
    bool _is_first_arg = true;
};
//=======================================================================================
//          VCAT -- Составитель строк - сообщений методами STL (stringstream)
//=======================================================================================





//=======================================================================================
//          IMPLEMENTATION
//=======================================================================================
template< typename ... Ts >
vcat::vcat( const Ts& ... args )
    : vcat()
{
    operator()( args... );
}
//=======================================================================================
template< typename T >
vcat& vcat::cat( const T& val )
{
    if ( !_is_first_arg && _with_spaces )
        stream << ' ';

    stream << val;
    _is_first_arg = false;
    return *this;
}
//=======================================================================================
template< typename T >
vcat& vcat::operator()( const T& val )
{
    return cat( val );
}
//=======================================================================================
template< typename T, typename ... Ts >
vcat& vcat::operator()( const T& val, const Ts& ... args )
{
    cat( val );
    return operator()( args... );
}
//=======================================================================================
template< typename T >
vcat& vcat::operator << ( const T& val )
{
    return cat( val );
}
//=======================================================================================
// Для того, чтобы vcat можно было выводить без указания .str();
template< typename Stream >
Stream& operator << ( Stream& s, const vcat& c )
{
    s << c.str();
    return s;
}
//=======================================================================================
//          IMPLEMENTATION
//=======================================================================================





#endif // vcat_H
