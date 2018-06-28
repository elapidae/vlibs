#include "vlog_pretty.h"



//=======================================================================================
VLogError::VLogError( const VLogger &logger )
    : _entry( logger )
{
    _what = vcat( '[', _entry.filename(), ':', _entry.line(), "] ",
                  _entry.str_type(), " >> ", _entry.message() );
}
//=======================================================================================
const char *VLogError::what() const noexcept
{
    return _what.c_str();
}
//=======================================================================================
const VLogEntry &VLogError::entry() const noexcept
{
    return _entry;
}
//=======================================================================================
