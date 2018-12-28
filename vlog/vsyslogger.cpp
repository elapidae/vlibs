#include "vsyslogger.h"

#include <syslog.h>
#include "vlogger.h"
#include <string.h>


//=======================================================================================
static int to_syslog_type( VLogEntry::Level t )
{
    switch (t)
    {
    case VLogEntry::Level::Trace:    return LOG_DEBUG;
    case VLogEntry::Level::Dbg:      return LOG_INFO;
    case VLogEntry::Level::Runlog:   return LOG_NOTICE;
    case VLogEntry::Level::Warning:  return LOG_WARNING;
    case VLogEntry::Level::Fatal:    return LOG_CRIT;
    }
    throw std::logic_error("Unknown entry type.");
}
//=======================================================================================
void VSysLogger::open( const std::string &ident )
{
    static std::unique_ptr<char[]> _ident;
    _ident.reset( new char[ident.size() + 1] );
    strcpy( _ident.get(), ident.c_str() );

    openlog( _ident.get(), LOG_CONS|LOG_PID|LOG_NDELAY, LOG_USER );
}
//=======================================================================================
void VSysLogger::register_self()
{
    VLogger::add_executer( execute );
}
//=======================================================================================
void VSysLogger::execute( const VLogEntry &entry )
{
    syslog( to_syslog_type(entry.level()), "%s", entry.message().c_str() );
}
//=======================================================================================
