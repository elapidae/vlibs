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


#include "vapplication.h"


#include "vposix_files.h"
#include "vposix_core.h"
#include "vposix_signal.h"
#include "vfile.h"

#include "verror.h"
#include "vcat_containers.h"
#include "vlog.h"
#include <assert.h>

#include <algorithm>
#include <mutex>

#include "vinvoke/vinvokequeue.h"
#include "vpoll/vpoll.h"



//=======================================================================================
//      VAPPLICATION
//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
class VApplication::_pimpl final
{
    //  Мьютекс используется, чтобы ограничить создание класса одним экземпляром.
    static std::mutex mutex;

public:
    static std::atomic<VApplication*> app;
    static bool signals_registered;

    static void on_signal( int )
    {}

    _pimpl( int argc, const char * const * const argv, VApplication* own );
    ~_pimpl();


    Args args;
    Pid  pid;

    VInvokeQueue invoke_queue;
    bool let_stop_poll;

    std::vector<InvokeFunc> dtor_funcs;
};
#pragma GCC diagnostic pop
//=======================================================================================
std::mutex                  VApplication::_pimpl::mutex;
std::atomic<VApplication*>  VApplication::_pimpl::app {nullptr};
//---------------------------------------------------------------------------------------
static void signals_cb(int)
{
    VApplication::app()->stop();
}
//---------------------------------------------------------------------------------------
bool VApplication::_pimpl::signals_registered = []()
{
    vposix::Signal::register_std_stops( signals_cb );
    return true;
}();
//=======================================================================================

//=======================================================================================
//  Решаются задачи:
//  1. Зафиксировать факт создания одного и только одного экземпляра класса;
//  2. Инициировать поллинг потока;
//  3. Зарегистрировать invoke очередь (очередь вызовов).
//  4. Зафиксировать статическое представление приложения.
VApplication::_pimpl::_pimpl( int argc, const char * const * const argv,
                              VApplication* own )
    : args( argc, argv )
{
    if ( !mutex.try_lock() )
        throw verror << "Object VApplication must be created once!";

    VPoll::add_poll();

    invoke_queue.open_polling( &let_stop_poll );

    app = own;
}
//=======================================================================================
//
VApplication::_pimpl::~_pimpl()
{
    app = nullptr;

    invoke_queue.close_polling();

    VPoll::del_poll();

    for ( auto& f: dtor_funcs ) f();

    mutex.unlock();
}
//=======================================================================================
VApplication* VApplication::app()
{
    assert( _pimpl::app && "Create VApplication object first." );
    return _pimpl::app;
}
//=======================================================================================
VApplication::VApplication()
    : p( new _pimpl(0, nullptr, this) )
{}
//=======================================================================================
VApplication::VApplication( int argc, const char * const * const argv )
    : p( new _pimpl(argc, argv, this) )
{}
//=======================================================================================
VApplication::~VApplication()
{}
//=======================================================================================
void VApplication::do_invoke( InvokeFunc && func )
{
    p->invoke_queue.enqueue( std::move(func) );
}
//=======================================================================================
void VApplication::poll()
{
    p->let_stop_poll = false;
    VPoll::poll( &p->let_stop_poll );
}
//=======================================================================================
//  nullptr as InvokeFunc is a stop signal.
void VApplication::stop()
{
    p->invoke_queue.enqueue( nullptr );
}
//=======================================================================================
void VApplication::add_post_routine( const VInvoke_Iface::InvokeFunc &func )
{
    p->dtor_funcs.push_back( func );
}
//=======================================================================================

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
    return vposix::Core::pid();
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

