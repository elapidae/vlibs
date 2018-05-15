#ifndef NERROR_H
#define NERROR_H

#include <memory>


typedef struct _GError GError;


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

    std::string message()   const;
    uint32_t    domain()    const;
    int         code()      const;

    std::string debug_msg() const; // сообщение, составленное из domain, code, message.


private:
    std::shared_ptr<GError> p;
    NError( GError *err );

    friend class _n_error_proxy;
    void _set( GError *err );
    static std::string _deb_msg( GError *err );
};
//=======================================================================================



//=======================================================================================
//  Пользователю этот класс не должен быть интересен.
// Используется для того, чтобы контролировать ошибку в G вызовах, когда просят
// передавать GError**. Если пользователь не передает приемную ошибку, бросается
// исключение.
//      Использовать, например, так:
//          void some_call_with_error( ..., NError *err )
//          {
//              _n_error_proxy err_proxy( err );
//              g_some_call_with_error( lots_of_params.. , err_proxy );
//              // Если была ошибка и ее принимают, NError будет правильно установлена,
//              // иначе будет исключение NException( err->message ).
//          }
//
class _n_error_proxy final
{
public:
    explicit _n_error_proxy( NError *err );
    ~_n_error_proxy();

    operator GError** ();

private:
    NError *_target;
    GError *_gerror = nullptr;

    _n_error_proxy ( const _n_error_proxy & ) = delete;
    _n_error_proxy & operator = ( const _n_error_proxy & ) = delete;
};
//=======================================================================================




#endif // NERROR_H
