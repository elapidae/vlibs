#ifndef VTIMEPOINT_H
#define VTIMEPOINT_H

#include "vcat.h"
#include <chrono>
#include <ctime>
#include <iomanip>


//=======================================================================================
//      GENERAL TEMPLATE
//=======================================================================================
template<typename Clk, typename Derived>
class _vTimePoint
{
public:
    using timepoint_t = typename Clk::time_point;

    static Derived now();

    explicit _vTimePoint();
    explicit _vTimePoint( const timepoint_t &tp );

    template<typename Duration2>
    explicit _vTimePoint( const Duration2 &d2 ); // Построение из любого duration.

    timepoint_t time_point() const;
    time_t      to_time_t()  const;

    int year()      const;
    int month()     const;
    int day()       const;
    int hour()      const;
    int minute()    const;
    int second()    const;

    std::chrono::nanoseconds    nanoseconds()   const;
    std::chrono::microseconds   microseconds()  const;
    std::chrono::milliseconds   milliseconds()  const;
    std::chrono::seconds        seconds()       const;

    bool operator <  ( const _vTimePoint &rhs ) const;
    bool operator >  ( const _vTimePoint &rhs ) const;
    bool operator <= ( const _vTimePoint &rhs ) const;
    bool operator >= ( const _vTimePoint &rhs ) const;
    bool operator == ( const _vTimePoint &rhs ) const;
    bool operator != ( const _vTimePoint &rhs ) const;

    template<typename Duration>
    Derived &operator -= ( const Duration &rhs );

    Derived operator - (const Derived &rhs) const;

    // Используется функцией strftime, размер результата не должен превышать 256 байт.
    // http://en.cppreference.com/w/cpp/chrono/c/strftime
    std::string str_format( const std::string &fmt ) const;

    std::string str_iso() const;
    std::string str_iso_zzz() const;

    std::string str_date() const;

    std::string str_time() const;
    std::string str_time_zzz() const;

    std::string str_iso_for_filenames() const
    { return str_format("%Y-%m-%d_T_%H_%M_%S"); }

private:
    typename Clk::time_point _tp;
};
//=======================================================================================
//      GENERAL TEMPLATE
//=======================================================================================



//=======================================================================================
//      System time point
//=======================================================================================
class VSystemTimePoint : public _vTimePoint< std::chrono::system_clock,
                                             VSystemTimePoint >
{
public:
    using _vTimePoint::_vTimePoint;
};
// By default, using system time.
using VTimePoint = VSystemTimePoint;
//=======================================================================================
//      System time point
//=======================================================================================
//      Steady time point
//=======================================================================================
class VSteadyTimePoint : public _vTimePoint< std::chrono::steady_clock,
                                             VSteadyTimePoint >
{
public:
    using _vTimePoint::_vTimePoint;
};
//=======================================================================================
//      Steady time point
//=======================================================================================
//      High resolution time point
//=======================================================================================
class VHighResolutionTimePoint : public _vTimePoint< std::chrono::high_resolution_clock,
                                                     VHighResolutionTimePoint >
{
public:
    using _vTimePoint::_vTimePoint;
};
//=======================================================================================
//      High resolution time point
//=======================================================================================





//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
namespace _priv
{
    int _year_from_time_t   ( time_t tt );
    int _month_from_time_t  ( time_t tt );
    int _day_from_time_t    ( time_t tt );
    int _hour_from_time_t   ( time_t tt );
    int _minute_from_time_t ( time_t tt );
    int _second_from_time_t ( time_t tt );
}
//=======================================================================================
template<typename Clk, typename Derived>
Derived _vTimePoint<Clk,Derived>::now()
{
    return Derived( Clk::now() );
}
//=======================================================================================
template<typename Clk, typename Derived>
_vTimePoint<Clk,Derived>::_vTimePoint()
{}
//=======================================================================================
template<typename Clk, typename Derived>
_vTimePoint<Clk,Derived>::_vTimePoint( const _vTimePoint::timepoint_t &tp )
    : _tp(tp)
{}
//=======================================================================================
template<typename Clk, typename Derived>
typename _vTimePoint<Clk,Derived>::timepoint_t
_vTimePoint<Clk,Derived>::time_point() const
{
    return _tp;
}
//=======================================================================================
template<typename Clk, typename Derived>
time_t _vTimePoint<Clk,Derived>::to_time_t() const
{
    return Clk::to_time_t(_tp);
}
//=======================================================================================
template<typename Clk, typename Derived>
template<typename Duration2>
_vTimePoint<Clk,Derived>::_vTimePoint( const Duration2 &d2 )
    : _vTimePoint( timepoint_t(d2) )
{}
//=======================================================================================
template<typename Clk, typename Derived>
int _vTimePoint<Clk,Derived>::year() const
{
    return _priv::_year_from_time_t( to_time_t() );
}
//---------------------------------------------------------------------------------------
template<typename Clk, typename Derived>
int _vTimePoint<Clk,Derived>::month() const
{
    return _priv::_month_from_time_t( to_time_t() );
}
//---------------------------------------------------------------------------------------
template<typename Clk, typename Derived>
int _vTimePoint<Clk,Derived>::day() const
{
    return _priv::_day_from_time_t( to_time_t() );
}
//---------------------------------------------------------------------------------------
template<typename Clk, typename Derived>
int _vTimePoint<Clk,Derived>::hour() const
{
    return _priv::_hour_from_time_t( to_time_t() );
}
//---------------------------------------------------------------------------------------
template<typename Clk, typename Derived>
int _vTimePoint<Clk,Derived>::minute() const
{
    return _priv::_minute_from_time_t( to_time_t() );
}
//---------------------------------------------------------------------------------------
template<typename Clk, typename Derived>
int _vTimePoint<Clk,Derived>::second() const
{
    return _priv::_second_from_time_t( to_time_t() );
}
//=======================================================================================
template<typename Clk, typename Derived>
std::chrono::nanoseconds _vTimePoint<Clk,Derived>::nanoseconds() const
{
    return std::chrono::
            duration_cast<std::chrono::nanoseconds>(_tp.time_since_epoch());
}
//=======================================================================================
template<typename Clk, typename Derived>
std::chrono::microseconds _vTimePoint<Clk,Derived>::microseconds() const
{
    return std::chrono::
            duration_cast<std::chrono::microseconds>(_tp.time_since_epoch());
}
//=======================================================================================
template<typename Clk, typename Derived>
std::chrono::milliseconds _vTimePoint<Clk,Derived>::milliseconds() const
{
    return std::chrono::
            duration_cast<std::chrono::milliseconds>(_tp.time_since_epoch());
}
//=======================================================================================
template<typename Clk, typename Derived>
std::chrono::seconds _vTimePoint<Clk,Derived>::seconds() const
{
    return std::chrono::
            duration_cast<std::chrono::seconds>(_tp.time_since_epoch());
}
//=======================================================================================
template<typename Clk, typename Derived>
bool _vTimePoint<Clk,Derived>::operator < (const _vTimePoint<Clk,Derived> &rhs) const
{
    return time_point() < rhs.time_point();
}
//=======================================================================================
template<typename Clk, typename Derived>
bool _vTimePoint<Clk,Derived>::operator > (const _vTimePoint<Clk,Derived> &rhs) const
{
    return time_point() > rhs.time_point();
}
//=======================================================================================
template<typename Clk, typename Derived>
bool _vTimePoint<Clk,Derived>::operator <= (const _vTimePoint<Clk,Derived> &rhs) const
{
    return time_point() <= rhs.time_point();
}
//=======================================================================================
template<typename Clk, typename Derived>
bool _vTimePoint<Clk,Derived>::operator >= (const _vTimePoint<Clk,Derived> &rhs) const
{
    return time_point() >= rhs.time_point();
}
//=======================================================================================
template<typename Clk, typename Derived>
bool _vTimePoint<Clk,Derived>::operator == ( const _vTimePoint<Clk,Derived> &rhs ) const
{
    return time_point() == rhs.time_point();
}
//=======================================================================================
template<typename Clk, typename Derived>
bool _vTimePoint<Clk,Derived>::operator != ( const _vTimePoint<Clk,Derived> &rhs ) const
{
    return time_point() != rhs.time_point();
}
//=======================================================================================
template<typename Clk, typename Derived>
template<typename Duration>
Derived &_vTimePoint<Clk,Derived>::operator -= ( const Duration &rhs )
{
    _tp -= rhs;
    return *this;
}
//---------------------------------------------------------------------------------------
template<typename Clk, typename Derived>
Derived _vTimePoint<Clk,Derived>::operator - ( const Derived &rhs ) const
{
    return Derived( this->time_point() - rhs.time_point() );
}
//=======================================================================================
template<typename Clk, typename Derived>
std::string _vTimePoint<Clk,Derived>::str_format(const std::string &fmt) const
{
    auto tt = Clk::to_time_t(_tp);
    std::tm tm = *std::gmtime( &tt );

    char res[257];
    auto sz = std::strftime( res, sizeof(res), fmt.c_str(), &tm );
    return std::string(res, sz);
}
//=======================================================================================
template<typename Clk, typename Derived>
std::string _vTimePoint<Clk,Derived>::str_iso() const
{
    return str_format("%Y-%m-%d %H:%M:%S");
}
//=======================================================================================
template<typename Clk, typename Derived>
std::string _vTimePoint<Clk,Derived>::str_iso_zzz() const
{
    return vcat( str_iso(), "." )
                 .field_width(3).fill_char('0')( microseconds().count()%1000 );
}
//=======================================================================================
template<typename Clk, typename Derived>
std::string _vTimePoint<Clk,Derived>::str_date() const
{
    return str_format( "%Y-%m-%d" );
}
//=======================================================================================
template<typename Clk, typename Derived>
std::string _vTimePoint<Clk,Derived>::str_time() const
{
    return str_format( "%H:%M:%S" );
}
//=======================================================================================
template<typename Clk, typename Derived>
std::string _vTimePoint<Clk,Derived>::str_time_zzz() const
{
    return vcat( str_time(), ".")
                 .field_width(3).fill_char('0')( microseconds().count()%1000 );
}
//=======================================================================================
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================







#endif // VTIMEPOINT_H
