#ifndef VTIMEPOINT_H
#define VTIMEPOINT_H

#include <chrono>

//=======================================================================================
template<typename Clk, typename Derived>
class _VTimePoint
{
public:
    using timepoint_t = typename Clk::time_point;

    explicit _VTimePoint() {}
    explicit _VTimePoint( const timepoint_t &tp ) : _tp(tp) {}

    template<typename Duration2>
    explicit _VTimePoint( const Duration2 &d2 )
        : _VTimePoint( timepoint_t(d2) )
    {}

    timepoint_t time_point() const { return _tp; }

    std::chrono::nanoseconds    nanoseconds()   const;
    std::chrono::microseconds   microseconds()  const
    {
        return std::chrono::
               duration_cast<std::chrono::microseconds>(_tp.time_since_epoch());
    }
    std::chrono::milliseconds   milliseconds()  const
    {
        return std::chrono::
               duration_cast<std::chrono::milliseconds>(_tp.time_since_epoch());
    }
    std::chrono::seconds        seconds()       const;

    bool operator < ( const _VTimePoint &rhs ) const
    { return time_point() < rhs.time_point(); }

    bool operator > ( const _VTimePoint &rhs ) const
    { return time_point() > rhs.time_point(); }

    template<typename Duration>
    Derived &operator -= ( const Duration &rhs )
    {
        _tp -= rhs;
        return *this;
    }

private:
    typename Clk::time_point _tp;
};
//=======================================================================================


//=======================================================================================
class VSystemTimePoint : public _VTimePoint<std::chrono::system_clock, VSystemTimePoint>
{
public:
    using _VTimePoint::_VTimePoint;

    static VSystemTimePoint now()
    { return VSystemTimePoint( std::chrono::system_clock::now() ); }

    VSystemTimePoint operator - (const VSystemTimePoint &rhs) const
    {
        return VSystemTimePoint( this->time_point() - rhs.time_point() );
    }
};
using VTimePoint = VSystemTimePoint;
//=======================================================================================






#endif // VTIMEPOINT_H
