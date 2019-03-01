#ifndef SERIALIZATION_TYPE_SIGNATURE_H
#define SERIALIZATION_TYPE_SIGNATURE_H

#include "serialization/serialization_type_traits.h"
//=======================================================================================
/*
 * Signatures of types.
 *
 *  for simple types:
 *      - "int", "uint", "float" with size in bits;
 *      - "char8" for chars. As own, because it signed/unsiged in different systems;
 *      - "bool8" for bools. As own, because of garant one byte per value;
 *      - "string" for std::string;
 *
 *  for std::array<T,N>: "[T,N]";
 *
 *  for std::vector<T>: "vector<T>";
 *
 *  for std::tuple<T,U,V>: "{T,U,V}";
 *
 *  for VSerializable types: "NameOfType(label){SerializableTuple}";
 *
 *  for VSerialize_Size: "%size%";
*/
//=======================================================================================


//=======================================================================================
namespace serialization
{
    //===================================================================================
    template<typename T> static constexpr typename std::enable_if< is_simple<T>(),
    std::string>::type type_signature();
    template<typename T> static typename std::enable_if< is_array<T>(),
    std::string>::type type_signature();
    template<typename T> static typename std::enable_if< is_vector<T>(),
    std::string>::type type_signature();
    template<typename T> static typename std::enable_if< is_serializable<T>(),
    std::string>::type type_signature();
    template<typename T> static typename std::enable_if< is_tuple<T>(),
    std::string>::type type_signature();
    template<typename T> static constexpr typename std::enable_if<is_serialize_size<T>(),
    std::string>::type type_signature();
    //===================================================================================
    //  type_args_signature
    //  tuple_signature
    //  Итерируем до тех пор, пока не достигнем последнего элемента, когда достигнем,
    //  установим индекс в -1 и выйдем через специализированную структуру.
    template<int idx, typename Tuple>
    struct _tuple_signature
    {
        static void signature( std::string* res )
        {
            *res += type_signature<tuple_element<Tuple,idx>>();
            res->push_back(',');

            static constexpr auto next_idx = tuple_next_idx<idx,Tuple>();
            _tuple_signature< next_idx, Tuple >::signature( res );
        }
    };
    //-----------------------------------------------------------------------------------
    template<typename Tuple>
    struct _tuple_signature<-1,Tuple>
    {
        static void signature( std::string* ) {} // do nothing.
    };
    //-----------------------------------------------------------------------------------
    template<typename Tuple> static
    std::string tuple_signature()
    {
        std::string res = "{";

        _tuple_signature<tuple_start_idx<Tuple>(),Tuple>::signature( &res );

        if (tuple_size<Tuple>() == 0) res.push_back('}'); // сейчас в строке только '{'.
        else                          res.back() = '}';   // заменяем ','.

        return res;
    }
    //===================================================================================
    //  serializable_type_name<T>() -- выводит имя типа из __PRETTY_FUNCTION__. Проверено
    //  только на gcc, на других языках может дать ерунду, надо проверять.

    std::string _serializable_type_name( const std::string& pretty_func );

    template<typename T>
    std::string serializable_type_name()
    {
        static auto res = _serializable_type_name(__PRETTY_FUNCTION__);
        return res;
    }
    //-----------------------------------------------------------------------------------
    //  serializable_signature<T>() -- выводит полную сигнатуру типа сериазицации.
    //
    template<typename T> static
    std::string serializable_signature()
    {
        static auto res = serializable_type_name<T>() +
                          serializable_label<T>() +
                          tuple_signature< serializable_tuple_type<T> >();
        return res;
    }
    //===================================================================================
    template<typename T> static constexpr typename std::enable_if< is_simple<T>(),
    const char*>::type simple_type_signature()
    {
        static_assert( sizeof(char)   == 1, "sizeof(char)   != 1" );
        static_assert( sizeof(float)  == 4, "sizeof(float)  != 4" );
        static_assert( sizeof(double) == 8, "sizeof(double) != 8" );

        return
            std::is_same<char,T>::value     ? "char8"   :
            std::is_same<bool,T>::value     ? "bool8"   :

            std::is_same<int8_t,T>::value   ? "int8"    :
            std::is_same<uint8_t,T>::value  ? "uint8"   :

            std::is_same<int16_t,T>::value  ? "int16"   :
            std::is_same<uint16_t,T>::value ? "uint16"  :

            std::is_same<int32_t,T>::value  ? "int32"   :
            std::is_same<uint32_t,T>::value ? "uint32"  :

            std::is_same<int64_t,T>::value  ? "int64"   :
            std::is_same<uint64_t,T>::value ? "uint64"  :

            std::is_same<float,T>::value    ? "float32" :
            std::is_same<double,T>::value   ? "float64" :

            std::is_base_of<std::string,T>::value ? "string"
                                                  : "!!! Unknown type !!!";
    }
    //===================================================================================
    template<typename T> static constexpr typename std::enable_if< is_simple<T>(),
    std::string>::type type_signature()
    {
        return simple_type_signature<T>();
    }
    //-----------------------------------------------------------------------------------
    template<typename T> static typename std::enable_if< is_array<T>(),
    std::string>::type type_signature()
    {
        static std::string res = []()
        {
            std::stringstream ss;
            ss << "[" << type_signature<typename T::value_type>() << ","
               << tuple_size<T>() << "]";
            return ss.str();
        }();
        return res;
    }
    //-----------------------------------------------------------------------------------
    template<typename T> static typename std::enable_if< is_vector<T>(),
    std::string>::type type_signature()
    {
        using elem_type = typename T::value_type;
        return "vector<" + type_signature<elem_type>() + ">";
    }
    //-----------------------------------------------------------------------------------
    template<typename T> static typename std::enable_if< is_serializable<T>(),
    std::string>::type type_signature()
    {
        return serializable_signature<T>();
    }
    //-----------------------------------------------------------------------------------
    template<typename T> static constexpr typename std::enable_if<is_serialize_size<T>(),
    std::string>::type type_signature()
    {
        return "%size%";
    }
    //-----------------------------------------------------------------------------------
    template<typename T> static typename std::enable_if< is_tuple<T>(),
    std::string>::type type_signature()
    {
        return tuple_signature<T>();
    }
    //===================================================================================
    template<typename T>
    static constexpr typename std::enable_if< std::is_pointer<T>::value,
    std::string>::type type_signature()
    {
        static_assert ( !std::is_pointer<T>::value, "POINTER must not be serialize." );
        return "!!! POINTER must not be serialize. !!!";
    }
    //===================================================================================
    template<typename T>
    static constexpr typename std::enable_if< std::is_reference<T>::value,
    std::string>::type type_signature()
    {
        static_assert(!std::is_reference<T>::value, "REFERENCE must not be serialize.");
        return "!!! REFERENCE must not be serialize !!!";
    }
    //===================================================================================
} // namespace serialization
//=======================================================================================


#endif // SERIALIZATION_TYPE_SIGNATURE_H
