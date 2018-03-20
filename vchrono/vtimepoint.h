#ifndef VTIMEPOINT_H
#define VTIMEPOINT_H

#include "varg.h"
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

    explicit _vTimePoint() {}
    explicit _vTimePoint( const timepoint_t &tp ) : _tp(tp) {}

    template<typename Duration2>
    explicit _vTimePoint( const Duration2 &d2 ); // Построение из любого duration.

    timepoint_t time_point() const { return _tp; }

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

    // Используется функцией strftime, размер результата не должен превышать 256 байт.
    // http://en.cppreference.com/w/cpp/chrono/c/strftime
    std::string str_format( const std::string &fmt ) const;

    std::string str_iso() const;
    std::string str_iso_zzz() const;

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
class VSystemTimePoint : public _vTimePoint<std::chrono::system_clock, VSystemTimePoint>
{
public:
    using _vTimePoint::_vTimePoint;

    static VSystemTimePoint now()
    { return VSystemTimePoint( std::chrono::system_clock::now() ); }

    VSystemTimePoint operator - (const VSystemTimePoint &rhs) const
    {
        return VSystemTimePoint( this->time_point() - rhs.time_point() );
    }
};
// By default, using system time.
using VTimePoint = VSystemTimePoint;
//=======================================================================================
//      System time point
//=======================================================================================





//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
template<typename Clk, typename Derived>
template<typename Duration2>
_vTimePoint<Clk,Derived>::_vTimePoint( const Duration2 &d2 )
    : _vTimePoint( timepoint_t(d2) )
{}
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
bool _vTimePoint<Clk,Derived>::operator == (const _vTimePoint<Clk,Derived> &rhs) const
{
    return time_point() == rhs.time_point();
}
//=======================================================================================
template<typename Clk, typename Derived>
bool _vTimePoint<Clk,Derived>::operator != (const _vTimePoint<Clk,Derived> &rhs) const
{
    return time_point() != rhs.time_point();
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
    return varg(str_iso(), ".")
               (std::setfill('0'), std::setw(3), microseconds().count() % 1000);
}
//=======================================================================================
//=======================================================================================
template<typename Clk, typename Derived>
template<typename Duration>
Derived &_vTimePoint<Clk,Derived>::operator -= ( const Duration &rhs )
{
    _tp -= rhs;
    return *this;
}
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================







#endif // VTIMEPOINT_H
