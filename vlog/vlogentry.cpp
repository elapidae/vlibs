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


#include "vlogentry.h"

#include "vcat.h"
#include <assert.h>
#include <algorithm>
#include <stdexcept>

using namespace std;



//=======================================================================================
//      VLogEntry
//=======================================================================================
VLogEntry::VLogEntry( VLogEntry::Level  level,
                      const VTimePoint& stamp,
                      const char*       file,
                      int               line,
                      const char*       func,
                      const string&     msg )
    : _level( level )
    , _stamp( stamp )
    , _file ( file  )
    , _line ( line  )
    , _func ( func  )
    , _msg  ( msg   )
{}
//=======================================================================================
const string &VLogEntry::message() const
{
    return _msg;
}
//=======================================================================================
VTimePoint VLogEntry::timestamp() const
{
    return _stamp;
}
//=======================================================================================
//  Отделяем из пути к файлу его имя: всё, что находится после '/'.
std::string VLogEntry::filename() const
{
    return _extract_filename( filepath() );
}
//=======================================================================================
std::string VLogEntry::_extract_filename( const string &fpath )
{
    auto slash_it = std::find( fpath.rbegin(), fpath.rend(), '/' );

    return { slash_it.base(), fpath.end() };
}
//=======================================================================================
const char *VLogEntry::filepath() const
{
    return _file;
}
//=======================================================================================
int32_t VLogEntry::line() const
{
    return _line;
}
//=======================================================================================
const char *VLogEntry::function() const
{
    return _func;
}
//=======================================================================================
VLogEntry::Level VLogEntry::level() const
{
    return _level;
}
//=======================================================================================
string VLogEntry::level_str() const
{
    switch ( _level )
    {
    case Level::Trace:   return "TRC";
    case Level::Dbg:     return "DBG";
    case Level::Runlog:  return "RUN";
    case Level::Warning: return "WRN";
    case Level::Fatal:   return "FTL";
    }
    throw std::logic_error("Unknown type");
}
//=======================================================================================
char VLogEntry::level_char() const
{
    switch ( _level )
    {
    case Level::Trace:    return 'T';
    case Level::Dbg:      return 'D';
    case Level::Runlog:   return 'R';
    case Level::Warning:  return 'W';
    case Level::Fatal:    return 'F';
    }
    throw std::logic_error("Unknown type");
}
//=======================================================================================
VLogEntry::Level VLogEntry::level_from_char( char ch )
{
    switch ( ch )
    {
    case 'T': return VLogEntry::Level::Trace;
    case 'D': return VLogEntry::Level::Dbg;
    case 'R': return VLogEntry::Level::Runlog;
    case 'W': return VLogEntry::Level::Warning;
    case 'F': return VLogEntry::Level::Fatal;
    }
    throw std::logic_error("Unknown type");
}
//=======================================================================================
bool VLogEntry::is_trace() const
{
    return level() == Level::Trace;
}
//=======================================================================================
bool VLogEntry::is_debug() const
{
    return level() == Level::Dbg;
}
//=======================================================================================
bool VLogEntry::is_runlog() const
{
    return level() == Level::Runlog;
}
//=======================================================================================
bool VLogEntry::is_warning() const
{
    return level() == Level::Warning;
}
//=======================================================================================
bool VLogEntry::is_fatal() const
{
    return level() == Level::Fatal;
}
//=======================================================================================
string VLogEntry::place() const
{
    return vcat( '[', filename(), ':', line(), ']' );
}
//=======================================================================================
string VLogEntry::place_func() const
{
    return vcat( '[', filename(), ':', line(), "=>", function(), ']' );
}
//=======================================================================================
const VLogEntry::Record VLogEntry::record() const
{
    return this;
}
//=======================================================================================
//  Будет забрано отсюда ближе к реализации UDP.
//=======================================================================================
//VLogEntry VLogEntry::deserialize( VBufferForwardReader *reader )
//{
//    auto type = deser_char_type( reader->take_ch() );
//    auto file = reader->take_dword_string_LE();
//    auto line = reader->take_i32_LE();
//    auto func = reader->take_dword_string_LE();
//    auto nts  = reader->take_i64_LE();
//    auto msg  = reader->take_dword_string_LE();

//    VLogEntry res( type, file, line, func );
//    res._timestmap = VTimePoint( std::chrono::nanoseconds(nts) );
//    res._msg = msg;

//    return res;
//}
//=======================================================================================
//void VLogEntry::serialize( VString *dst ) const
//{
//    int64_t nts = _timestmap.nanoseconds().count();

//    dst->append_LE( level_char() );
//    dst->append_dword_string_LE( _file );
//    dst->append_LE( _line );
//    dst->append_dword_string_LE( _func );
//    dst->append_LE( nts );
//    dst->append_dword_string_LE( message() );
//}
//=======================================================================================
//VString VLogEntry::serialize() const
//{
//    VString res;
//    serialize( &res );
//    return res;
//}
//=======================================================================================
//      VLogEntry
//=======================================================================================



//=======================================================================================
//      VLogEntry::Record
//=======================================================================================
VLogEntry::Record::Record(const VLogEntry *entry)
    : _entry(entry)
{}
//=======================================================================================
string VLogEntry::Record::place_level_msg() const
{
    return _entry->place() + "\t>> " + _entry->level_str() + ": " + _entry->message();
}
//=======================================================================================
string VLogEntry::Record::time_place_msg_nl() const
{
    return _entry->timestamp().str_datetime_zzz() + '\t' +
           _entry->place()   + '\t' +
           _entry->message() + '\n';
}
//=======================================================================================
string VLogEntry::Record::time_place_level_msg_nl() const
{
    return _entry->timestamp().str_datetime_zzz() + '\t' +
           _entry->place()     + '\t' +
           _entry->level_str() + '\t' +
           _entry->message()   + '\n';
}
//=======================================================================================
string VLogEntry::Record::begin_line_time_nl()
{
    return vcat( "============= BEGIN LOGGING ============= ",
                 VTimePoint::now().str_datetime_zzz(),
                 " =======================\n");
}
//=======================================================================================
//      VLogEntry::Record
//=======================================================================================
