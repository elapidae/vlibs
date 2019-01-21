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


#ifndef VCAT_TUPLE_H
#define VCAT_TUPLE_H

#include <ostream>
#include <tuple>

//=======================================================================================
namespace std
{
    //===================================================================================
    ostream& operator << ( ostream& os, const std::tuple<>& );
    //===================================================================================
    template<typename T, typename ... Args>
    ostream& operator << ( ostream& os, const std::tuple<T,Args...> &tup );
    //===================================================================================
    template<typename T1, typename T2>
    ostream& operator << ( ostream& os, const std::pair<T1,T2> &p );
    //===================================================================================


    //===================================================================================
    //      IMPLEMENTATION
    //===================================================================================
    template<size_t pos, size_t endpos>
    void _print (ostream& os, const std::tuple<>& )
    {
        os << ">";
    }
    //===================================================================================
    template<size_t pos, size_t endpos, bool process, typename T, typename ... Args>
    void _print (ostream& os, const std::tuple<T,Args...> &tup )
    {
        if ( !process )
        {
            os << ">";
            return;
        }
        os << get<pos>(tup);
        if ( pos + 1 < endpos  )
            os << "|";

        _print< pos + 1 < endpos ? pos + 1 : pos,
                endpos,
                pos + 1 < endpos >(os,tup);
    }
    //===================================================================================
    ostream& operator << ( ostream& os, const std::tuple<>& )
    {
        os << "tuple<>";
        return os;
    }
    //===================================================================================
    template<typename T, typename ... Args>
    ostream& operator << (ostream& os, const std::tuple<T,Args...> &tup )
    {
        os << "tuple<";
        constexpr size_t sz = tuple_size<decltype(tup)>();
        _print<0,sz,sz != 0>(os, tup);
        return os;
    }
    //===================================================================================
    template<typename T1, typename T2>
    ostream& operator << ( ostream& os, const std::pair<T1,T2> &p )
    {
        os << "pair<" << p.first << "," << p.second << ">";
        return os;
    }
    //===================================================================================
    //      IMPLEMENTATION
    //===================================================================================
} // std namespace
//=======================================================================================



#endif // VCAT_TUPLE_H
