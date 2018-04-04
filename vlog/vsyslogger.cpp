#include "vsyslogger.h"

#include <syslog.h>
#include "vlogger.h"
#include <string.h>


using namespace vlog;


//=======================================================================================
static int to_syslog_type( VLogEntry::Type t )
{
    switch (t)
    {
    case VLogEntry::Type::Trace:    return LOG_DEBUG;
    case VLogEntry::Type::Dbg:      return LOG_INFO;
    case VLogEntry::Type::Runlog:   return LOG_NOTICE;
    case VLogEntry::Type::Warning:  return LOG_WARNING;
    case VLogEntry::Type::Fatal:    return LOG_CRIT;
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
    syslog( to_syslog_type(entry.type()), "%s", entry.message().c_str() );
}
//=======================================================================================



//static bool log_opened = false;

//VSysLogger::VSysLogger( const std::string &ident )
//    : _ident( new char[ident.size() + 1] )
//{
//    if (!log_opened)
//        openlog( ident.c_str(), LOG_CONS|LOG_PID|LOG_NDELAY, LOG_USER );
//    else
//        throw std::runtime_error();

//    log_opened = true;
//}

//VSysLogger::~VSysLogger()
//{
//    closelog();
//}

//void VSysLogger::register_self()
//{
//    VLogger::add_executer( [this](const VLogEntry &e){ this->execute(e); } );
//}

//void VSysLogger::execute( const VLogEntry &entry )
//{
//    syslog( to_syslog_type(entry.type()), "%s", entry.message().c_str() );
//}
