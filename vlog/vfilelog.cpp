#include "vfilelog.h"

#include "vtimepoint.h"
#include "vlogger.h"
#include "vdir.h"
#include "verror.h"
#include "vlog_pretty.h"


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
    : _dir_created( VDir::mkdir(path) )
    , _trace  ( path + "/trace.log",   one_file_size, rotate_files_count )
    , _deb    ( path + "/debug.log",   one_file_size, rotate_files_count )
    , _runlog ( path + "/runlog.log",  one_file_size, rotate_files_count )
    , _warn   ( path + "/warning.log", one_file_size, rotate_files_count )
    , _fatal  ( path + "/fatal.log",   one_file_size, rotate_files_count )
{
    if ( !_dir_created )
        throw verror << "Cannot create dir '" << path << "' for leveled log...";

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
    VLogger::add_executer( [this](const VLogEntry &e) { execute(e); });
}
//=======================================================================================
#ifdef VGIO_KEYFILE_INCLUDED_BYEL
VFileLog_Leveled::Ptr VFileLog_Leveled::load_from_keyfile( const vgio::KeyFile &kf,
                                                           const std::string &group )
{
    if ( !kf.safe_bool(group, "need_leveled_log",false) ) return {};

    auto path   = kf.get_string( group, "leveled_log_path"          );
    auto fsize  = kf.get_int(    group, "leveled_log_one_file_size" );
    auto scount = kf.get_int(    group, "leveled_log_files_count"   );

    if ( path.empty() || scount < 0 || fsize <= 0 ) {
        vwarning << "Leveled-keyfile-values: "
                    "( path.empty() || scount < 0 || fsize <= 0 )";
        return {};
    }

    return std::make_shared<VFileLog_Leveled>( path, fsize, scount );
}
//---------------------------------------------------------------------------------------
void VFileLog_Leveled::save_to_keyfile( vgio::KeyFile *kf,
                                        const std::string &group,
                                        bool need_log,
                                        const std::string &path,
                                        int file_size,
                                        int rotates_count )
{
    kf->set_bool    ( group, "need_leveled_log",            need_log        );
    kf->set_string  ( group, "leveled_log_path",            path            );
    kf->set_int     ( group, "leveled_log_one_file_size",   file_size       );
    kf->set_int     ( group, "leveled_log_files_count",     rotates_count   );
}
#endif
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
    auto e = std::bind( &VFileLog_Shared::execute, this, std::placeholders::_1 );
    VLogger::add_executer( e );
}
//=======================================================================================
