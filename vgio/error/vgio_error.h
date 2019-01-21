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


#ifndef VIO_ERROR_H
#define VIO_ERROR_H

#include <memory>
#include <stdint.h>
#include <stdexcept>

//=======================================================================================
/// 02-08-2018          by Elapidae
///
/// vgio::Error -- обертка к GError, используется библиотеками G* для сообщения об
/// ошибках, передается в виде указателя.
///
/// Автор старается формировать методы так, чтобы можно было узнать об ошибке явно, или,
/// если ошибка возникла, а вызывающий код ее не собирается ее принимать, то бросалось
/// исключение vgio::Exception.
///
//=======================================================================================


//=======================================================================================
typedef struct _GError GError;
//=======================================================================================


//=======================================================================================
namespace vgio
{
    //===================================================================================
    namespace _impl { class error_proxy; }
    //===================================================================================

    //===================================================================================
    class Exception : public std::runtime_error
    {
    public:
        Exception( const std::string &msg );
    };
    //===================================================================================


    //===================================================================================
    //      Error
    //===================================================================================
    class Error final
    {
    public:
        Error();

        bool has() const;

        std::string message()   const;
        uint32_t    domain()    const;
        int         code()      const;

        std::string debug_msg() const; // сообщение, составленное из domain, code, msg.

        ~Error() = default;

    private:
        std::shared_ptr<GError> p;
        Error( GError *err );

        friend class _impl::error_proxy;
        void _set( GError *err );
        static std::string _deb_msg( GError *err );
    };
    //===================================================================================
    //      Error
    //===================================================================================



    //===================================================================================
    //      IMPLEMENTATION
    //===================================================================================
    namespace _impl
    {
        //===============================================================================
        //  Пользователю этот класс не должен быть интересен.
        // Используется для того, чтобы контролировать ошибку в G вызовах, когда просят
        // передавать GError**. Если пользователь не передает приемную ошибку, бросается
        // исключение.
        //      Использовать, например, так:
        //          void some_call_with_error( ..., Error *err )
        //          {
        //              _error_proxy err_proxy( err );
        //              g_some_call_with_error( lots_of_params.. , err_proxy );
        //              // Если была ошибка и ее принимают, Error будет правильно
        //              // установлена, иначе будет исключение Exception( err->message ).
        //          }
        //
        class error_proxy final
        {
        public:
            explicit error_proxy( Error *err );
            ~error_proxy();

            operator GError** ();

            void flush();

        private:
            Error *_target;
            GError *_gerror = nullptr;
            bool _flushed = false;

            error_proxy ( const error_proxy & ) = delete;
            error_proxy & operator = ( const error_proxy & ) = delete;
        }; // class _error_proxy
        //===============================================================================
    } // namespace _impl
    //===================================================================================
} // vio namespace
//=======================================================================================


#endif // VIO_ERROR_H
