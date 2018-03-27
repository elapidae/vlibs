#include "vlog_pretty.h"



//=======================================================================================
VLogError::VLogError(const vlog::VLogger &e )
    : _entry( e._get_cur_entry() )
{
    _what = vcat('[', _entry.filename(), ':', _entry.line(), "] >> ", _entry.message());
}
//=======================================================================================
const char *VLogError::what() const noexcept
{
    return _what.c_str();
}
//=======================================================================================
const vlog::VLogEntry &VLogError::entry() const noexcept
{
    return _entry;
}
//=======================================================================================
