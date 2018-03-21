#ifndef vcat_H
#define vcat_H

#include "vcat_iface.h"
#include <memory>

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
class vcat : public _vcat_iface<vcat>
{
public:
    //-----------------------------------------------------------------------------------

    explicit vcat();

    template< typename ... Ts >
    explicit vcat( const Ts& ... args );


    std::string str() const;
    operator std::string() const;


private:
    std::stringstream _stream;

    friend class _vcat_iface<vcat>;
    template<typename T>
    void do_cat( const T& val );
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
template<typename T>
void vcat::do_cat( const T& val )
{
    _stream << val;
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
