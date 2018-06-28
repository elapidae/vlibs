#include "vlogentry.h"

#include <assert.h>
#include "vstring.h"



using namespace std;
//using namespace vlog;


//=======================================================================================
//      VLogEntry
//=======================================================================================
VLogEntry::VLogEntry( Type type, const string &file, int32_t line, const string &func )
    : _timestmap( VTimePoint::now() )
    , _type( type )
    , _file( file )
    , _line( line )
    , _func( func )
{}
//=======================================================================================
VLogEntry::VLogEntry( VLogEntry::Type type,
                      const string &file, int32_t line, const string &func,
                      const string &msg )
    : VLogEntry( type, file, line, func )
{
    _msg = msg;
}
//=======================================================================================
VLogEntry::Type VLogEntry::type() const
{
    return _type;
}
//=======================================================================================
string VLogEntry::str_type() const
{
    switch (_type)
    {
    case Type::Trace:   return "Trc";
    case Type::Dbg:     return "Dbg";
    case Type::Runlog:  return "Run";
    case Type::Warning: return "WRN";
    case Type::Fatal:   return "FTL";
    }
    throw std::logic_error("Unknown type");
}
//=======================================================================================
char VLogEntry::char_type() const
{
    switch ( _type )
    {
    case Type::Trace:    return 'T';
    case Type::Dbg:      return 'D';
    case Type::Runlog:   return 'R';
    case Type::Warning:  return 'W';
    case Type::Fatal:    return 'F';
    }
    throw std::logic_error("Unknown type");
}
//---------------------------------------------------------------------------------------
static VLogEntry::Type deser_char_type( char v )
{
    switch (v)
    {
    case 'T': return VLogEntry::Type::Trace;
    case 'D': return VLogEntry::Type::Dbg;
    case 'R': return VLogEntry::Type::Runlog;
    case 'W': return VLogEntry::Type::Warning;
    case 'F': return VLogEntry::Type::Fatal;
    }
    throw std::logic_error("Unknown type");
}
//=======================================================================================
int32_t VLogEntry::line() const
{
    return _line;
}
//=======================================================================================
string VLogEntry::funcname() const
{
    return _func;
}
//=======================================================================================
string VLogEntry::filename() const
{
    assert( !_file.empty() );
    return VString(_file).split('/').back();
}
//=======================================================================================
string VLogEntry::filepath() const
{
    return _file;
}
//=======================================================================================
string VLogEntry::message() const
{
    return _msg;
}
//=======================================================================================
VTimePoint VLogEntry::timestamp() const
{
    return _timestmap;
}
//=======================================================================================
bool VLogEntry::is_fatal() const
{
    return type() == Type::Fatal;
}
//=======================================================================================
//=======================================================================================
VLogEntry VLogEntry::deserialize( VBufferForwardReader *reader )
{
    auto type = deser_char_type( reader->take_ch() );
    auto file = reader->take_dword_string_LE();
    auto line = reader->take_i32_LE();
    auto func = reader->take_dword_string_LE();
    auto nts  = reader->take_i64_LE();
    auto msg  = reader->take_dword_string_LE();

    VLogEntry res( type, file, line, func );
    res._timestmap = VTimePoint( std::chrono::nanoseconds(nts) );
    res._msg = msg;

    return res;
}
//=======================================================================================
void VLogEntry::serialize( VString *dst ) const
{
    int64_t nts = _timestmap.nanoseconds().count();

    dst->append_LE( char_type() );
    dst->append_dword_string_LE( _file );
    dst->append_LE( _line );
    dst->append_dword_string_LE( _func );
    dst->append_LE( nts );
    dst->append_dword_string_LE( message() );
}
//=======================================================================================
//      VLogEntry
//=======================================================================================
