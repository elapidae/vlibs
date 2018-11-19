#ifndef VPOSIX_CORE_H
#define VPOSIX_CORE_H

#include <type_traits>
#include <errno.h>
#include <stdexcept>
#include <string>
#include "vposix_errno.h"
#include "verror.h"


//=======================================================================================
//  class Errno
//
//  Соответствия ошибок есть здесь:
//  https://ru.cppreference.com/w/cpp/error/errc
//
//=======================================================================================


//=======================================================================================
namespace vposix
{
    //===================================================================================

    constexpr bool do_trace() { return true; }

    //===================================================================================
    class Core
    {
    public:
        //===============================================================================
        static std::string str_error( int err );
        //===============================================================================
        [[noreturn]]
        static void throw_err( int err, const std::string& who );
        //===============================================================================

        //  Тестовая версия.
        template< typename Fn, typename ... Args >
        static auto linux_call( Fn fn, Args ... args ) -> decltype( fn(args...) );
        //===============================================================================
        //
        //  linux_call сделан по образу Qt макроса EINTR_LOOP, который гоняет в
        //  цикле вызов до тех пор, пока либо не будет успешного вызова либо пока ошибка
        //  будет EINTR, означающая, что вызов функции был сброшен из-за прерывания.
        //  Linux такая linux.
        //
        //  Кидает исключение в случае ошибки, иначе возвращает результат функции Fn.
        //  Вызывается примерно так: auto fd = vposix::linux_call<int>(::open, O_RDWR);
        //
        //template< typename RetType, typename Fn, typename ... Args >
        //static RetType linux_call_r( Fn fn, Args ... args );
        //===============================================================================
        //
        //  Не бросает исключение, возвращает как есть. Дальше ковыряйтесь с errno сами.
        //
        template< typename Fn, typename ... Args >
        static auto linux_call_or_err( Fn fn, Args ... args ) -> decltype( fn(args...) );
        //===============================================================================
    }; // Core
    //===================================================================================

    class Errno
    {
    public:
        Errno();

        int has()  const;
        int code() const;
        std::string str() const;
        [[noreturn]] void throw_verror() const; //  Вызввает исключение, если ошибка есть.

        bool eagain() const;
        bool resource_unavailable_try_again() const;    // as c++11.

    private:
        int _err;
    };


    //===================================================================================
    //      IMPLEMENTATION
    //===================================================================================
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wnoexcept-type"
    //===================================================================================
    template<typename Fn, typename ... Args>
    auto Core::linux_call_or_err( Fn fn, Args ... args ) -> decltype( fn(args...) )
    {
        decltype(fn(args...)) res;

        do {
            res = fn( args... );
        } while ( res == -1 && errno == EINTR );

        return res;
    }
    //===================================================================================
    template< typename Fn, typename ... Args >
    auto Core::linux_call( Fn fn, Args ... args ) -> decltype( fn(args...) )
    {
        auto res = linux_call_or_err( std::forward<Fn>(fn),
                                      std::forward<Args>(args)... );

        if ( res != -1 ) return res;

        throw_err( errno, "linux_call" );
    }
    //===================================================================================
    #pragma GCC diagnostic pop
    //===================================================================================
} // namespace vposix
//=======================================================================================


#endif // VPOSIX_CORE_H