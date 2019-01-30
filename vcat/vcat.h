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
//      vcat.h
//=======================================================================================
#ifndef VCAT_H
#define VCAT_H

#include "_vcat_iface.h"
#include <memory>

//=======================================================================================
/*      2018-03-20       VCAT
 *  UPD 2018-07-03
 *
 * Класс предназначен для составления сообщений в строку.
 * Имя берет по аналогии с программой cat, делает, в принципе, то же.
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
 * Действуют все /проверенные/ модификаторы потоков. Часть из них перенесена в методы
 * класса (чтобы были под рукой), с частью автор не разобрался, вообще, их как грязи
 * /ниже приведены ссылки на документацию по части модификаторов/.
 *
 * Введено еще два модификатора: vcat::Space & vcat::NoSpace, которые позволяют
 * автоматически вставлять пробелы между агрументами. Дублируются методами [no]space().
 *
 *
 * Если будет непонятно или неудобно, прошу сообщить, помогите сделать описание и
 * код лучше. Если поможете с юнит-тестированием -- цены вам не будет!
 *
 * Вопросы, пожелания, предложения, просьбы добавить к/л модификатор или
 * его эффект -- *WELCOME!*
*/
//=======================================================================================
//  Манипуляторы в интернете:
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
    explicit vcat( Ts&& ... args );

    std::string str()       const;
    operator std::string()  const;

    //-----------------------------------------------------------------------------------
private:
    void _init_default_modifiers();
    std::stringstream _stream;

    friend class _vcat_iface<vcat>;
    template<typename T> void do_cat( T&& val );
};
//=======================================================================================
//          VCAT -- Составитель строк - сообщений методами STL (stringstream)
//=======================================================================================


//=======================================================================================
//          IMPLEMENTATION
//=======================================================================================
template< typename ... Ts >
vcat::vcat( Ts&& ... args )
{
    _init_default_modifiers();
    operator()( std::forward<Ts>(args)... );
}
//=======================================================================================
template<typename T>
void vcat::do_cat( T&& val )
{
    _stream << std::forward<T>(val);
}
//=======================================================================================
// Для того, чтобы vcat можно было выводить без указания .str();
std::ostream& operator << ( std::ostream& s, const vcat& c );
//=======================================================================================
//          IMPLEMENTATION
//=======================================================================================


#endif // VCAT_H
//=======================================================================================
//      /vcat.h
//=======================================================================================
