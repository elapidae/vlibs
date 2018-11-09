#ifndef VPOSIX_CORE_H
#define VPOSIX_CORE_H

#include <type_traits>
#include <errno.h>
#include <stdexcept>
#include "vposix_errno.h"

namespace vposix
{
    //===================================================================================

    constexpr bool do_trace() { return true; }

    //===================================================================================
    class Core
    {
    public:

    };
    //===================================================================================


    //===================================================================================
    //  Кидает исключение в случае ошибки, иначе возвращает результат функции Fn.
    //  Вызывается примерно так: auto fd = vposix::linux_call<int>(::open, O_RDWR);
    template< typename RetType, typename Fn, typename ... Args >
    RetType linux_call( Fn fn, Args ... args );
    //===================================================================================
    //  linux_call_eintr сделан по образу Qt макроса EINTR_LOOP, который гоняет в цикле
    //  вызов до тех пор, пока либо не будет успешного вызова либо пока ошибка будет
    //  EINTR, означающая, что вызов функции был сброшен из-за прерывания.
    //  Linux такая linux.
    template< typename RetType, typename Fn, typename ... Ts >
    RetType linux_call_eintr( Fn fn, Ts ... ts );
    //===================================================================================
    template< typename RetType, typename Fn, typename ... Ts >
    RetType linux_call_eintr_or_errno( bool *ok, Fn fn, Ts ... ts );
    //===================================================================================


    //===================================================================================
    //      IMPLEMENTATION
    //===================================================================================
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wnoexcept-type"
    template< typename RetType, typename Fn, typename ... Args >
    RetType linux_call( Fn fn, Args ... args )
    {
        auto res = fn( args... );
        static_assert( std::is_same<decltype(res),RetType>::value, "" );

        if ( res != -1 ) return res;

        throw std::runtime_error( Errno::str_error(errno) );
    }
    //===================================================================================
    template< typename RetType, typename Fn, typename ... Ts >
    RetType linux_call_eintr( Fn fn, Ts ... ts )
    {
        static_assert ( std::is_same<decltype(fn(ts...)),RetType>::value,
                        "eintr_call: ret type must be same as function return." );

        RetType res;
        do {
            res = fn( ts... );
        } while ( res == -1 && errno == EINTR );

        if ( res != -1 ) return res;

        throw std::runtime_error( Errno::str_error(errno) );
    }
    //===================================================================================
    template< typename RetType, typename Fn, typename ... Ts >
    RetType linux_call_eintr_or_errno( bool *ok, Fn fn, Ts ... ts )
    {
        static_assert ( std::is_same<decltype(fn(ts...)),RetType>::value,
                        "eintr_call: ret type must be same as function return." );
        RetType res;
        do {
            res = fn( ts... );
        } while ( res == -1 && errno == EINTR );

        *ok = res != -1;
        return res == -1 ? errno : res;
    }
    #pragma GCC diagnostic pop
    //===================================================================================
} // namespace vposix
//=======================================================================================


#endif // VPOSIX_CORE_H
