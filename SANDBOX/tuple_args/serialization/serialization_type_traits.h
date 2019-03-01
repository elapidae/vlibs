#ifndef SERIALIZATION_TYPE_TRAITS_H
#define SERIALIZATION_TYPE_TRAITS_H


#include <type_traits>
#include <string>
#include <vector>
#include <array>

#include <vserializable.h>
#include <sstream>

template<class T> class TD;
template<int> class TDI;

//=======================================================================================
namespace serialization
{
    //===================================================================================
    enum class Type_Spec
    {
        Simple,
        Array,
        Vector,
        Serialized,
        Serialized_Size,
        Tuple,
        Undefined };
    template<typename T> static constexpr Type_Spec type_spec();
    //===================================================================================
    template<typename T> static constexpr bool is_bool();
    template<typename T> static constexpr bool is_arithmetic();
    template<typename T> static constexpr bool is_container();

    template<typename T> static constexpr bool is_string();
    template<typename T> static constexpr bool is_simple();
    template<typename T> static constexpr bool is_vector();
    template<typename T> static constexpr bool is_array();
    template<typename T> static constexpr bool is_tuple();
    template<typename T> static constexpr bool is_serializable();
    template<typename T> static constexpr bool is_serialize_size();

    //  Цель сей странной функции -- установить сколько реально байт нужно для записи
    //  конкретного размера с поток.
    size_t size_of_size( size_t sz );

    uint8_t _bool_to_byte ( bool b    );
    bool _bool_from_byte  ( uint8_t u ); // throw Decoder::DecodeError.
    //===================================================================================
    //  simple types
    template<typename T> static constexpr
    bool is_bool() { return std::is_same<bool,T>::value; }
    //-----------------------------------------------------------------------------------
    template<typename T> static constexpr
    bool is_arithmetic() { return std::is_arithmetic<T>::value && !is_bool<T>(); }
    //-----------------------------------------------------------------------------------
    template<typename T> static constexpr
    bool is_string()
    { return std::is_base_of<std::string,T>(); }
    //-----------------------------------------------------------------------------------
    template<typename T> static constexpr
    bool is_simple()
    { return is_bool<T>() || is_arithmetic<T>() || is_string<T>(); }
    //-----------------------------------------------------------------------------------
    template<typename T> static constexpr
    bool is_serialize_size() { return std::is_same<VSerialize_Size,T>::value; }

    //===================================================================================
    //  is_vector
    template<typename T>
    struct _is_vector : std::false_type {};

    template<typename T>
    struct _is_vector<std::vector<T>> : std::true_type {};

    template<typename T> static constexpr
    bool is_vector() { return _is_vector<T>::value; }

    //===================================================================================
    //  is_tuple, tuple helpers
    template<typename T, typename = void>
    struct _has_tuple_size: std::false_type {};

    template<typename T>
    struct _has_tuple_size< T, typename
                    std::enable_if<( std::tuple_size<T>::value >= 0 ), void>::type>
        : std::true_type {};

    template<typename T> static constexpr
    bool has_tuple_size() { return _has_tuple_size<T>::value; }

    template<typename T> static constexpr
    bool is_tuple() { return has_tuple_size<T>() && !is_container<T>(); }

    template<typename T> static constexpr
    int tuple_size() { return std::tuple_size<T>::value; }

    template<typename T> static constexpr // Используется при итерациях с кортежами.
    int tuple_start_idx() { return std::tuple_size<T>::value == 0 ? -1 : 0; }

    template<int idx, typename T> static constexpr
    int tuple_next_idx() { return idx + 1 == tuple_size<T>() ? -1 : idx + 1; }

    template<typename T, int idx>
    using tuple_element = typename std::tuple_element<idx,T>::type;

    //===================================================================================
    //  vectors
    template<typename T, typename = void>
    struct _has_value_type: std::false_type {};

    template<typename T>
    struct _has_value_type< T, typename std::enable_if<( std::is_same<
                            typename T::value_type, typename T::value_type>::value ),
                    void>::type> : std::true_type {};

    template<typename T> static constexpr
    bool has_value_type() { return _has_value_type<T>::value; }
    //-------------------------------------------------------------------------------
    template<typename T, typename = void>
    struct _has_size_type: std::false_type {};

    template<typename T>
    struct _has_size_type< T, typename std::enable_if<( std::is_same<
                              typename T::size_type, typename T::size_type>::value ),
                    void>::type> : std::true_type {};

    template<typename T> static constexpr
    bool has_size_type() { return _has_size_type<T>::value; }
    //-------------------------------------------------------------------------------
    // TODO: мало проверок на контейнеризацию.
    template<typename T> static constexpr
    bool is_container() { return has_size_type<T>() && has_value_type<T>(); }

    //===================================================================================
    //  arrays
    // https://ru.cppreference.com/w/cpp/container/array
    template<typename T> static constexpr
    bool is_array() { return is_container<T>() && has_tuple_size<T>(); }

    //===================================================================================
    // serializable
    //  serializable_tuple_type, is_serializable<T>()

    template<typename T>
    using serializable_tuple_type = typename std::result_of<
                    decltype(&VSerializable<T>::operator())(VSerializable<T>,T)>::type;

    template<typename T, typename = void>
    struct _has_serializable_tuple: std::false_type {};

    template<typename T>
    struct _has_serializable_tuple< T,
            typename std::enable_if<is_tuple<serializable_tuple_type<T>>(), void>
                                ::type> : std::true_type {};

    template<typename T> static constexpr
    bool is_serializable() { return _has_serializable_tuple<T>::value; }

    //-----------------------------------------------------------------------------------
    //  serializable_label() -- Метку пишем в скобочках, так глазу приятнее. Если метку
    //  не ввели, оставляем скобоки пустыми.
    //
    template<typename T> static constexpr
    bool _is_string_or_cstr()
    { return is_string<T>() || std::is_same<const char*,T>::value; }

    template<typename T>
    using _serializable_label_type = decltype( VSerializable<T>::label() );

    template<typename T, typename = void>
    struct _serializable_label { static const std::string label() { return "()"; } };

    template<typename T>
    struct _serializable_label< T, typename std::enable_if<
                       _is_string_or_cstr<_serializable_label_type<T>>(),void>::type>
    {
        static const std::string label()
        {
            static auto res = std::string("(") + VSerializable<T>::label() + ")";
            return res;
        }
    };

    template<typename T> static
    std::string serializable_label()
    { return _serializable_label<T>::label(); }
    //-----------------------------------------------------------------------------------
    //===================================================================================
    template<typename T> static constexpr
    Type_Spec type_spec()
    {
        static_assert( is_simple<T>()         ? 1 : 0 +
                       is_array<T>()          ? 1 : 0 +
                       is_vector<T>()         ? 1 : 0 +
                       is_serializable<T>()   ? 1 : 0 +
                       is_serialize_size<T>() ? 1 : 0 +
                       is_tuple<T>()          ? 1 : 0 == 1,
                       "Либо тип не подлежит сериализации, либо сериализация не "
                       "объявлена. Проверьте объявление template<> Serializable<T> "
                       "для этого типа. Не могут специализироваться арифметические "
                       "типы, строки, кортежи, вектора и пр. стандартные типы." );

        return is_simple<T>()           ? Type_Spec::Simple          :
               is_array<T>()            ? Type_Spec::Array           :
               is_vector<T>()           ? Type_Spec::Vector          :
               is_serializable<T>()     ? Type_Spec::Serialized      :
               is_serialize_size<T>()   ? Type_Spec::Serialized_Size :
               is_tuple<T>()            ? Type_Spec::Tuple           :
                                          Type_Spec::Undefined;
    }

    //===================================================================================
    //  Вывод минимальных размеров сериализации.
    template<typename T> static constexpr typename std::enable_if< is_bool<T>(),
    size_t>::type min_size();
    template<typename T> static constexpr typename std::enable_if< is_arithmetic<T>(),
    size_t>::type min_size();
    template<typename T> static constexpr typename std::enable_if< is_string<T>(),
    size_t>::type min_size();
    template<typename T> static typename std::enable_if< is_array<T>(),
    size_t>::type min_size();
    template<typename T> static typename std::enable_if< is_vector<T>(),
    size_t>::type min_size();
    template<typename T> static typename std::enable_if< is_serializable<T>(),
    size_t>::type min_size();
    template<typename T> static typename std::enable_if< is_serialize_size<T>(),
    size_t>::type min_size();
    template<typename T> static typename std::enable_if< is_tuple<T>(),
    size_t>::type min_size();
    //-----------------------------------------------------------------------------------
    template<int idx, typename Tuple>
    struct _min_tuple_size
    {
        static constexpr size_t tsize()
        {
            using cur_elem = tuple_element<Tuple,idx>;
            //TD<cur_elem> ddd;
            //TDI<min_size<cur_elem>()> iii;
            return min_size<cur_elem>() +
                   _min_tuple_size<tuple_next_idx<idx,Tuple>(),Tuple>::tsize();
        }
    };
    //-----------------------------------------------------------------------------------
    template<typename T>
    struct _min_tuple_size<-1,T>
    {
        static constexpr size_t tsize()
        {
            return 0;
        }
    };
    //-----------------------------------------------------------------------------------
    template<typename T> static constexpr typename std::enable_if< is_bool<T>(),
    size_t>::type min_size()
    {
        return 1;
    }
    //-----------------------------------------------------------------------------------
    template<typename T> static constexpr typename std::enable_if<is_arithmetic<T>(),
    size_t>::type min_size()
    {
        return sizeof(T);
    }
    //-----------------------------------------------------------------------------------
    template<typename T> static constexpr typename std::enable_if<is_string<T>(),
    size_t>::type min_size()
    {
        return 1;
    }
    //-----------------------------------------------------------------------------------
    template<typename T> static typename std::enable_if< is_array<T>(),
    size_t>::type min_size()
    {
        return tuple_size<T>() * min_size<typename T::value_type>();
    }
    //-----------------------------------------------------------------------------------
    template<typename T> static typename std::enable_if< is_vector<T>(),
    size_t>::type min_size()
    {
        return 1;
    }
    //-----------------------------------------------------------------------------------
    template<typename T> static typename std::enable_if< is_serializable<T>(),
    size_t>::type min_size()
    {
        return min_size< serializable_tuple_type<T> >();
    }
    //-----------------------------------------------------------------------------------
    template<typename T> static typename std::enable_if< is_serialize_size<T>(),
    size_t>::type min_size()
    {
        return 1;
    }
    //-----------------------------------------------------------------------------------
    template<typename T> static typename std::enable_if< is_tuple<T>(),
    size_t>::type min_size()
    {
        return _min_tuple_size< tuple_start_idx<T>(), T >::tsize();
    }

    //===================================================================================
    //  Была мысль сделать проверку соответствия аргументов конструктора или
    //  инициализатора кортежу. Плохо то, что типы могут не иметь
    //  конструкторов по умолчанию, соотв. просто так вывести не получается.
    //  Надо будет посмотреть в сторону методов decode.
    //===================================================================================


} // namespace serialization
//=======================================================================================


#endif // SERIALIZATION_TYPE_TRAITS_H
