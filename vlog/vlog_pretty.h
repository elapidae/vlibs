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
#define vtrace_proxy   VTRACE_PROXY
#define vdebug_proxy   VDEBUG_PROXY
#define vdeb_proxy     VDEBUG_PROXY
#define vrunlog_proxy  VRUNLOG_PROXY
#define vwarning_proxy VWARNING_PROXY
#define vfatal_proxy   VFATAL_PROXY
//=======================================================================================

//=======================================================================================
class VLogError : public std::exception
{
public:
    explicit VLogError( const VLogger   &logger );
    //explicit VLogError( const VLogEntry &entry  );

    virtual const char    * what()  const noexcept override;
    const VLogEntry       & entry() const noexcept;

private:
    std::string _what;
    VLogEntry   _entry;
};
//=======================================================================================


#endif // VLOG_PRETTY_H
