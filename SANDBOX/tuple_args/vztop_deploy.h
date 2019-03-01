#ifndef VZTOP_DEPLOY_H
#define VZTOP_DEPLOY_H

#include <tuple>
#include <assert.h>

//=======================================================================================
namespace vztop
{
    //===================================================================================
    template<typename Lambda,typename T>
    struct result_of_lambda
    {
        using type = typename std::result_of<Lambda(T)>::type;
    };
    //===================================================================================

    //===================================================================================
    template<typename Res>
    struct Deploy
    {
        static const char* id()
        {
            assert(false && "Type not deployed.");
            return "";
        }

        void pack( const Res& )
        { assert(false && "Type not deployed."); }
    };
    //===================================================================================
    template<typename T>
    struct TypeSign;
    //===================================================================================
    template<typename ... Args>
    class Tuple : public std::tuple<Args...>
    {
    public:
        using base = typename std::tuple<Args...>;

        constexpr Tuple()
            : std::tuple<Args...>()
        {}

        //constexpr Tuple( Args&& ... args )
        //    : base( std::forward<Args>(args)... )
        //{}

        constexpr Tuple( const Args& ... args )
            : base( args... )
        {}

        enum { size = std::tuple_size<base>::value };

        template<size_t idx>
        struct element
        { using type = typename std::tuple_element<idx, base>::type; };

        template<size_t idx>
        constexpr const typename element<idx>::type& get() const
        { return std::get<idx>(*this); }



        static std::string args_signature()
        {
            std::string res = "<";
            _signature< std::tuple<Args...>, Args... >::s( &res );
            return res;
        }

        template<typename Tuple, typename T, typename ... Es>
        struct _signature
        {
            static void s( std::string *buf )
            {
                *buf += TypeSign<T>::sign();
                buf->push_back(',');

                using next_tup = std::tuple<Es...>;
                using next = _signature<next_tup,Es...>;
                next::s( buf );
            }
        };

        template<typename T>
        struct _signature<std::tuple<T>,T>
        {
            static void s( std::string *buf )
            {
                *buf += TypeSign<T>::sign();
                buf->push_back('>');
            }
        };

    };
    //===================================================================================
    template<typename ... Args>
    Tuple<Args...> pack_tuple( Args&& ... args )
    {
        return Tuple<Args...>( std::forward<Args>(args)... );
    }

    //===================================================================================


    //===================================================================================
    template<typename T>
    struct TypeSign
    {
        //===============================================================================
        enum _type { _plain, _vector, _deployed };
        //===============================================================================
        static std::string sign()
        {
            //  Строку считаем простой неделимой единицей.
            constexpr const bool is_plain = std::is_arithmetic<T>::value ||
                                            std::is_same<char,T>::value  ||
                                            std::is_base_of<std::string,T>::value;

            constexpr const bool has_deploy = !is_plain; // &&
                                              //!std::is_same<char,T>::value;

            return _sign<is_plain,has_deploy,true>::s();
        }
        //===============================================================================


        //===============================================================================
        template<bool is_simple, bool has_deploy, bool any>
        struct _sign;
        //===============================================================================
        template<bool has_deploy, bool any>
        struct _sign<true, has_deploy,any> // simple
        {
            static std::string s()
            {
                static std::string sz = sizeof(T) == 1 ? "1" :
                                        sizeof(T) == 2 ? "2" :
                                        sizeof(T) == 4 ? "4" :
                                        sizeof(T) == 8 ? "8" :
                                        (assert(false),"");

                static bool is_int = std::is_integral<T>::value;

                static std::string res =
                        std::is_base_of<std::string,T>::value   ? "string"      :
                        std::is_same<char,T>::value             ? "char"        :
                        std::is_floating_point<T>::value        ? "float" + sz  :
                        std::is_signed<T>::value   && is_int    ? "int"   + sz  :
                        std::is_unsigned<T>::value && is_int    ? "uint"  + sz  :
                        (assert(false),"");

                return res;
            }
        };
        //===============================================================================
        template<bool has_deploy, bool any>
        struct _sign<false, has_deploy, any>;
        //===============================================================================
        template<bool any>
        struct _sign<false, true,any> // has deploy
        {
            static constexpr const char* s()
            {
                return Deploy<T>::id();
            }
        };
        //===============================================================================
        template<bool any>
        struct _sign<false, false,any> // has not deploy
        {};
        //===============================================================================
    }; // TypeSign
    //===================================================================================

} // namespace vztop
//=======================================================================================



#endif // VZTOP_DEPLOY_H
