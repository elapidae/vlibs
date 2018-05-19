#include "vfilelog.h"

#include "vtimepoint.h"
#include "vlogger.h"
#include "vdir.h"

using namespace vlog;


//=======================================================================================
std::string VFileLog::as_line_with_type( const VLogEntry &entry )
{
    return vcat( entry.timestamp().str_datetime_zzz(), '\t',
                 '[', entry.filename(), ':', entry.line(), "]\t",
                 entry.str_type(), '\t',
                 entry.message(), '\n');
}
//=======================================================================================
std::string VFileLog::as_line_without_type( const VLogEntry &entry )
{
    return vcat( entry.timestamp().str_datetime_zzz(), '\t',
                 '[', entry.filename(), ':', entry.line(), "]\t",
                 entry.message(), '\n');
}
//=======================================================================================
std::string VFileLog::start_line()
{
    return vcat( "------------- BEGIN LOGGING ------------- ",
                 VTimePoint::now().str_datetime_zzz(),
                 " -----------------------\n");
}
//=======================================================================================

//=======================================================================================
vlog::VGroupFileLog::VGroupFileLog( const std::string &path,
                                    long one_file_size,
                                    int rotate_files_count )
    : _dir_created( VDir::mkdir(path) )
    , _trace  ( vcat(path, "/trace.log"),   one_file_size, rotate_files_count )
    , _deb    ( vcat(path, "/debug.log"),   one_file_size, rotate_files_count )
    , _runlog ( vcat(path, "/runlog.log"),  one_file_size, rotate_files_count )
    , _warn   ( vcat(path, "/warning.log"), one_file_size, rotate_files_count )
    , _fatal  ( vcat(path, "/fatal.log"),   one_file_size, rotate_files_count )
{
    if (start_line().empty()) return;

    auto line = start_line();
    _trace.write  ( line );
    _deb.write    ( line );
    _runlog.write ( line );
    _warn.write   ( line );
    _fatal.write  ( line );
}
//=======================================================================================
void VGroupFileLog::execute( const vlog::VLogEntry &entry )
{
    auto line = as_line_without_type( entry );
    switch ( entry.type() )
    {
    case VLogEntry::Type::Trace:   _trace.write  ( line ); break;
    case VLogEntry::Type::Dbg:     _deb.write    ( line ); break;
    case VLogEntry::Type::Runlog:  _runlog.write ( line ); break;
    case VLogEntry::Type::Warning: _warn.write   ( line ); break;
    case VLogEntry::Type::Fatal:   _fatal.write  ( line ); break;
    }
}
//=======================================================================================
void VGroupFileLog::register_self()
{
    VLogger::add_executer( [this](const VLogEntry &e) { execute(e); });
}
//=======================================================================================
VCommonFileLog::VCommonFileLog( const std::string &fname,
                          long one_file_size,
                          int rotate_files_count )
    : _file( fname, one_file_size, rotate_files_count )
{
    if (start_line().empty()) return;
    _file.write( start_line() );
}
//=======================================================================================
void VCommonFileLog::execute( const VLogEntry &entry )
{
    _file.write( as_line_with_type(entry) );
}
//=======================================================================================
void VCommonFileLog::register_self()
{
    VLogger::add_executer( [this](const VLogEntry &e) { execute(e); });
}
//=======================================================================================
