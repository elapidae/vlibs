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
    VDateTime() = delete;

public:
    using time_point_t = decltype( std::chrono::system_clock::now() );

    static VDateTime now();

    explicit VDateTime( const time_point_t &tp );

    time_point_t time_point() const;

    std::string str_iso() const;

    int     year()          const;
    int64_t seconds()       const;
    int64_t microseconds()  const;   // NB! Всего микросекунд, не остаток секунды.

    template<typename Duration>
    const VDateTime& operator += ( const Duration& d )
    {
        _timestamp += d;
        return *this;
    }

    bool set_system_time() const;

private:
    time_point_t _timestamp;

    mutable tm *_cstyle_time = nullptr;
    void _set_cstyle_time() const;
};
//=======================================================================================



#endif // VDATETIME_H
