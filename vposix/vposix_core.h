/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


#ifndef VPOSIX_CORE_H
#define VPOSIX_CORE_H

#include <type_traits>
#include <errno.h>
#include <stdexcept>
#include <string>
#include "verror.h"
#include "vcompiler.h"

//=======================================================================================
//
//  class Core
//
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
    // Общий флаг для отладки. По мере обкатывания модулей, можно будет переводить их
    // на свой *_trace();
    constexpr bool do_trace() { return true; }

    //===================================================================================
    class Core
    {
    public:
        //===============================================================================
        //  Ради одного вызова разводить файлы не хочется, пусть здесь поживет.
        static pid_t pid();
        //===============================================================================

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
        template< typename Fn, typename ... Args >
        static auto linux_call( Fn fn, const std::string& src, Args ... args )
                                                            -> decltype( fn(args...) );
        //===============================================================================
        //  Не бросает исключение, возвращает как есть. Дальше ковыряйтесь с errno сами.
        //
        template< typename Fn, typename ... Args >
        static auto linux_call_or_err( Fn fn, Args ... args ) -> decltype( fn(args...) );
        //===============================================================================
    }; // Core
    //===================================================================================

    //===================================================================================
    class Errno
    {
    public:
        Errno();

        int has()  const;
        int code() const;
        std::string str() const;

        // Вызввает исключение, если ошибка есть.
        V_NORETURN
        void throw_verror( const std::string& event ) const;


        bool again_or_wouldblock() const;               //  EAGAIN | EWOULDBLOCK
        bool resource_unavailable_try_again() const;    // as c++11.

        bool operation_in_progress() const;             //  EINPROGRESS
        bool connection_already_in_progress() const;    //  EALREADY

    private:
        int _err;
    }; // Errno
    //===================================================================================


    //===================================================================================
    //      IMPLEMENTATION
    //===================================================================================
    #pragma GCC diagnostic push
    #if (V_NOEXCEPT_SIGNATURE_WARNING_ENABLED)
        #pragma GCC diagnostic ignored "-Wnoexcept-type"
    #endif
    //===================================================================================
    template<typename Fn, typename ... Args>
    auto Core::linux_call_or_err( Fn fn, Args ... args ) -> decltype( fn(args...) )
    {
        decltype(fn(args...)) res;

        do
        {
            res = fn( args... );
        }
        while ( res == -1 && errno == EINTR );

        return res;
    }
    //===================================================================================
    template< typename Fn, typename ... Args >
    auto Core::linux_call( Fn fn, const std::string& src, Args ... args )
                                                               -> decltype( fn(args...) )
    {
        auto res = linux_call_or_err( std::forward<Fn>(fn),
                                      std::forward<Args>(args)... );

        if ( res != -1 ) return res;

        Errno().throw_verror( src );
    }
    //===================================================================================
    #pragma GCC diagnostic pop
    //===================================================================================
} // namespace vposix
//=======================================================================================


#endif // VPOSIX_CORE_H
