#ifndef VERROR_H
#define VERROR_H

#include <memory>
#include "vlog.h"

//=======================================================================================
/*  UPD 2018-07-03
 *  VError -- класс для бросания исключений в непредвиденных, неисследованных ситуациях.
 *
 *  Задача класса -- сформировать сообщение исключения с точкой вхождения в исходниках.
 *
 *  В задачу класса не входит пробрасывать исключения на обработку, не следует специально
 *  перехватывать его, основное предназначение -- сообщить о проблемном участке кода.
 *  Можно в main() перехватить, чтобы просто выйти "return 200;", тогда появляется
 *  эффект, что сообщение выводится два раза.
**/
//=======================================================================================


//=======================================================================================
class VError : public std::exception, public _vcat_iface<VError>
{
public:
    explicit VError( const char *file, int line, const char *fn );
    virtual ~VError() override;

    virtual const char * what() const noexcept override;

private:
    std::shared_ptr<VLogger> _logger;
    std::string _preambul;
    std::string _what;
    std::shared_ptr<bool> _printed;

    friend class _vcat_iface<VError>;
    template<typename T> void do_cat( T&& val )
    {
        if ( *_printed ) VWARNING << "Do not cat message after throw.";

        _logger->do_cat( std::forward<T>(val) );
        auto entry = _logger->entry();

        _what = _preambul + entry.message() + '\n';
    }
};
//---------------------------------------------------------------------------------------
#define verror VError( __FILE__, __LINE__, VLOG_FUNCTION )
//=======================================================================================


#endif // VERROR_H
