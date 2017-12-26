#include "vtimer.h"

#include <unistd.h>

#include "vlogger.h"

VTimer::VTimer( int ms )
    : _thread( "timer" )
    , _timeout( &timeout )      // Sync threading.
    , _need_stop( true )
    , _stopped( true )
{
    if ( ms > 0 )
        start( ms );
}

VTimer::~VTimer()
{
    stop();
}

void VTimer::start( int ms )
{
    _need_stop = false;

    _thread.finvoke( [ms,this]()
    {
        _stopped = false;
        while (1)
        {
            usleep(ms * 1000);

            if (_need_stop)
                return;

            _timeout();     // Sync threading.
        }
        _stopped = true;
    });
}

void VTimer::stop()
{
    _need_stop = true;
}

bool VTimer::stopped() const
{
    return _stopped;
}


//void VTimeCounter::start()
//{
//    _point = std::chrono::steady_clock::now();
//}

//VTimeCounter::duration VTimeCounter::elapsed() const
//{
//    return std::chrono::steady_clock::now() - _point;
//}

//VTimeCounter::duration VTimeCounter::restart()
//{
//    auto res = elapsed();
//    start();
//    return res;
//}

//int VTimeCounter::elapsed_ms() const
//{
//    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed()).count();
//}

//int VTimeCounter::restart_ms()
//{
//    return std::chrono::duration_cast<std::chrono::milliseconds>(restart()).count();
//}
