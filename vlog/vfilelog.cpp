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


#include "vfilelog.h"

#include "vtimepoint.h"
#include "vlogger.h"
#include "vdir.h"
#include "verror.h"
#include "vlog.h"


//=======================================================================================
std::string VAbstractFileLog::as_line_with_type( const VLogEntry &entry )
{
    return vcat( entry.timestamp().str_datetime_zzz(), '\t',
                 '[', entry.filename(), ':', entry.line(), "]\t",
                 entry.level_str(), '\t',
                 entry.message(), '\n');
}
//=======================================================================================
std::string VAbstractFileLog::as_line_without_type( const VLogEntry &entry )
{
    return vcat( entry.timestamp().str_datetime_zzz(), '\t',
                 '[', entry.filename(), ':', entry.line(), "]\t",
                 entry.message(), '\n');
}
//=======================================================================================
std::string VAbstractFileLog::start_line()
{
    return vcat( "------------- BEGIN LOGGING ------------- ",
                 VTimePoint::now().str_datetime_zzz(),
                 " -----------------------\n");
}
//=======================================================================================


//=======================================================================================
VFileLog_Leveled::VFileLog_Leveled( const std::string &path,
                                    ulong one_file_size,
                                    uint rotate_files_count )
    : _dir_created( VDir::mkdir_e(path) )
    , _trace  ( path + "/trace.log",   one_file_size, rotate_files_count )
    , _deb    ( path + "/debug.log",   one_file_size, rotate_files_count )
    , _runlog ( path + "/runlog.log",  one_file_size, rotate_files_count )
    , _warn   ( path + "/warning.log", one_file_size, rotate_files_count )
    , _fatal  ( path + "/fatal.log",   one_file_size, rotate_files_count )
{
    if ( _dir_created != VDir::MkDirError::NoError &&
         _dir_created != VDir::MkDirError::AlreadyExists
        )
    {
        throw verror << "Cannot create dir '" << path << "' for leveled log...";
    }

    if ( start_line().empty() ) return;

    auto line = start_line();
    _trace.write  ( line );
    _deb.write    ( line );
    _runlog.write ( line );
    _warn.write   ( line );
    _fatal.write  ( line );
}
//=======================================================================================
void VFileLog_Leveled::execute( const VLogEntry &entry )
{
    auto line = as_line_without_type( entry );
    switch ( entry.level() )
    {
    case VLogEntry::Level::Trace:   _trace.write  ( line ); return;
    case VLogEntry::Level::Dbg:     _deb.write    ( line ); return;
    case VLogEntry::Level::Runlog:  _runlog.write ( line ); return;
    case VLogEntry::Level::Warning: _warn.write   ( line ); return;
    case VLogEntry::Level::Fatal:   _fatal.write  ( line ); return;
    }
    throw verror << "Log level has been changed without refactoring.";
}
//=======================================================================================
void VFileLog_Leveled::register_self()
{
    VLogger::add_executer( [this](const VLogEntry& e) { execute(e); } );
}
//=======================================================================================


//=======================================================================================
VFileLog_Shared::VFileLog_Shared( const std::string &fname,
                                  ulong one_file_size,
                                  uint rotate_files_count )
    : _file( fname, one_file_size, rotate_files_count )
{
    if ( !_file.is_open() )
        throw verror << "Cannot open shared log '" << fname << "'.";

    if ( start_line().empty() ) return;
    _file.write( start_line() );
}
//=======================================================================================
void VFileLog_Shared::execute( const VLogEntry &entry )
{
    _file.write( as_line_with_type(entry) );
}
//=======================================================================================
void VFileLog_Shared::register_self()
{
    VLogger::add_executer( [this](const VLogEntry& e) { execute(e); } );
}
//=======================================================================================
