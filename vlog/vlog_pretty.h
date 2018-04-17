#ifndef VLOG_PRETTY_H
#define VLOG_PRETTY_H


#include "vlog.h"

//=======================================================================================
#define vtrace   VTRACE
#define vdebug   VDEBUG
#define vdeb     VDEBUG
#define vrunlog  VRUNLOG
#define vwarning VWARNING
#define vfatal   VFATAL
//=======================================================================================

//=======================================================================================
class VLogError : public std::exception
{
public:
    explicit VLogError( const vlog::VLogger &e );
    explicit VLogError( const vlog::VLogEntry &e );

    virtual const char    * what()  const noexcept override;
    const vlog::VLogEntry & entry() const noexcept;

private:
    std::string     _what;
    vlog::VLogEntry _entry;
};
//=======================================================================================


#endif // VLOG_PRETTY_H
