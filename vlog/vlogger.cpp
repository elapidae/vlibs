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
    _cat.space(); // Пробелы включены по умолчанию.
}
//=======================================================================================
VLogger::~VLogger()
{
    _entry._set_msg( _cat );
    execute( _entry );
}
//=======================================================================================
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
}
//=======================================================================================
//      VLogger
//=======================================================================================

