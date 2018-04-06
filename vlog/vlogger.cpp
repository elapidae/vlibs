#include "vlogger.h"

#include <iostream>


using namespace vlog;
using namespace std;


//=======================================================================================
//      VLogger
//=======================================================================================
VLogger::VLogger( VLogEntry::Type type,
                  const std::string &file,
                  int32_t line,
                  const std::string &func )
    : _entry( type, file, line, func )
{
    space();    // Пробелы включены по умолчанию.
}
//=======================================================================================
VLogger::~VLogger()
{
    _entry._set_msg( _cat );
    execute( _entry );
}
//=======================================================================================
VLogEntry VLogger::_get_cur_entry() const
{
    auto res = _entry;
    res._set_msg( _cat );
    return res;
}
//=======================================================================================
void VLogger::_log_to_cout( const VLogEntry &entry )
{
    cout << '[' << entry.filename() << ':' << entry.line() << "] >> "
         << entry.str_type() << ": " << entry.message() << endl;
}
//---------------------------------------------------------------------------------------
void VLogger::_log_to_cerr( const VLogEntry &entry )
{
    cerr << '[' << entry.filename() << ':' << entry.line() << "] >> "
         << entry.str_type() << ": " << entry.message() << endl;
}
//=======================================================================================
static bool need_exit_on_fatal = true;
void VLogger::_do_exit_on_fatal( const VLogEntry &entry )
{
    if ( !need_exit_on_fatal || !entry.is_fatal() ) return;
    exit(1);
}
//=======================================================================================
static vector<VLogger::Executer> executers = []()
{
    vector<VLogger::Executer> res;
    res.push_back( &VLogger::_log_to_cout );
    return res;
}();
//---------------------------------------------------------------------------------------
void VLogger::add_executer( VLogger::Executer e )
{
    executers.push_back( e );
}
//---------------------------------------------------------------------------------------
void VLogger::clear_executers()
{
    executers.clear();
}
//---------------------------------------------------------------------------------------
void VLogger::execute( const VLogEntry &entry )
{
    for ( auto & e: executers )
        e( entry );

    _do_exit_on_fatal( entry );
}
//=======================================================================================
void VLogger::exit_on_fatal(bool on)
{

}
//=======================================================================================
//      VLogger
//=======================================================================================

