#ifndef VLOG_H
#define VLOG_H

#include "vlogger.h"

//=======================================================================================
#define VLOGGER2_DEFINED_NOT_USE_WITH_OLD_VLOGGER

//=======================================================================================
#ifdef vlog
#error "Old vlogger turned on."
#endif
//=======================================================================================


//=======================================================================================
//=======================================================================================
#define VTRACE    VLogger( VLogEntry::Type::Trace,   \
                                                    __FILE__, __LINE__, __FUNCTION__ )
#define VDEBUG    VLogger( VLogEntry::Type::Dbg,     \
                                                    __FILE__, __LINE__, __FUNCTION__ )
#define VRUNLOG   VLogger( VLogEntry::Type::Runlog,  \
                                                    __FILE__, __LINE__, __FUNCTION__ )
#define VWARNING  VLogger( VLogEntry::Type::Warning, \
                                                    __FILE__, __LINE__, __FUNCTION__ )
#define VFATAL    VLogger( VLogEntry::Type::Fatal,   \
                                                    __FILE__, __LINE__, __FUNCTION__ )
//=======================================================================================
#define VTRACE_PROXY    VLogger( VLogEntry::Type::Trace,   \
                                                    __FILE__, __LINE__, __FUNCTION__, \
                                                    VLogger::_is_proxy::is_proxy )
#define VDEBUG_PROXY    VLogger( VLogEntry::Type::Dbg,     \
                                                    __FILE__, __LINE__, __FUNCTION__, \
                                                    VLogger::_is_proxy::is_proxy )
#define VRUNLOG_PROXY   VLogger( VLogEntry::Type::Runlog,  \
                                                    __FILE__, __LINE__, __FUNCTION__, \
                                                    VLogger::_is_proxy::is_proxy )
#define VWARNING_PROXY  VLogger( VLogEntry::Type::Warning, \
                                                    __FILE__, __LINE__, __FUNCTION__, \
                                                    VLogger::_is_proxy::is_proxy )
#define VFATAL_PROXY    VLogger( VLogEntry::Type::Fatal,   \
                                                    __FILE__, __LINE__, __FUNCTION__, \
                                                    VLogger::_is_proxy::is_proxy )
//=======================================================================================
//=======================================================================================
/*  2018-05-24 -- Deprecated, было введено для проксирования, сейчас другой подход.
#define VLOG_ENTRY_TRACE(msg)   VLogEntry( VLogEntry::Type::Trace,   \
                                                 __FILE__, __LINE__,__FUNCTION__,(msg))
#define VLOG_ENTRY_DEBUG(msg)   VLogEntry( VLogEntry::Type::Dbg,     \
                                                 __FILE__, __LINE__,__FUNCTION__,(msg))
#define VLOG_ENTRY_RUNLOG(msg)  VLogEntry( VLogEntry::Type::Runlog,  \
                                                 __FILE__, __LINE__,__FUNCTION__,(msg))
#define VLOG_ENTRY_WARNING(msg) VLogEntry( VLogEntry::Type::Warning, \
                                                 __FILE__, __LINE__,__FUNCTION__,(msg))
#define VLOG_ENTRY_FATAL(msg)   VLogEntry( VLogEntry::Type::Fatal,   \
                                                 __FILE__, __LINE__,__FUNCTION__,(msg))
*/
//=======================================================================================




#endif // VLOG_H
