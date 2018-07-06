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
    : _logger  ( make_logger(file, line, func) )
    , _printed ( std::make_shared<bool>(false) )
{
    _preambul = _logger->entry().place_func();
    _logger->do_cat( "ERROR: " );
}
//=======================================================================================
VError::~VError()
{
    if ( *_printed ) return;

    VLogger::execute( *_logger );
    *_printed = true;
}
//=======================================================================================
const char *VError::what() const noexcept
{
    return _what.c_str();
}
//=======================================================================================
