#include "vlog_pretty.h"



//=======================================================================================
VLogError::VLogError( const vlog::VLogger &e )
    : VLogError( e._get_cur_entry() )
{}
//=======================================================================================
VLogError::VLogError( const vlog::VLogEntry &e )
    : _entry( e )
{
    _what = vcat( '[', _entry.filename(), ':', _entry.line(), "] ",
                  e.str_type(), " >> ", _entry.message() );
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
