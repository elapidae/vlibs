#ifndef SERIALIZATION_TYPE_COMPARE_H
#define SERIALIZATION_TYPE_COMPARE_H

#include "serialization/serialization_type_traits.h"

//=======================================================================================
namespace serialization
{
    //===================================================================================
    template<typename T> static constexpr typename std::enable_if< is_bool<T>(),
    bool>::type _equal( const T& lhs, const T& rhs );

    template<typename T> static constexpr typename std::enable_if<is_arithmetic<T>()   ||
                                                                  is_string<T>()       ||
                                                                  is_serialize_size<T>(),
    bool>::type _equal( const T& lhs, const T& rhs );

    template<typename T> static typename std::enable_if< is_vector<T>() ||
                                                         is_array<T>(),
    bool>::type _equal( const T& lhs, const T& rhs );

    template<typename T> static constexpr typename std::enable_if< is_tuple<T>(),
    bool>::type _equal( const T& lhs, const T& rhs );

    template<typename T> static constexpr typename std::enable_if< is_serializable<T>(),
    bool>::type _equal( const T& lhs, const T& rhs );
    //===================================================================================
    //  Не удивляйтесь, при сравнении неициализированной/нестандартной bool может
    //  быть что угодно. Поэтому проверяем аккуратно.
    template<typename T> static constexpr typename std::enable_if< is_bool<T>(),
    bool>::type _equal( const T& lhs, const T& rhs )
    {
        return (lhs ? 1 : 0) == (rhs ? 1 : 0);
    }
    //===================================================================================
    template<typename T> static constexpr typename std::enable_if<is_arithmetic<T>()   ||
                                                                  is_string<T>()       ||
                                                                  is_serialize_size<T>(),
    bool>::type _equal( const T& lhs, const T& rhs )
    {
        return lhs == rhs;
    }
    //===================================================================================
    template<typename T> static typename std::enable_if< is_vector<T>() ||
                                                         is_array<T>(),
    bool>::type _equal( const T& lhs, const T& rhs )
    {
        if ( lhs.size() != rhs.size() ) return false;

        auto i1 = lhs.begin();
        auto i2 = rhs.begin();
        while ( i1 != lhs.end() )
        {
            if ( !_equal(*i1++, *i2++) ) return false;
        }
        return true;
    }
    //===================================================================================
    template<int idx, typename Tup>
    struct _equal_tuple
    {
        static constexpr bool eq( const Tup& lhs, const Tup& rhs )
        {
            return _equal( std::get<idx>(lhs), std::get<idx>(rhs) ) &&
                   _equal_tuple< tuple_next_idx<idx,Tup>(), Tup >::eq( lhs, rhs );
        }
    };
    //-----------------------------------------------------------------------------------
    template<typename Tup>
    struct _equal_tuple<-1, Tup>
    {
        static constexpr bool eq( const Tup&, const Tup& )
        { return true; }
    };
    //-----------------------------------------------------------------------------------
    template<typename T> static constexpr typename std::enable_if< is_tuple<T>(),
    bool>::type _equal( const T& lhs, const T& rhs )
    {
        return _equal_tuple< tuple_start_idx<T>(), T >::eq( lhs, rhs );
    }
    //===================================================================================
    template<typename T> static constexpr typename std::enable_if< is_serializable<T>(),
    bool>::type _equal( const T& lhs, const T& rhs )
    {
        return _equal( VSerializable<T>()(lhs), VSerializable<T>()(rhs) );
    }
    //===================================================================================

} // namespace serialization
//=======================================================================================


//=======================================================================================
template<typename T> static typename std::enable_if< serialization::is_serializable<T>(),
bool>::type operator == ( const T& lhs, const T& rhs )
{
    return serialization::_equal( lhs, rhs );
}
//===================================================================================
template<typename T> static typename std::enable_if< serialization::is_serializable<T>(),
bool>::type operator != ( const T& lhs, const T& rhs )
{
    return !( lhs == rhs );
}
//===================================================================================


#endif // SERIALIZATION_TYPE_COMPARE_H
