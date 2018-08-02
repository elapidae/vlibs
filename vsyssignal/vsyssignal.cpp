#include "vsyssignal.h"


#include <signal.h>


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

    signal( SIGINT,  _on_signals );
    signal( SIGKILL, _on_signals );
    signal( SIGTERM, _on_signals );

    _cb_registered = true;
}
//=======================================================================================

