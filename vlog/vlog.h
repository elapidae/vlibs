#ifndef VLOG_H
#define VLOG_H

#include "vlogger.h"

//=======================================================================================
#define VLOGGER2_DEFINED_NOT_USE_WITH_OLD_VLOGGER

#ifdef vlog
#error "Old vlogger turned on."
#endif
//=======================================================================================


//=======================================================================================
//=======================================================================================
#define VTRACE   vlog::VLogger( vlog::VLogEntry::Type::Trace,   \
                                                    __FILE__, __LINE__, __FUNCTION__ )
#define VDEBUG   vlog::VLogger( vlog::VLogEntry::Type::Dbg,     \
                                                    __FILE__, __LINE__, __FUNCTION__ )
#define VRUNLOG  vlog::VLogger( vlog::VLogEntry::Type::Runlog,  \
                                                    __FILE__, __LINE__, __FUNCTION__ )
#define VWARNING vlog::VLogger( vlog::VLogEntry::Type::Warning, \
                                                    __FILE__, __LINE__, __FUNCTION__ )
#define VFATAL   vlog::VLogger( vlog::VLogEntry::Type::Fatal,   \
                                                    __FILE__, __LINE__, __FUNCTION__ )
//=======================================================================================
//=======================================================================================
#define VLOG_ENTRY_TRACE(msg)   vlog::VLogEntry( vlog::VLogEntry::Type::Trace,   \
                                                 __FILE__, __LINE__, __FUNCTION__, (msg))
#define VLOG_ENTRY_DEBUG(msg)   vlog::VLogEntry( vlog::VLogEntry::Type::Dbg,     \
                                                 __FILE__, __LINE__, __FUNCTION__, (msg))
#define VLOG_ENTRY_RUNLOG(msg)  vlog::VLogEntry( vlog::VLogEntry::Type::Runlog,  \
                                                 __FILE__, __LINE__, __FUNCTION__, (msg))
#define VLOG_ENTRY_WARNING(msg) vlog::VLogEntry( vlog::VLogEntry::Type::Warning, \
                                                 __FILE__, __LINE__, __FUNCTION__, (msg))
#define VLOG_ENTRY_FATAL(msg)   vlog::VLogEntry( vlog::VLogEntry::Type::Fatal,   \
                                                 __FILE__, __LINE__, __FUNCTION__, (msg))
//=======================================================================================




#endif // VLOG_H
