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


#include "vsyssignal.h"


#include <signal.h>
#include "vlog_pretty.h"

//=======================================================================================
bool VSysSignal::_cb_registered = false;
std::vector<VSysSignal::Stopper0> VSysSignal::_s0;
std::vector<VSysSignal::Stopper1> VSysSignal::_s1;
//=======================================================================================


//=======================================================================================
void VSysSignal::watch( VSysSignal::Stopper0 s0 )
{
    _register_cb();
    _s0.push_back( s0 );
}
//=======================================================================================
void VSysSignal::watch( VSysSignal::Stopper1 s1 )
{
    _register_cb();
    _s1.push_back( s1 );
}
//=======================================================================================
void VSysSignal::_on_signals( int s )
{
    for ( auto && s0: _s0 )
        s0();

    for ( auto && s1: _s1 )
        s1( s );
}
//=======================================================================================
void VSysSignal::_register_cb()
{
    if ( _cb_registered ) return;

    vwarning << "Механизм VSysSignal::watch устарел. "
                "Используйте вместо него VApplication.\nВ него встроен механизм "
                "остановки app.poll() по сигналам Ctrl+C и kill <pid>.";

    signal( SIGINT,  _on_signals );
    signal( SIGKILL, _on_signals ); //  Эту вообще нельзя установить.
    signal( SIGTERM, _on_signals );

    _cb_registered = true;
}
//=======================================================================================

