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


#include "vposix_signal.h"


#include <signal.h>
#include <unistd.h> // alarm here.

#include <vposix_core.h>
#include "verror.h"

using namespace vposix;

//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
static bool is_sigerr( Signal::CallBack cb )
{
    return cb == SIG_ERR;
}
#pragma GCC diagnostic pop
//=======================================================================================

//=======================================================================================
int Signal::sig_interactive()           { return SIGINT;    }
int Signal::sig_termination_request()   { return SIGTERM;   }
int Signal::sig_killed()                { return SIGKILL;   }
int Signal::sig_alarm()                 { return SIGALRM;   }
//=======================================================================================

//=======================================================================================
Signal::CallBack Signal::_signal( int sig, Signal::CallBack cb )
{
    if ( do_trace() ) VTRACE( "V::signal(",sig,")" );

    //  Здесь не получается завернуть в linux_call, т.к. результат -- указатель.
    //  Происходит ошибка кастования. Можно ухойдокать вызов, в проверке сделать
    //  кастование, но очень не хочется вносить кашу в шаблон.
    auto res = ::signal( sig, cb );

    if ( is_sigerr(res) )
        Errno().throw_verror( "SIGERR" );

    return res;
}
//=======================================================================================
unsigned int Signal::_alarm( unsigned int seconds )
{
    if ( do_trace() ) VTRACE( "V::alarm(",seconds,")" );
    return ::alarm( seconds );
}
//=======================================================================================
void Signal::register_std_stops( CallBack cb )
{
    _signal( sig_interactive(),         cb );
    _signal( sig_termination_request(), cb );
}
//=======================================================================================
unsigned int Signal::re_alarm( unsigned int seconds, Signal::CallBack cb )
{
    _signal( sig_alarm(), cb );
    return _alarm( seconds );
}
//=======================================================================================
