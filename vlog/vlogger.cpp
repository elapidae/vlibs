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


#include "vlogger.h"

#include <iostream>
#include <vector>
#include <mutex>

#include "vlog.h"

using namespace std;


//=======================================================================================
//      VLogger
//=======================================================================================
VLogger::VLogger( VLogEntry::Level  level,
                  const char*       file,
                  int32_t           line,
                  const char*       func,
                  _is_proxy         proxy )
    : _stamp ( _stamp.now() )
    , _level ( level )
    , _file  ( file  )
    , _line  ( line  )
    , _func  ( func  )
    , _i_am_proxy( proxy == _is_proxy::is_proxy ? true : false )
{
    // Включаем поля по умолчанию.
    _stream << std::showbase << std::boolalpha;

    // Пробелы между выводимыми полями тоже включены по умолчанию.
    space();
}
//=======================================================================================
VLogger::~VLogger()
{
    if ( _i_am_proxy ) return;

    execute( entry() );
}
//=======================================================================================
VLogEntry VLogger::entry() const
{
    return VLogEntry( _level, _stamp, _file, _line, _func, _stream.str() );
}
//=======================================================================================
VLogger::operator VLogEntry() const
{
    return entry();
}
//=======================================================================================

//=======================================================================================
//      Настройка выполнения и обработка точек логгирования.
//=======================================================================================
static vector<VLogger::Executer> executers = []()
{
    vector<VLogger::Executer> res;
    //res.push_back( &VLogger::to_cout ); // Это логгер по умолчанию.
    res.push_back( &VLogger::to_cout_and_cerr ); // Это логгер по умолчанию.
    return res;
}();
//=======================================================================================
void VLogger::add_executer( VLogger::Executer executer )
{
    executers.push_back( executer );
}
//=======================================================================================
void VLogger::clear_executers()
{
    executers.clear();
}
//=======================================================================================
void VLogger::execute( const VLogEntry &entry )
{
    for ( auto & e: executers )
        e( entry );
}
//=======================================================================================

//=======================================================================================
//      Стандартный вывод
//=======================================================================================
void VLogger::to_cout( const VLogEntry &entry )
{
    cout << entry.record().place_level_msg() << endl;
}
//=======================================================================================
void VLogger::to_cerr( const VLogEntry &entry )
{
    cerr << entry.record().place_level_msg() << endl;
}
//=======================================================================================
void VLogger::to_cout_and_cerr( const VLogEntry &entry )
{
    if ( entry.is_warning() || entry.is_fatal() )
        to_cerr( entry );
    else
        to_cout( entry );
}
//=======================================================================================
void VLogger::to_cout_mutexed( const VLogEntry &entry )
{
    static std::mutex mutex;
    std::unique_lock<std::mutex> lock( mutex );
    to_cout( entry );
}
//=======================================================================================
void VLogger::to_cerr_mutexed( const VLogEntry &entry )
{
    static std::mutex mutex;
    std::unique_lock<std::mutex> lock( mutex );
    to_cerr( entry );
}
//=======================================================================================
void VLogger::to_cout_and_cerr_mutexed(const VLogEntry &entry)
{
    static std::mutex mutex;
    std::unique_lock<std::mutex> lock( mutex );
    to_cout_and_cerr( entry );
}
//=======================================================================================
//      VLogger
//=======================================================================================

