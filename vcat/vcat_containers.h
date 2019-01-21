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


#ifndef VCAT_CONTAINERS_H
#define VCAT_CONTAINERS_H

#include <iostream>

#include <vector>
#include <deque>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>



namespace std
{
    namespace details
    {
        template<typename T, typename Cont>
        void _write_container( ostream & os, const Cont &c, const char *name )
        {
            os << name << '(';
            for ( auto it = c.begin(); it != c.end(); ++it )
            {
                os << (*it);
                auto next = it; ++next; // Это нужно, т.к. сложение (it + 1) не работает
                                        // на некоторых контейнерах.
                if ( next != c.end() ) os << ',';
            }
            os << ')';
        }
    }


    template<typename T, typename U>
    ostream & operator << ( ostream & os, const std::pair<T,U> & p )
    {
        os << '{' << p.first << '|' << p.second << '}';
        return os;
    }

    template<typename T>
    ostream & operator << ( ostream & os, const std::vector<T>& v )
    {
        details::_write_container<T,std::vector<T>>( os, v, "std::vector" );
        return os;
    }

    template<typename T>
    ostream & operator << ( ostream & os, const std::list<T>& l )
    {
        details::_write_container<T,std::list<T>>( os, l, "std::list" );
        return os;
    }

    template<typename T>
    ostream & operator << ( ostream & os, const std::set<T>& s )
    {
        details::_write_container<T,std::set<T>>( os, s, "std::set" );
        return os;
    }

    template<typename T>
    ostream & operator << ( ostream & os, const std::multiset<T>& s )
    {
        details::_write_container<T,std::multiset<T>>( os, s, "std::multiset" );
        return os;
    }

    template<typename T>
    ostream & operator << ( ostream & os, const std::unordered_set<T>& s )
    {
        details::_write_container<T,std::unordered_set<T>>(os, s, "std::unordered_set");
        return os;
    }

    template<typename T>
    ostream & operator << ( ostream & os, const std::unordered_multiset<T>& s )
    {
        details::_write_container<T,std::unordered_multiset<T>>
                                                      (os, s, "std::unordered_multiset");
        return os;
    }

    template<typename T>
    ostream & operator << ( ostream & os, const std::deque<T>& d )
    {
        details::_write_container<T,std::deque<T>>( os, d, "std::deque" );
        return os;
    }

    template<typename T, typename U>
    ostream & operator << ( ostream & os, const std::map<T,U>& m )
    {
        details::_write_container<T,std::map<T,U>>( os, m, "std::map" );
        return os;
    }

    template<typename T, typename U>
    ostream & operator << ( ostream & os, const std::multimap<T,U>& m )
    {
        details::_write_container<T,std::multimap<T,U>>( os, m, "std::multimap" );
        return os;
    }

    template<typename T, typename U>
    ostream & operator << ( ostream & os, const std::unordered_map<T,U>& m )
    {
        details::_write_container<T,std::unordered_map<T,U>>(os, m,"std::unordered_map");
        return os;
    }

    template<typename T, typename U>
    ostream & operator << ( ostream & os, const std::unordered_multimap<T,U>& m )
    {
        details::_write_container<T,std::unordered_multimap<T,U>>
                                                       (os, m,"std::unordered_multimap");
        return os;
    }
} // std namespace




#endif // VCAT_CONTAINERS_H
