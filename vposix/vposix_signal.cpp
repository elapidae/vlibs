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
