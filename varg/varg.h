#ifndef VARG_H
#define VARG_H

#include <sstream>
#include <memory>

//=======================================================================================
/*      varg -- Вспомогательный класс, предназначенный для составления строк сообщений.
 *
 *      Использует std::stringstream, но перегружает не operator<<(), а opeartor()(),
 *      таким образом избавляет пользователя от нелогичных приоритетов.
 *
 *      NB! При копировании все копии будут работать с одним и тем же реальным объектом.
 *
 *      Модификаторы потоков действуют также, как в Стандарте.
 *      NB! По умолчанию выставляются модификаторы:
 *          std::boolalpha (вывод булевых значений как true/false, вместо 1/0);
 *          std::showbase (вывод 0x при шестнадцатеричном выводе, 0 при восьмеричном );
 *
 *      Добавлены свои модификаторы (их нет в Стандарте):
 *      varg::space, varg::nospace -- ставить пробелы после элементов
 *                                    (и не ставит после применения модификаторов).
 *
 *      varg::long_fp, varg::std_fp -- печатать типы float и double
 *                                     с максимальной точностью.
 *
 *      Примеры использования:
 *      const char *hello = "Hello";
 *      std::string world = "world!";
 *      long lval = 42;
 *      std::string hw = varg(hello, " ", world, " ", lval);
 *      // hw == "Hello world! 42"
 *
 *      // Применение пробелов между элементами:
 *      varg(varg::space, hello, world, lval).println();
 *      // В консоль выводится "Hello world! 42\n"
 *
 *      // Можно группировать по смыслу вот так:
 *      auto arg = varg("First element", " of string | ")
 *                     (varg::space)
 *                     (std::hex, "Second element", 42, '|')    // 42 будет как 0x2a
 *                     (std::oct, "Third element", 42);         // 42 будет как 052
 *      arg.println();
 *      // В консоли: First element of string | Second element 0x2a | Third element 052
 *
 *      // Модификатор вывода чисел с плавающей запятой.
 *      varg(varg::space, .3, varg::long_fp, .3).println();
 *      // Вывод: 0.3 0.29999999999999999
 */
//=======================================================================================




//=======================================================================================
//          VARG -- Составитель строк-сообщений методами STL ostream
//=======================================================================================
class varg
{
public:
    varg();

    template< typename ... Args >
    explicit varg( const Args& ... args );

    template< typename T >
    varg& operator()( const T& val );

    template< typename T, typename ... Args >
    varg& operator()( const T& val, const Args& ... args );

    varg& operator()( const float  &f );
    varg& operator()( const double &d );

    varg& operator()( const decltype(std::hex)& modifier );

    std::string str() const;
    operator std::string() const;

    void println() const;               // Вывод в cout с переводом строки.

    enum  _space    { space    };
    enum  _nospace  { nospace  };
    varg& operator()( _space   );
    varg& operator()( _nospace );

    enum  _long_fp  { long_fp  };
    enum  _std_fp   { std_fp   };
    varg& operator()( _long_fp );
    varg& operator()( _std_fp  );

    varg& width(int w);                 // Модификаторы выравнивания, см. Стандарт
    varg& right();                      // Совет от автора: много эспериментируйте
    varg& left();                       // перед использованием в продашн-коде.

    //-------------------------------------------------------------------------------
private:
    class Pimpl;
    std::shared_ptr<Pimpl> p;

    std::stringstream& _stream();
    void _apply_spaces();
};
//=======================================================================================
//          VARG -- Составитель строк - сообщений методами STL ostream
//=======================================================================================


//=======================================================================================
//          IMPLEMENTATION
//=======================================================================================
template< typename ... Args >
varg::varg( const Args& ... args )
    : varg()
{
    operator()( args... );
}
//=======================================================================================
template< typename T >
varg& varg::operator()( const T& val )
{
    _stream() << val;
    _apply_spaces();
    return *this;
}
//=======================================================================================
template< typename T, typename ... Tail >
varg& varg::operator()( const T& val, const Tail& ... args )
{
    operator()( val );
    return operator()( args... );
}
//=======================================================================================
//          IMPLEMENTATION
//=======================================================================================


#endif // VARG_H
