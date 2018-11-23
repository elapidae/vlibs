#include "vposix_timerfd.h"

#include <sys/timerfd.h>
#include <assert.h>
#include "vposix_core.h"
#include "vposix_files.h"

#include "vlog_pretty.h"

using namespace vposix;


//=======================================================================================
//int TimerFD::_create()
//{
//    auto id = CLOCK_MONOTONIC;
//    auto flags = TFD_NONBLOCK | TFD_CLOEXEC;
//    //return Core::linux_call<int>( ::timerfd_create, id, flags );
//    return Core::linux_call( ::timerfd_create, id, flags );
//}
//=======================================================================================
int TimerFD::create_monotonic()
{
    auto id = CLOCK_MONOTONIC;
    auto flags = TFD_NONBLOCK | TFD_CLOEXEC;

    return Core::linux_call( ::timerfd_create, id, flags );
}
//=======================================================================================
void TimerFD::start_monotonic( int fd, const TimerFD::nanosecs &duration)
{
    auto sec = duration.count()  / 1000000000;
    auto nsec = duration.count() % 1000000000;
    itimerspec spec;

    spec.it_value.tv_sec  = sec;
    spec.it_value.tv_nsec = nsec;

    spec.it_interval.tv_sec  = sec;
    spec.it_interval.tv_nsec = nsec;

    _settime( fd, spec );
}
//=======================================================================================
void TimerFD::singleshot_monotonic(int fd, const TimerFD::nanosecs &duration)
{
    auto sec = duration.count()  / 1000000000;
    auto nsec = duration.count() % 1000000000;
    itimerspec spec;

    spec.it_value.tv_sec  = sec;
    spec.it_value.tv_nsec = nsec;

    spec.it_interval.tv_sec  = 0;
    spec.it_interval.tv_nsec = 0;

    _settime( fd, spec );
}
//=======================================================================================
void TimerFD::stop( int fd )
{
    itimerspec spec;

    spec.it_value.tv_sec  = 0;
    spec.it_value.tv_nsec = 0;

    spec.it_interval.tv_sec  = 0;
    spec.it_interval.tv_nsec = 0;

    _settime( fd, spec );
}
//=======================================================================================
int TimerFD::read( int fd )
{
    uint64_t res = 0;
    auto sz = Files::read_or_err( fd, &res, sizeof(res) );
    if ( sz == -1 )
    {
        Errno e;
        if ( !e.resource_unavailable_try_again() )
            e.throw_verror();
    }
    return int(res);
}
//=======================================================================================
void TimerFD::_settime( int fd,
                        const itimerspec& new_value,
                        itimerspec* old_value )
{
    int flags = 0; // May be TFD_TIMER_ABSTIME

    auto res = Core::linux_call( ::timerfd_settime, fd, flags, &new_value, old_value );
    assert( res == 0 );
}
//=======================================================================================
void TimerFD::_gettime( int fd, itimerspec *cur_value )
{

    auto res = Core::linux_call( ::timerfd_gettime, fd, cur_value );
    assert( res == 0 );
}
//=======================================================================================
