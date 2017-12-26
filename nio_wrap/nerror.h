#ifndef NERROR_H
#define NERROR_H

#include <stdexcept>
#include <glib.h>
#include <memory>

//=======================================================================================
class NException : public std::runtime_error
{
public:
    NException( const std::string &msg );
};
//=======================================================================================
//=======================================================================================
class NError final
{
public:
    NError();

    bool has() const;

    std::string message() const;
    uint32_t    domain()  const;
    int         code()    const;

    std::string deb_msg() const;

private:
    std::shared_ptr<GError> p;
    NError( GError *err );

//    friend class NFile;
//    friend class NInputStream;
//    friend class NOutputStream;
//    friend class NKeyFile;
    friend class _NErrorProxy;
    void _set( GError *err );
    static std::string _deb_msg( GError *err );
};
//=======================================================================================
//  Пользователю этот класс не должен быть интересен.
// Используется для того, чтобы контролировать ошибку в G вызовах, когда просят
// передавать GError**. Если пользователь не передает приемную ошибку, бросается
// исключение.
//      Использовать, например, так:
//          void some_call_with_error( ..., NError *err )
//          {
//              _NErrorProxy err_proxy( err );
//              g_some_call_with_error( lots_of_params.. , err_proxy.use() );
//              // Если была ошибка и ее принимают, NError будет правильно установлена,
//              // иначе будет исключение NException( err->message ).
//          }
//
class _NErrorProxy final
{
public:
    explicit _NErrorProxy( NError *err );
    ~_NErrorProxy();

    void throw_if_need();

    operator GError** ();

private:
    NError *_target;
    GError *_gerror = nullptr;

    _NErrorProxy ( const _NErrorProxy & ) = delete;
    _NErrorProxy & operator = ( const _NErrorProxy & ) = delete;
};
//=======================================================================================




#endif // NERROR_H
