#include "vapplication.h"

#include "verror.h"
#include "vcat_containers.h"
#include "vlog_pretty.h"
#include <assert.h>
#include <algorithm>
#include <mutex>
#include <unistd.h>
#include "vfile.h"
#include "vposix_files.h"
#include "vposix_errno.h"

#include "vpoll/veventqueue.h"
//#include "vpoll/vpoll_fds.h"

//=======================================================================================
//      VAPPLICATION
//=======================================================================================

//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
class VApplication::_pimpl
{
    //  Мьютекс используется, чтобы ограничить создание класса одним экземпляром.
    //  В будущем планируется контролировать классом главный поток.
    static std::mutex mutex;

public:

    _pimpl( int argc, const char * const * const argv )
        : args( argc, argv )
      //  , poll_queue( VPoll_Queue::init_fds_and_get_queue() )
    {
        if ( !mutex.try_lock() )
            throw verror << "Object VApplication must be created once!";
    }
    ~_pimpl()
    {
     //   VPoll_Queue::del_queue();
        VPoll::del_poll();

        mutex.unlock();
    }

    Args args;
    Pid  pid;

  //  VPoll_Queue poll_queue;
    volatile bool let_stop;
};
#pragma GCC diagnostic pop
//=======================================================================================
std::mutex VApplication::_pimpl::mutex;
//=======================================================================================
VApplication::VApplication()
    : p( new _pimpl(0, nullptr) )
{}
//=======================================================================================
VApplication::VApplication( int argc, const char * const * const argv )
    : p( new _pimpl(argc, argv) )
{}
//=======================================================================================
//VApplication::~VApplication()
//{}
//=======================================================================================
//void VApplication::do_invoke( VPoll_Queue_Iface::InvokeFunc && func )
//{
//    assert( func );
//    p->poll_queue.invoke( std::move(func) );
//}
//=======================================================================================
const VApplication::Args &VApplication::args() const
{
    return p->args;
}
//=======================================================================================
VApplication::Args &VApplication::args()
{
    return p->args;
}
//=======================================================================================
std::string VApplication::app_name() const
{
    return args().app_name();
}
//=======================================================================================
std::string VApplication::app_path() const
{
    return args().app_path();
}
//=======================================================================================
std::string VApplication::full_app_name() const
{
    return args().full_app_name();
}
//=======================================================================================
VApplication::Pid &VApplication::pid()
{
    return p->pid;
}
//=======================================================================================
void VApplication::poll()
{
    p->let_stop = false;
    VPoll::poll( &p->let_stop );
}
//=======================================================================================
void VApplication::stop()
{
    p->let_stop = true;
    //p->poll_queue.invoke( InvokeFunc() );
}
//=======================================================================================
//      VAPPLICATION
//=======================================================================================



//=======================================================================================
//      ARGS
//=======================================================================================
VApplication::Args::Args( int argc, const char * const * const argv )
{
    assert( argc >= 0 );
    if (argc > 0)
    {
        assert( argv && argv[0] );

        _full_app_name = argv[0];
        assert( !_full_app_name.empty() );
    }

    for ( int i = 1; i < argc; ++i )
    {
        _args.push_back( argv[i] );
    }
}
//=======================================================================================
std::string VApplication::Args::app_name() const
{
    auto last_slash = std::find( _full_app_name.rbegin(), _full_app_name.rend(), '/' );
    return { last_slash.base(), _full_app_name.end() };
}
//=======================================================================================
std::string VApplication::Args::app_path() const
{
    auto last_slash = std::find( _full_app_name.rbegin(), _full_app_name.rend(), '/' );
    return { _full_app_name.begin(), last_slash.base() };
}
//=======================================================================================
std::string VApplication::Args::full_app_name() const
{
    return _full_app_name;
}
//=======================================================================================
bool VApplication::Args::has_flag(cstr name ) const
{
    return _args.end() != std::find( _args.begin(), _args.end(), name );
}
//=======================================================================================
std::string VApplication::Args::std_value( cstr name ) const
{
    auto name_pos = std::find( _args.begin(), _args.end(), name );
    if ( name_pos == _args.end() )
        throw std::runtime_error( vcat("Cannot find argument '", name, "'.") );

    auto val_pos = name_pos + 1;
    if ( val_pos == _args.end() )
        throw std::runtime_error( vcat("Argument '", name, "' has not any value.") );

    return *val_pos;
}
//=======================================================================================
std::string VApplication::Args::std_value_or( cstr name, cstr default_val ) const
{
    auto name_pos = std::find( _args.begin(), _args.end(), name );
    if ( name_pos == _args.end() )
        return default_val;

    auto val_pos = name_pos + 1;
    if ( val_pos == _args.end() )
    {
        vwarning.nospace()("Argument '", name, "' has not any value"
                                               ", using '", default_val, "' instead.");
        return default_val;
    }

    return *val_pos;
}
//=======================================================================================
bool VApplication::Args::take_has_flag(cstr name )
{
    auto res = has_flag( name );

    if ( res )
        _args.erase( std::find(_args.begin(), _args.end(), name) );

    return res;
}
//=======================================================================================
std::string VApplication::Args::take_std_value( cstr name )
{
    auto res = std_value( name );

    auto name_pos = std::find( _args.begin(), _args.end(), name );
    _args.erase( name_pos, name_pos + 2 );

    return res;
}
//=======================================================================================
std::string VApplication::Args::take_std_value_or( cstr name, cstr default_val )
{
    auto res = std_value_or( name, default_val );

    //  Если нету имени параметра, значит ничего удалять не надо, сразу выходим.
    auto name_pos = std::find( _args.begin(), _args.end(), name );
    if ( name_pos == _args.end() )
        return res;

    // Если значение присутствует, то захватываем его на удаление.
    auto val_pos = name_pos + 1;
    if ( val_pos != _args.end() )
        ++val_pos;

    _args.erase( name_pos, val_pos );
    return res;
}
//=======================================================================================
const std::vector<std::string> &VApplication::Args::remain() const
{
    return _args;
}
//=======================================================================================
void VApplication::Args::throw_verror_if_not_empty()
{
    if ( _args.empty() ) return;

    throw verror("Unknown arguments: ", _args);
}
//=======================================================================================
//      ARGS
//=======================================================================================


//=======================================================================================
//      PID
//=======================================================================================
class VApplication::Pid::_pimpl
{
public:
    std::string fname;
    std::unique_ptr<VFile> file;
};
//=======================================================================================
pid_t VApplication::Pid::pid()
{
    return ::getpid();
}
//=======================================================================================
VApplication::Pid::Pid()
    : p( new _pimpl )
{}
//=======================================================================================
VApplication::Pid::~Pid()
{
    if ( !p->file ) return;

    vposix::Files::remove( p->fname );
}
//=======================================================================================
void VApplication::Pid::store( cstr path, cstr fname )
{
    if ( path.empty() || fname.empty() )
        throw verror << "Путь или имя файла для сохранения PID процесса пусты.";

    p->fname = path + "/" + fname;

    system( ("mkdir -p " + path).c_str() );

    if ( p->file )
        vwarning << "Pid file already catched.";

    p->file.reset( new VFile(p->fname) );
    p->file->write( vcat(pid()) );
}
//=======================================================================================
//      PID
//=======================================================================================
