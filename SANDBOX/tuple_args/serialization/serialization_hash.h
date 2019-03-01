#ifndef SERIALIZATION_HASH_H
#define SERIALIZATION_HASH_H

#include "serialization/serialization_type_traits.h"
#include "serialization/serialization_type_signature.h"
#include "serialization/serialization_type_compare.h"

//#include <set>

//=======================================================================================
namespace serialization
{
    //===================================================================================
    using hash_type = uint32_t;
    using channel_hash_type = uint32_t;
    hash_type _hash_func( const std::string& signature );
    void _collisions_check( hash_type check );
    //===================================================================================
    template<typename T>
    static hash_type hash_of_name()
    {
        static_assert ( is_serializable<T>(), "hash_of_name: !is_serializable<T>" );

        static auto res = []()
        {
            auto res = _hash_func( serializable_type_name<T>() );
            _collisions_check( res );
            return res;
        }();

        return res;
    }
    //===================================================================================
    template<typename T>
    static hash_type hash_of_signature()
    {
        static_assert ( is_serializable<T>(), "hash_of_name: !is_serializable<T>" );

        static auto res = _hash_func( serializable_signature<T>() );
        return res;
    }
    //===================================================================================
    channel_hash_type hash_of_channel( const std::string& channel );
    //===================================================================================

    //===================================================================================

} // namespace serialization
//=======================================================================================


//=======================================================================================
namespace serialization
{
    //===================================================================================
    template<typename T> static typename std::enable_if< is_bool<T>()        ||
                                                         is_arithmetic<T>()  ||
                                                         is_string<T>()      ,
    size_t>::type calc_hash( const T& val );

    template<typename T> static typename std::enable_if< is_serialize_size<T>(),
    size_t>::type calc_hash( const T& val );

    template<typename T> static typename std::enable_if< is_serializable<T>(),
    size_t>::type calc_hash( const T& val );

    template<typename T> static typename std::enable_if< is_tuple<T>(),
    size_t>::type calc_hash( const T& val );

    template<typename T> static typename std::enable_if< is_vector<T>() ||
                                                         is_array<T>()  ,
    size_t>::type calc_hash( const T& val );

    //===================================================================================
    template<typename T> static typename std::enable_if< is_bool<T>()        ||
                                                         is_arithmetic<T>()  ||
                                                         is_string<T>()      ,
    size_t>::type calc_hash( const T& val )
    {
        return std::hash<T>()( val );
    }
    //===================================================================================
    template<typename T> static typename std::enable_if<is_serialize_size<T>(),
    size_t>::type calc_hash( const T& val )
    {
        return std::hash<typename T::value_type>()( val.value() );
    }
    //===================================================================================
    template<typename T> static typename std::enable_if< is_serializable<T>(),
    size_t>::type calc_hash( const T& val )
    {
        return calc_hash( VSerializable<T>()(val) );
    }
    //===================================================================================

    template<typename T> static typename std::enable_if< is_vector<T>() ||
                                                         is_array<T>()  ,
    size_t>::type calc_hash( const T& val )
    {
        size_t res = 0;
        for ( const auto& v: val )
            res ^= calc_hash(v);
        return res;
    }
    //===================================================================================
    template<int idx, typename Tuple>
    struct _tuple_hash
    {
        static constexpr size_t shash( const Tuple& tup )
        {
            using next_hash = _tuple_hash< tuple_next_idx<idx,Tuple>(), Tuple >;
            return calc_hash(std::get<idx>(tup)) ^ next_hash::shash(tup);
        }
    };
    //-----------------------------------------------------------------------------------
    template<typename Tuple>
    struct _tuple_hash<-1,Tuple>
    {
        static constexpr size_t shash( const Tuple& )
        {
            return 0xbeaf404; // any magic is ok.
        }
    };
    //-----------------------------------------------------------------------------------
    template<typename T> static typename std::enable_if< is_tuple<T>(),
    size_t>::type calc_hash( const T& val )
    {
        return _tuple_hash<tuple_start_idx<T>(),T>::shash( val );
    }
    //===================================================================================
} // namespace serialization
//=======================================================================================

//=======================================================================================
template<typename T>
struct Vserialize_Hash : public T
{
    using T::T;
    size_t calc_hash() const noexcept
    {
        return serialization::calc_hash<T>();
    }
};
namespace std
{
    template<typename T>
    struct hash< Vserialize_Hash<T> >
    {
        size_t operator()( const Vserialize_Hash<T>& val ) const noexcept
        {
            return val.calc_hash();
        }
    };
}
//=======================================================================================

/*  Template, replace MyType to need typename.
//=======================================================================================
namespace std
{
    template<>
    struct hash<MyType>
    {
        size_t operator()( const MyType& val ) const noexcept
        {
            return serialization::calc_hash( val );
        }
    };
}
//=======================================================================================
*/



#endif // SERIALIZATION_HASH_H
