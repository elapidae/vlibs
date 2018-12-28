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
