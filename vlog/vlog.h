#ifndef VLOG_H
#define VLOG_H

#include "vlogger.h"



//=======================================================================================
#define VLOG_FUNCTION __PRETTY_FUNCTION__

#define VTRACE          VLogger( VLogEntry::Level::Trace,           \
                                 __FILE__, __LINE__, VLOG_FUNCTION, \
                                 VLogger::_is_proxy::no_proxy )

#define VDEBUG          VLogger( VLogEntry::Level::Dbg,             \
                                 __FILE__, __LINE__, VLOG_FUNCTION, \
                                 VLogger::_is_proxy::no_proxy )

#define VRUNLOG         VLogger( VLogEntry::Level::Runlog,          \
                                 __FILE__, __LINE__, VLOG_FUNCTION, \
                                 VLogger::_is_proxy::no_proxy )

#define VWARNING        VLogger( VLogEntry::Level::Warning,         \
                                 __FILE__, __LINE__, VLOG_FUNCTION, \
                                 VLogger::_is_proxy::no_proxy )

#define VFATAL          VLogger( VLogEntry::Level::Fatal,           \
                                 __FILE__, __LINE__, VLOG_FUNCTION, \
                                 VLogger::_is_proxy::no_proxy )

//=======================================================================================

#define VTRACE_PROXY    VLogger( VLogEntry::Level::Trace,           \
                                 __FILE__, __LINE__, VLOG_FUNCTION, \
                                 VLogger::_is_proxy::is_proxy )

#define VDEBUG_PROXY    VLogger( VLogEntry::Level::Dbg,             \
                                 __FILE__, __LINE__, VLOG_FUNCTION, \
                                 VLogger::_is_proxy::is_proxy )

#define VRUNLOG_PROXY   VLogger( VLogEntry::Level::Runlog,          \
                                 __FILE__, __LINE__, VLOG_FUNCTION, \
                                 VLogger::_is_proxy::is_proxy )

#define VWARNING_PROXY  VLogger( VLogEntry::Level::Warning,         \
                                 __FILE__, __LINE__, VLOG_FUNCTION, \
                                 VLogger::_is_proxy::is_proxy )

#define VFATAL_PROXY    VLogger( VLogEntry::Level::Fatal,           \
                                 __FILE__, __LINE__, VLOG_FUNCTION, \
                                 VLogger::_is_proxy::is_proxy )

//=======================================================================================


#endif // VLOG_H
