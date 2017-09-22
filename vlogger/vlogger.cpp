#include "vlogger.h"

#include <string>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <unordered_map>

#include "json11.h"
#include "vdatetime.h"


using namespace std;
using namespace chrono;
using namespace json11;


//=======================================================================================
//          VLOG EXCEPTION
//=======================================================================================
VLogException::VLogException( const VLog &log_ )
    : _log( log_ )
{
    _what = _log.sourcePoint() + " " + _log.str();
}
//=======================================================================================
const VLog &VLogException::log() const noexcept
{
    return _log;
}
//=======================================================================================
const char *VLogException::what() const noexcept
{
    return _what.c_str();
}
//=======================================================================================
//          VLOG EXCEPTION
//=======================================================================================




//=======================================================================================
//          ADD, CLEAR, PRINT LOGGER IMPLEMENTATION
//=======================================================================================
static void native_default_logger( const VLog &log )
{
    string preambul( "[Unknown log type] " );
    switch( log.type() )
    {
    case VLog::Type::Trace:  preambul = log.sourcePoint() + " T>> "; break;
    case VLog::Type::Deb:    preambul = log.sourcePoint() + " D>> "; break;
    case VLog::Type::Runlog: preambul = log.sourcePoint() + " " +
                                        log.isoDateTime() + " R>> "; break;
    case VLog::Type::Warn:   preambul = log.sourcePoint() + " WARN >>> "; break;
    case VLog::Type::Fatal:  preambul = log.sourcePoint() + " FATAL!!! >>>> "; break;
    }
    cout << preambul << log.str() << endl;
}
//=======================================================================================


//=======================================================================================
using Log_Handler = VLog::OutControl::Handler;
static unordered_map<int, Log_Handler> log_handles = []()
{
    decltype(log_handles) res;
    res.emplace(0, &native_default_logger);
    return res;
}();
int next_handle_id = 0;
//---------------------------------------------------------------------------------------
VLog::OutControl::Deleter
VLog::OutControl::add_logger( const Log_Handler &h )
{
    auto id = ++next_handle_id;
    log_handles.emplace( id, h );

    static int fake;
    return Deleter( &fake, [id](void*){ log_handles.erase(id); } );
}
//=======================================================================================
void VLog::OutControl::clear_all_loggers()
{
    log_handles.clear();
}
//=======================================================================================
Log_Handler VLog::OutControl::default_logger()
{
    return &native_default_logger;
}
//=======================================================================================
static void apply_log( const VLog &log )
{
    for ( const auto &h: log_handles )
        h.second( log );
}
//=======================================================================================
//          ADD, CLEAR, PRINT LOGGER IMPLEMENTATION
//=======================================================================================



//=======================================================================================
//      ФУНКЦИИ ПРИЕМА ЛОГОВ (vtrace, vdeb, vrunlog, vwarning, vfatal)
//=======================================================================================
void vtrace( const VLog &log )
{
    const_cast<VLog&>(log).set_type( VLog::Type::Trace );
    apply_log( log );
}
//=======================================================================================
void vdeb( const VLog &log )
{
    const_cast<VLog&>(log).set_type( VLog::Type::Deb );
    apply_log( log );
}
//=======================================================================================
void vrunlog( const VLog &log )
{
    const_cast<VLog&>(log).set_type( VLog::Type::Runlog );
    apply_log( log );
}
//=======================================================================================
void vwarning( const VLog &log )
{
    const_cast<VLog&>(log).set_type( VLog::Type::Warn );
    apply_log( log );
}
//=======================================================================================
void vfatal( const VLog &log )
{
    const_cast<VLog&>(log).set_type( VLog::Type::Fatal );
    apply_log( log );
    throw VLogException( log );
}
//=======================================================================================
//      ФУНКЦИИ ПРИЕМА ЛОГОВ (vtrace, vdeb, vrunlog, vwarning, vfatal)
//=======================================================================================



//=======================================================================================
//          Helpers for json translation
//=======================================================================================
static string from_log_type(VLog::Type t)
{
    switch (t) {
    case VLog::Type::Deb:    return "Deb";
    case VLog::Type::Fatal:  return "Fatal";
    case VLog::Type::Runlog: return "Runlog";
    case VLog::Type::Trace:  return "Trace";
    case VLog::Type::Warn:   return "Warn";
    }
    return "NOT_SET";
}
//=======================================================================================
static VLog::Type to_log_type( const std::string &t )
{
    if (t == "Deb")    return VLog::Type::Deb;
    if (t == "Fatal")  return VLog::Type::Fatal;
    if (t == "Runlog") return VLog::Type::Runlog;
    if (t == "Trace")  return VLog::Type::Trace;
    if (t == "Warn")   return VLog::Type::Warn;
    return VLog::Type::Deb; // by default...
}
//=======================================================================================
//          Helpers for json translation
//=======================================================================================



//=======================================================================================
//  using for pretty debug messages with location.
//=======================================================================================
static string pretty_fn_name(const string &fpath)
{
    auto rbegin = fpath.rbegin();
    auto rend = find( rbegin, fpath.rend(), '/' );

    string res;
    res.resize( rend - rbegin );
    reverse_copy( rbegin, rend, res.begin() );

    return res;
}
//=======================================================================================
template<typename T>
void get_type(T);
//=======================================================================================
//  Костыль, чтобы в дате и времени были ведущие нули.
//static string i2s(int i, uint len = 2)
//{
//    stringstream ss;
//    ss << i;

//    auto res = ss.str();

//    while (res.size() < len)
//        res.insert(res.begin(),'0');

//    return res;
//}
//=======================================================================================




//=======================================================================================
class VLog::Pimpl
{
    void init_arg();

public:
    Pimpl()
    {
        init_arg();
    }

    Pimpl( const char *file, const char *func, int line )
        : file( file )
        , func( func )
        , line( line )
        , timestamp( system_clock::now()   )
        //, timestamp2( VDateTime::now() )
        , thread_id( this_thread::get_id() )
    {
        thread_str = varg(hex)( this_thread::get_id() );
        init_arg();
    }

    std::string file;
    std::string func;
    int         line;
    Type        type = Type::Deb;

    using clock_type = decltype(std::chrono::system_clock::now());
    clock_type timestamp;
    //VDateTime timestamp2;

    using thread_type = decltype(this_thread::get_id());
    thread_type thread_id;
    string thread_str;

    // Аккумулятор логирования.
    varg arg;
};
//=======================================================================================



//=======================================================================================
void VLog::Pimpl::init_arg()
{
    // Опции по умолчанию
    arg(varg::space);
}
//=======================================================================================
VLog::VLog()
    : p( new Pimpl )
{}
//=======================================================================================
varg &VLog::_arg()
{
    return p->arg;
}
//=======================================================================================
VLog::VLog( const char *file, const char *func, int line )
    : p( new Pimpl(file, func, line) )
{}
//=======================================================================================
string VLog::str() const
{
    return p->arg.str();
}
//=======================================================================================
string VLog::isoDateTime() const
{
    return VDateTime(p->timestamp).str_iso();
//    stringstream ss;

//    auto tse = p->timestamp.time_since_epoch();
//    auto ms = duration_cast<milliseconds>(tse).count() % 1000;

//    time_t tt = system_clock::to_time_t(p->timestamp);
//    tm *time = localtime( &tt );
//    ss << time->tm_year + 1900  << "-"
//       << i2s(time->tm_mon)     << "-"
//       << i2s(time->tm_mday)    << " "
//       << i2s(time->tm_hour)    << ":"
//       << i2s(time->tm_min)     << ":"
//       << i2s(time->tm_sec)     << "."
//       << i2s(ms, 3)            << " ";

//    return ss.str();
}
//=======================================================================================
string VLog::sourcePoint() const
{
    stringstream ss;

    ss << "["
       << pretty_fn_name(p->file)
       << ":" << p->line
       << "/" << p->func
       << "()]";

    return ss.str();
}
//=======================================================================================
string VLog::threadId() const
{
    return p->thread_str;
}
//=======================================================================================
void VLog::print() const
{
    cout << sourcePoint() << " >> " << str() << endl;
}
//=======================================================================================
VLog::Type VLog::type() const
{
    return p->type;
}
//=======================================================================================
void VLog::set_type(VLog::Type t)
{
    p->type = t;
}
//=======================================================================================



//=======================================================================================
//          JSON SERIALIZATION / DESERIALIZATION
//=======================================================================================
string VLog::to_json() const
{
    Json::object obj;
    obj["target"] = "vlog";

    obj["file"] = p->file;
    obj["func"] = p->func;
    obj["line"] = p->line;

    obj["thread"] = threadId();

    auto duration = p->timestamp.time_since_epoch();
    auto usec = duration_cast<microseconds>(duration);
    obj["utc_sec"]  = int( usec.count() / 1000000 );
    obj["utc_usec"] = int( usec.count() % 1000000 );

    obj["text"] = p->arg.str();

    obj["log-type"] = from_log_type( type() );

    return Json(obj).dump();
}
//=======================================================================================
VLog VLog::from_json( const string &parse_this, bool *ok_ )
{
    bool fake_ok;
    bool &ok = ok_ ? *ok_ : fake_ok;
    ok = false;

    VLog res;

    string err;
    auto json = Json::parse( parse_this, err );

    if ( !err.empty() ||
         !json.is_object() )
    {
        vdeb( vlog("Json log error/not object:", err) );
        return res;
    }

    auto obj = json.object_items();
    if ( obj["target"] != "vlog" )
    {
        vdeb( vlog("Target is not 'vlog'") );
        return res;
    }

    auto pp = res.p.get();
    pp->file = obj["file"].string_value();
    pp->func = obj["func"].string_value();
    pp->line = obj["line"].int_value();

    pp->thread_str = obj["thread"].string_value();

    auto secs  = obj["utc_sec"].int_value();
    auto usecs = obj["utc_usec"].int_value();
    pp->timestamp = Pimpl::clock_type( seconds(secs) + microseconds(usecs) );

    pp->arg( obj["text"].string_value() );

    res.set_type( to_log_type(obj["log-type"].string_value()) );

    ok = true;
    return  res;
}
//=======================================================================================
//          JSON SERIALIZATION / DESERIALIZATION
//=======================================================================================







//=======================================================================================
//VLogProxy::VLogProxy(VLogProxy *proxy)
//{
//    if (proxy)
//    {
//        trace.connect  ( &proxy->trace  );
//        deb.connect    ( &proxy->deb    );
//        runlog.connect ( &proxy->runlog );
//        warn.connect   ( &proxy->warn   );
//        fatal.connect  ( &proxy->fatal  );
//    }
//    else
//    {
//        trace.connect  ( this, &VLogProxy::_on_trace  );
//        deb.connect    ( this, &VLogProxy::_on_deb    );
//        runlog.connect ( this, &VLogProxy::_on_runlog );
//        warn.connect   ( this, &VLogProxy::_on_warn   );
//        fatal.connect  ( this, &VLogProxy::_on_fatal  );
//    }
//}
//=======================================================================================
//void VLogProxy::_on_trace(const VLog &log)
//{
//    varg( log.sourcePoint(), " T >>> ", log.str() ).print();
//}
//=======================================================================================
//void VLogProxy::_on_deb(const VLog &log)
//{
//    varg(log.sourcePoint(), " D >>> ", log.str()).print();
//}
//=======================================================================================
//void VLogProxy::_on_runlog(const VLog &log)
//{
//    varg( log.sourcePoint(), " ", log.isoDateTime(), " RUN: ", log.str() ).print();
//}
//=======================================================================================
//void VLogProxy::_on_warn(const VLog &log)
//{
//    varg(log.sourcePoint(), " WARNING: >>> ", log.str()).print();
//}
//=======================================================================================
//void VLogProxy::_on_fatal(const VLog &log)
//{
//    varg(log.sourcePoint(), " FATAL: >>> ", log.str()).print();
//    exit(42);
//}
//=======================================================================================


