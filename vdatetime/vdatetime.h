#ifndef VDATETIME_H
#define VDATETIME_H

#include <string>
#include <chrono>

//=======================================================================================
//  Определение недели в терминах C++11
namespace std
{
    namespace chrono
    {
        static constexpr auto _seconds_in_week = 7 * 24 * 3600;
        using weeks = std::chrono::duration<int64_t, std::ratio<_seconds_in_week>>;

    } // chrono namespace

} // std namespace
//=======================================================================================


//=======================================================================================
//  В помощь определения времени навигаторам.
//  Интервал между 01.01.1970 (Unix UTC) и 06.01.1980 (GPS).
static constexpr std::chrono::seconds gps_to_epoch_secs( 315964800 );
static constexpr std::chrono::milliseconds ms_between_gps_and_utc( gps_to_epoch_secs );
static constexpr std::chrono::microseconds us_between_gps_and_utc( gps_to_epoch_secs );
//=======================================================================================




//=======================================================================================
class VDateTime
{
public:
    using time_point_t = decltype( std::chrono::system_clock::now() );
    using duration_t = time_point_t::duration;

    static VDateTime now();
    static VDateTime from_time_t( time_t t );

    VDateTime();
    explicit VDateTime( const time_point_t &tp );

    template<typename Duration>
    explicit VDateTime( const Duration &d )
        : VDateTime( time_point_t( std::chrono::duration_cast<duration_t>(d) ) ) {}


    time_point_t time_point() const;

    std::string str_iso() const;

    std::string str_date()  const;
    std::string str_time()  const;

    int     year()          const;
    int     month()         const;
    int     day()           const;
    int     hour()          const;
    int     minute()        const;
    int     second()        const;

    int64_t seconds()       const;
    int64_t milliseconds()  const;
    int64_t microseconds()  const;   // NB! Всего микросекунд, не остаток секунды.
    int64_t nanoseconds()   const;   // NB! Всего, не остаток секунды.

    template<typename Duration>
    const VDateTime& operator += ( const Duration& d )
    {
        _timestamp += d;
        return *this;
    }

    bool set_system_time() const;

    bool operator < ( const VDateTime & rhs ) const;
    bool operator > ( const VDateTime & rhs ) const;

    time_point_t::duration duration() const;

private:
    time_point_t _timestamp;

    mutable tm *_cstyle_time = nullptr;
    void _set_cstyle_time() const;
};
VDateTime operator - ( const VDateTime &lhs, const VDateTime &rhs );
//=======================================================================================



#endif // VDATETIME_H
