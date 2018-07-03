#include "verror.h"

#include "vlog_pretty.h"


//=======================================================================================
static
std::shared_ptr<VLogger> make_logger( const char *file, int line, const char *func )
{
    return std::make_shared<VLogger>( VLogEntry::Level::Fatal,
                                      file, line, func,
                                      VLogger::_is_proxy::is_proxy );
}
//=======================================================================================


//=======================================================================================
VError::VError( const char *file, int line, const char *func )
    : _logger( make_logger(file, line, func) )
{
    _preambul = _logger->entry().place_func() + " ERROR: ";
}
//=======================================================================================
VError::~VError()
{
    // По удалению не получится, т.к. реализация делает копию и потом terminate().
    VLogger::execute( *_logger );
}
//=======================================================================================
const char *VError::what() const noexcept
{
    return _what.c_str();
}
//=======================================================================================
