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
        enum class Type { RealTime, Monotonic };

        TimerFD( Type t = Type::Monotonic );
        ~TimerFD();

        void start( int nanosec );
        void singleshot( int nanosec );

        void start( const std::chrono::nanoseconds& duration );
        void singleshot( const std::chrono::nanoseconds& duration );
        void stop();

        template<typename Duration>
        void start( const Duration& duration );

        template<typename Duration>
        void singleshot( const Duration& duration );

        //  Debug part, will be remove.
        int fd() const;
        uint64_t read();

    private:
        int _fd = -1;
        TimerFD& operator = ( const TimerFD& ) = delete;

        static int _create( Type t );

        static void _settime( int fd,
                             // int flags, -- 0 / TFD_TIMER_ABSTIME. Use only 0.
                             const itimerspec& new_value,
                             itimerspec* old_value = nullptr );

        static void _gettime( int fd, itimerspec* cur_value );
    };
    //===================================================================================
    template<typename Duration>
    void TimerFD::start( const Duration& duration )
    {
        start( std::chrono::duration_cast<std::chrono::nanoseconds>(duration) );
    }
    //===================================================================================
    template<typename Duration>
    void TimerFD::singleshot( const Duration& duration )
    {
        singleshot( std::chrono::duration_cast<std::chrono::nanoseconds>(duration) );
    }
    //===================================================================================
} // namespace vposix
//=======================================================================================


#endif // VPOSIX_TIMERFD_H
