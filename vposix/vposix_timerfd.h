#ifndef VPOSIX_TIMERFD_H
#define VPOSIX_TIMERFD_H

#include <chrono>

//=======================================================================================
//  http://ru.manpages.org/timerfd_create/2
//=======================================================================================


//=======================================================================================
struct itimerspec;
//=======================================================================================
namespace vposix
{
    //===================================================================================
    class TimerFD
    {
    public:
        using nanosecs = std::chrono::nanoseconds;

        static int  create_monotonic();
        static void start_monotonic( int fd, const nanosecs& duration );
        static void singleshot_monotonic( int fd, const nanosecs& duration );

        static void stop( int fd );
        static int read( int fd );

    private:
        static void _settime( int fd,
                             // int flags, -- 0 / TFD_TIMER_ABSTIME. Use only 0.
                             const itimerspec& new_value,
                             itimerspec* old_value = nullptr );

        static void _gettime( int fd, itimerspec* cur_value );
    };
    //===================================================================================
} // namespace vposix
//=======================================================================================


#endif // VPOSIX_TIMERFD_H
