#ifndef VZTOP_SIGNATURE_H
#define VZTOP_SIGNATURE_H

#include "vztop_deploy.h"
#include <algorithm>
#include "vcrc.h"
#include <assert.h>
#include "vlog_pretty.h"

namespace vztop
{
    template<typename T>
    struct Signature
    {
        enum class Type { Plain, Vector, Deployed };

        static constexpr bool is_plain()
        { return std::is_arithmetic<T>::value ||
                 std::is_base_of<std::string,T>().value; }

        template<typename U>
        struct _is_vector { bool const value = false; };

        template<typename U>
        struct _is_vector<std::vector<U>> { bool const value = true; };

        static constexpr bool is_vector() { return _is_vector<T>().value; }

        static constexpr bool is_string()
        { return std::is_base_of<std::string,T>().value; }

        // TODO: Сделать проверку на деплой, пока не понимаю как.
        static constexpr Type type() { return is_plain()  ? Type::Plain  :
                                              is_vector() ? Type::Vector :
                                                            Type::Deployed;
                                     }

        //  Чтобы вызов хэширующей функции был в одном месте, не расползался.
        static uint32_t _crc( const std::string& str )
        {
            return vcrc::poly_04C11DB7( str );
        }

        static uint32_t name_crc()
        {
            static const auto res = []()
            {
                std::string id = Deploy<T>::id();
                auto first_space = std::find( id.begin(), id.end(), ' ' );
                return _crc( {id.begin(), first_space} );
            }();
            return res;
        }

        static uint32_t full_crc()
        {
            static const auto res = []()
            {
                //static_cast<(_deploy::*)(const T&)>(&_deploy::pack);
                //using PP = typename static_cast<&_deploy>()
                using P = typename
                    std::result_of<decltype(&Deploy<T>::pack)(const T&)>::type;

                std::string sign = Deploy<T>::id() + P::args_signature();
                return _crc( sign );
            }();
            return res;
        }

    }; // Signature

} // namespace vztop


#endif // VZTOP_SIGNATURE_H
