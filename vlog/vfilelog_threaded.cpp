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


#include "vfilelog_threaded.h"

#include "vlogger.h"

//using namespace vlog;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"


//=======================================================================================
VGroupFileLog_Threaded::VGroupFileLog_Threaded( const std::string &path,
                                                long one_file_size,
                                                int rotate_files_count )
{
    _thread.finvoke( [=]()
    {
        _log.reset( new VFileLog_Leveled(path, one_file_size, rotate_files_count) );
    });
}
//=======================================================================================
VGroupFileLog_Threaded::~VGroupFileLog_Threaded()
{
    _thread.finvoke( [this](){ _log.reset(); } );
}
//=======================================================================================
void VGroupFileLog_Threaded::execute( const VLogEntry &entry )
{
    _thread.finvoke( [=](){ if (_log) _log->execute(entry); } );
}
//=======================================================================================
void VGroupFileLog_Threaded::register_self()
{
    VLogger::add_executer( [this](const VLogEntry &e){ execute(e); } );
}
//=======================================================================================
int VGroupFileLog_Threaded::queued_entries() const
{
    return _thread.queue_size();
}
//=======================================================================================


//=======================================================================================
VCommonFileLog_Threaded::VCommonFileLog_Threaded( const std::string &fname,
                                            long one_file_size,
                                            int rotate_files_count )
{
    _thread.finvoke( [=]()
    {
        _log.reset( new VFileLog_Shared(fname, one_file_size, rotate_files_count) );
    });
}
//=======================================================================================
VCommonFileLog_Threaded::~VCommonFileLog_Threaded()
{
    _thread.finvoke( [this](){ _log.reset(); } );
}
//=======================================================================================
void VCommonFileLog_Threaded::execute( const VLogEntry &entry )
{
    _thread.finvoke( [=](){ if (_log) _log->execute(entry); } );
}
//=======================================================================================
void VCommonFileLog_Threaded::register_self()
{
    VLogger::add_executer( [this](const VLogEntry &e){ execute(e); } );
}
//=======================================================================================
int VCommonFileLog_Threaded::queued_entries() const
{
    return _thread.queue_size();
}
//=======================================================================================



#pragma GCC diagnostic pop
