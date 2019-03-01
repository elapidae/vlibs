#ifndef ISHUMI_IMPL_SIGNATURE_H
#define ISHUMI_IMPL_SIGNATURE_H

#include <algorithm>
#include <stdint.h>
#include <string>
#include <vector>

#include "ishumi_serialize.h"
#include "vlog_pretty.h"

#include "vcrc.h"


//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wunused-template"
#pragma GCC diagnostic ignored "-Wunused-function"
namespace ishumi
{
    //===================================================================================
    namespace impl
    {
        //===============================================================================
        enum class Serial_Spec { Simple, Vector, Serialized, Tuple, Undefined };
        template<typename T> static constexpr Serial_Spec serial_spec();
        //===============================================================================
        template<typename T>
        using serialize_id_type = decltype( Serialize<T>::id() );

        template<typename T>
        using serialize_tuple_type = typename
            std::result_of<decltype(&Serialize<T>::operator())(Serialize<T>,T)>::type;
        //using serialize_reduce_type = typename
        //std::result_of<decltype(&Serialize<T>::reduce)(Serialize<T>,T)>::type;
        //using serialize_reduce_type = typename
        //std::result_of<decltype(Serialize<T>::reduce)(Serialize<T>,T)>::type;
        //typename srl::result_of_arg1<decltypeSerialize<T>::reduce,T>;
        //using serialize_reduce_type = decltype( Serialize<T>().reduce(T()) );
        //===============================================================================
        template<typename T>
        std::string extract_T_name()
        {
            static constexpr const char begin_sign[] = "ishumi::impl::extract_T_name() [with T = ";
            static constexpr const char end_sign[]   = ";";

            std::string pretty_func = __PRETTY_FUNCTION__;

            auto b = pretty_func.find(begin_sign) + sizeof(begin_sign) - 1;
            auto e = pretty_func.find(end_sign);
            //assert( e > b );
            return pretty_func.substr( b, e - b ) + " "; // Пробел -- чтобы не забывали.
        }
        //===============================================================================
        //using str_vec_sizetype = uint32_t;
        using signature_type = uint32_t;
        static signature_type _use_this_signature_hash( const std::string& str )
        {
            return vcrc::poly_04C11DB7( str );
        }
        //  проверяет что такого имени еще не было.
        void add_check_signature( signature_type sig_of_name );
        //===============================================================================
        template<typename T> static constexpr bool is_simple();
        template<typename T> static constexpr bool is_vector();
        template<typename T> static constexpr bool is_serialize();
        //-------------------------------------------------------------------------------
        template<typename T> static typename std::enable_if< is_serialize<T>(),
        signature_type>::type full_serialize_signature();
        //-------------------------------------------------------------------------------
        template<typename T> static typename std::enable_if< is_serialize<T>(),
        signature_type>::type name_serialize_signature();
        //===============================================================================
        template<typename T> static constexpr
        bool is_string()            { return std::is_base_of<std::string,T>::value; }
        //===============================================================================
        template<typename T> static constexpr
        bool is_arithmetic()        { return std::is_arithmetic<T>::value; }
        //===============================================================================
        //  Строку тоже считаем простым типом, т.к. реализации чтения и записи можно
        //  перенести в буфферы, подальше от развертки аргументов.
        template<typename T> static constexpr
        bool is_simple()            { return is_arithmetic<T>() || is_string<T>(); }
        //===============================================================================
        template<typename T>
        struct _is_vector { bool const value = false; };

        template<typename T>
        struct _is_vector<std::vector<T>> { bool const value = true; };

        template<typename T> static constexpr
        bool is_vector() { return _is_vector<T>().value; }
        //===============================================================================
        //template<typename T> static constexpr bool check_that_in_one_group();
        template<typename T> static constexpr bool is_tuple();

        template<typename T> static constexpr Serial_Spec serial_spec()
        {
            static_assert( is_simple<T>()      ? 1 : 0 +
                           is_vector<T>()      ? 1 : 0 +
                           is_serialize<T>()   ? 1 : 0 +
                           is_tuple<T>()       ? 1 : 0 == 1,
                           "Либо тип не подлежит сериализации, либо сериализация не "
                           "объявлена. Проверьте объявление template<> Serialize<T> "
                           "для этого типа. Не могут специализироваться арифметические "
                           "типы, строки, кортежи, вектора и пр. стандартные типы." );


            return is_simple<T>()       ? Serial_Spec::Simple       :
                   is_vector<T>()       ? Serial_Spec::Vector       :
                   is_serialize<T>()    ? Serial_Spec::Serialized   :
                   is_tuple<T>()        ? Serial_Spec::Tuple        :
                                          Serial_Spec::Undefined;
        }
        //===============================================================================
        template<typename T> static constexpr
        bool _is_string_or_const_char()
        { return is_string<T>() || std::is_same<const char*,T>::value; }

        template<typename T, typename = bool>
        struct _has_serialize_id: std::false_type {};

        template<typename T>
        struct _has_serialize_id< T,
                typename std::enable_if<_is_string_or_const_char<serialize_id_type<T>>(),
                                        bool>::type > : std::true_type
        {};
        //-------------------------------------------------------------------------------
        template<typename T, typename = void>
        struct _is_tuple: std::false_type {};

        template<typename T>
        struct _is_tuple< T,
                typename std::enable_if<( std::tuple_size<T>::value >= 0 ), void>::type>
            : std::true_type
        {};

        template<typename T> static constexpr
        bool is_tuple()     { return _is_tuple<T>::value; }

        template<typename T> static constexpr
        int first_tuple_idx()
        { return std::tuple_size<T>::value == 0 ? -1 : 0; }
        //-------------------------------------------------------------------------------
        template<typename T, typename = void>
        struct _has_serialize_reduce: std::false_type {};

        template<typename T>
        struct _has_serialize_reduce< T,
                typename std::enable_if<_is_tuple<serialize_tuple_type<T>>::value,
                                        void>::type>
            : std::true_type
        {};
        //-------------------------------------------------------------------------------
        template<typename T> static constexpr
        bool is_serialize()
        {
            return _has_serialize_id<T>::value &&
                   _has_serialize_reduce<T>::value;
        }
        //-------------------------------------------------------------------------------
//        template<typename T> static constexpr
//        bool check_that_in_one_group()
//        {
//            return true;
////            constexpr const int count = is_simple<T>()      ? 1 : 0 +
////                                        is_vector<T>()      ? 1 : 0 +
////                                        is_serialize<T>()   ? 1 : 0 +
////                                        is_tuple<T>()       ? 1 : 0;

//            static_assert( is_simple<T>()      ? 1 : 0 +
//                                                 is_vector<T>()      ? 1 : 0 +
//                                                 is_serialize<T>()   ? 1 : 0 +
//                                                 is_tuple<T>()       ? 1 : 0 == 1, "Type is not unique type trait." );
//        }
        //===============================================================================


        //===============================================================================
        template<typename T> static constexpr typename std::enable_if< is_simple<T>(),
        const char*>::type simple_type_signature()
        {
            static_assert( sizeof(char)   == 1, "sizeof(char)   != 1" );
            static_assert( sizeof(float)  == 4, "sizeof(float)  != 4" );
            static_assert( sizeof(double) == 8, "sizeof(double) != 8" );

            return
                std::is_same<char,T>::value     ? "char8"   :

                std::is_same<int8_t,T>::value   ? "int8"    :
                std::is_same<uint8_t,T>::value  ? "uint8"   :

                std::is_same<int16_t,T>::value  ? "int16"   :
                std::is_same<uint16_t,T>::value ? "uint16"  :

                std::is_same<int32_t,T>::value  ? "int32"   :
                std::is_same<uint32_t,T>::value ? "uint32"  :

                std::is_same<int64_t,T>::value  ? "int64"   :
                std::is_same<uint64_t,T>::value ? "uint64"  :

                std::is_same<float,T>::value    ? "float32"  :
                std::is_same<double,T>::value   ? "double64" :

                std::is_base_of<std::string,T>::value ? "string"
                                                      : "!!! Unknown type !!!";
        }
        //===============================================================================
        template<typename T> static typename std::enable_if< is_simple<T>(),
        std::string>::type type_signature()
        {
            return simple_type_signature<T>();
        }

        template<typename T> static typename std::enable_if< is_serialize<T>(),
        std::string>::type serialize_signature();

        template<typename T> static typename std::enable_if< is_serialize<T>(),
        std::string>::type type_signature()
        {
            return serialize_signature<T>();
        }

        template<typename T> static typename std::enable_if< is_vector<T>(),
        std::string>::type type_signature()
        {
            using elem_type = typename T::value_type;
            return "vector<" + type_signature<elem_type>() + ">";
        }

        template<typename atuple> std::string tuple_signature();

        template<typename T> static typename std::enable_if< is_tuple<T>(),
        std::string>::type type_signature()
        {
            return tuple_signature<T>();
        }
        //===============================================================================
        //  Итерируем до тех пор, пока не достигнем последнего элемента, когда достигнем,
        //  установим индекс в -1 и выйдем через специализированную структуру.
        template<int idx, typename atuple>
        struct TupleSignature
        {
            static void signature( std::string* res )
            {
                using element = typename std::tuple_element<idx,atuple>::type;
                static constexpr auto tup_size = std::tuple_size<atuple>::value;
                static constexpr auto next_idx = idx + 1 == tup_size ? -1 : idx + 1;

                *res += type_signature<element>();
                res->push_back(',');

                TupleSignature<next_idx,atuple>::signature( res );
            }
        };
        //-------------------------------------------------------------------------------
        template<typename atuple>
        struct TupleSignature<-1,atuple>
        {
            static void signature( std::string* )
            {} // do nothing.
        };
        //-------------------------------------------------------------------------------
        template<typename atuple>
        std::string tuple_signature()
        {
            std::string res = "{";
            static constexpr auto idx = first_tuple_idx<atuple>();
            TupleSignature<idx,atuple>::signature( &res );
            if (idx == -1)
                res.push_back('}');
            else
                res.back() = '}';
            return res;
        }
        //-------------------------------------------------------------------------------
        template<typename T> static typename std::enable_if< is_serialize<T>(),
        std::string>::type serialize_name()
        {
            // Именем считаем все до первого пробела.
            std::string full_id = Serialize<T>::id();
            return { full_id.begin(), std::find(full_id.begin(), full_id.end(), ' ') };
        }
        //-------------------------------------------------------------------------------
        template<typename T> static typename std::enable_if< is_serialize<T>(),
        std::string>::type serialize_signature()
        {
            return Serialize<T>::id() + tuple_signature<serialize_tuple_type<T>>();
        }
        //===============================================================================
        template<typename T> static typename std::enable_if< is_serialize<T>(),
        signature_type>::type full_serialize_signature()
        {
            return _use_this_signature_hash( serialize_signature<T>() );
        }
        //-------------------------------------------------------------------------------
        template<typename T> static typename std::enable_if< is_serialize<T>(),
        signature_type>::type name_serialize_signature()
        {
            static signature_type res = _use_this_signature_hash( serialize_name<T>() );
            add_check_signature( res );
            return res;
        }
        //===============================================================================
    } // namespace impl
    //===================================================================================
} // namespace ishumi
#pragma GCC diagnostic pop
//=======================================================================================

#endif // ISHUMI_IMPL_SIGNATURE_H
