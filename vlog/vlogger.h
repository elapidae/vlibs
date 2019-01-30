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


#ifndef VLOGGER_H
#define VLOGGER_H

#include "vlogentry.h"
#include <functional>

//=======================================================================================
/*  UPD 2018-07-02
 *
 *  VLogger  -- класс, собирающий лог сообщение в строку и передающий его на обработку.
 *  Сам класс создавать "руками" не следует, он инстанцируется макросами
 *  VTRACE, VDEBUG, VRUNLOG, VWARNING, VFATAL (находятся в заголовке vlog.h). [1]
 *  Предоставляет расширенный потоковый интерфейс, см. описание vcat.h /у них одна база/.
 *
 *
 *  Предоставляются статические методы для настройки и управления логгированием:
 *  - void clear_executers ();
 *  - void add_executer    ( Executer  );
 *  - void execute         ( VLogEntry );   // вызывается из логгера.
 *  NB! Методы не потокобезопасные! Подразумевается, что логгирование настраивается
 *  в начале работы программы один раз и больше туда не лазиют!
 *  Вызывать execute() потокобезопасно если все executer-ы безопасны.
 *
 *  По умолчанию включен вывод в консоль, через cout.
 *
 * [1]
 *  UPD 2019-01-24 -- vlog_pretty.h признан deprecated.
 *  Макросы vtrace, vdeb, vrunlog, vwarning, vfatal перенесены в vlog.h.
*/
//=======================================================================================



//=======================================================================================
class VLogger final : public _vcat_iface<VLogger>
{
public:
    //-----------------------------------------------------------------------------------

    //  А здесь пусто... У класса интерфейс vcat (см. заголовок vcat.h).

    VLogEntry entry()       const;
    operator VLogEntry()    const;

    //-----------------------------------------------------------------------------------
    //  Кухня настройки логгирования.

    using Executer = std::function< void(const VLogEntry &entry) >;

    static void add_executer( Executer e );
    static void clear_executers();
    static void execute( const VLogEntry &entry );

    //  Выводят в виде "[file.cpp:123] DBG message\n";
    static void to_cout( const VLogEntry &entry );
    static void to_cerr( const VLogEntry &entry );
    static void to_cout_and_cerr( const VLogEntry &entry ); // warnings & fatals -> cerr

    //  Иногда надо, НО! Не злоупотребляйте!
    static void to_cout_mutexed( const VLogEntry &entry );
    static void to_cerr_mutexed( const VLogEntry &entry );
    static void to_cout_and_cerr_mutexed( const VLogEntry &entry );

    //-----------------------------------------------------------------------------------
    //  Внутренная кухня.

    //  Предназначен для создания исключительно из макросов.
    enum class _is_proxy { is_proxy, no_proxy };
    VLogger( VLogEntry::Level     level,
             const char*          file,
             int32_t              line,
             const char*          func,
             _is_proxy            proxy );

    ~VLogger();

    //-----------------------------------------------------------------------------------
private:
    VTimePoint          _stamp;
    VLogEntry::Level    _level;
    const char*         _file;
    int32_t             _line;
    const char*         _func;
    bool                _i_am_proxy;

    std::stringstream   _stream;

    friend class VError;
    friend class _vcat_iface<VLogger>;
    template<typename T> void do_cat( T&& val ) { _stream << std::forward<T>(val); }

    VLogger( VLogger && )                   = delete;
    VLogger( const VLogger & )              = delete;
    VLogger& operator = ( VLogger && )      = delete;
    VLogger& operator = ( const VLogger & ) = delete;
};
//=======================================================================================

#endif // VLOGGER_H
