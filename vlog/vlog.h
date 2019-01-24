/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


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
//  TODO: распросить и посоветоваться, по моему, с прокси глупая идея была.
//  Xотелось всем угодить в итоге угодил в лужу.
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

//=======================================================================================
//  UPD 2019-01-24 -- vlog_pretty deprecated. Let all will be here.
//=======================================================================================
#define vtrace   VTRACE
#define vdebug   VDEBUG
#define vdeb     VDEBUG
#define vrunlog  VRUNLOG
#define vwarning VWARNING
#define vfatal   VFATAL
//=======================================================================================
#define vtrace_proxy   VTRACE_PROXY
#define vdebug_proxy   VDEBUG_PROXY
#define vdeb_proxy     VDEBUG_PROXY
#define vrunlog_proxy  VRUNLOG_PROXY
#define vwarning_proxy VWARNING_PROXY
#define vfatal_proxy   VFATAL_PROXY
//=======================================================================================


#endif // VLOG_H
