/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


#ifndef VTIMEPOINT_H
#define VTIMEPOINT_H

#include "vcat.h"
#include <chrono>
#include <ctime>
#include <iomanip>

//=======================================================================================
/**
 *      Группа классов - оберток вокруг std::chrono::*_clock.
 *
 *  Предоставляется три класса, соответствующих введенным в 11 Стандарте:
 *      class VSystemTimePoint
 *      class VSteadyTimePoint
 *      class VHighReslutionTimePoint
 *      using VTimePoint = VSystemTimePoint // по умолчанию используется системное время.
 *
 *  Все они предоставляют одинаковый интерфейс, описанный через шаблон _vTimePoint,
 *  читать его не очень приятно, попробую описать API (на примере VTimePoint):
 *
 *  NB! Класс не заточен для работы с локальным временем. Подразумевается UTC время.
 *      Если будут запросы по работе с локальным представлением времени, необходимо будет
 *      продумать API, помогайте!
 *
 *  (ts -- сокращение от timestamp, подразумевает созданный экземпляр)
 *
 *      VTimePoint::now() // статический метод захвата текущего времени.
 *
 *  // стандарные вхождения:
 *      [as in std::chrono] time_point();
 *      time_t to_time_t();
 *
 *      year(), month(), day(), hour(), minute(), second()       // int типы.
 *      nanoseconds(), microseconds(), milliseconds(), seconds() // std::chrono типы.
 *
 *  Операторы сравнения.
 *  NB! Если какие-нибудь сравнения не будут действовать -- сообщите автору!
 *
 *  Есть операторы вычитания, т.е. можно писать:
 *      auto ts = VTimePoint::now();
 *      .... // long code
 *      auto diff_ts = VTimePoint::now() - ts;
 *      ts -= VTimePoint::now();
 *
 *  TODO: пока не введены операторы суммирования (не уверен, что они нужны).
 *
 *  Преобразования в строки:
 *      str_datetime()                      // yyyy-MM-dd hh:mm:ss
 *      str_datetime_zzz()                  // yyyy-MM-dd hh:mm:ss.zzz
 *      str_date()                          // yyyy-MM-dd
 *      str_time()                          // hh:mm:ss
 *      str_time_zzz()                      // hh:mm:ss.zzz
 *      str_datetime_for_filenames()        // yyyy-MM-dd_T_hh_mm_ss (без ':', пробелов)
 *      str_datetime_zzz_for_filenames()    // yyyy-MM-dd_T_hh_mm_ss.zzz
 *
 *      // Произвольный формат.
 *      // Используется функция strftime, размер результата не должен превышать 256 байт.
 *      // http://en.cppreference.com/w/cpp/chrono/c/strftime
 *      std::string str_format( const std::string &fmt ) const;
 *
 *  Не касается класса непосредственно:
 *  Перегружен стандартный вывод для типов std::chrono::[milli/micro/nano]seconds.
 *  Т.е. после включения заголовка (#include "vtimepoint.h") можно писать так:
 *      std::cout << VTimePoint::now().milliseconds();
 *      // то же самое.
 *      std::cout << std::chrono::duration_cast<std::chrono::milliseconds>
 *                                                    (std::chrono::system_clock::now());
**/
//=======================================================================================



//=======================================================================================
//      GENERAL TEMPLATE
//=======================================================================================
class _vtimepoint_helper
{
public:
    // Форматы для get/put_time(); к сожалению, не поддерживаются миллисекунды.
    static const char *fmt_datetime();
    static const char *fmt_date();
    static const char *fmt_time();
    static const char *fmt_datetime_for_filename();

protected:
    static time_t  _tm_to_time_t( std::tm *tm );
    static std::tm _time_t_to_tm( time_t tt   );
    static std::tm _from_format( const std::string &dt, const std::string &fmt );
    static std::string _str_format( time_t tt, const std::string &fmt );

    _vtimepoint_helper() = default;
};
//=======================================================================================
template<typename Clk, typename Derived>
class _vTimePoint : public _vtimepoint_helper
{
public:

    using timepoint_type = typename Clk::time_point;

    static bool is_steady();

    static Derived now();

    static Derived from_format  ( const std::string &dt, const std::string &fmt );
    static Derived from_datetime( const std::string &dt ); // From "yyyy-MM-dd hh:mm:ss".

    explicit _vTimePoint();
    explicit _vTimePoint( const timepoint_type &tp );
    explicit _vTimePoint( time_t tt );

    template<typename Duration2>
    explicit _vTimePoint( const Duration2 &d2 ); // Построение из любого duration.

    timepoint_type time_point() const;
    time_t         to_time_t()  const;

    int year()          const;  //
    int month()         const;  //  NB! 0..11
    int day()           const;  //  NB! 1..31
    int hour()          const;  //  NB! 0..23
    int minute()        const;  //  NB! 0..59
    int second()        const;  //  NB! 0..59
    int millisecond()   const;  //  NB! 0..999

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

    template<typename Duration> bool operator <  ( const Duration &rhs ) const;
    template<typename Duration> bool operator >  ( const Duration &rhs ) const;
    template<typename Duration> bool operator <= ( const Duration &rhs ) const;
    template<typename Duration> bool operator >= ( const Duration &rhs ) const;
    template<typename Duration> bool operator == ( const Duration &rhs ) const;
    template<typename Duration> bool operator != ( const Duration &rhs ) const;

    template<typename Duration>
    Derived &operator -= ( const Duration &rhs );

    Derived operator - (const Derived &rhs) const;

    // Не работает...
    //template<typename Duration>
    //Derived &operator += ( const Duration &rhs );
    //Derived operator + (const Derived &rhs) const;

    // Используется функцией strftime, размер результата не должен превышать 256 байт.
    // http://en.cppreference.com/w/cpp/chrono/c/strftime
    std::string str_format( const std::string &fmt ) const;

    std::string str_datetime()                   const;
    std::string str_datetime_zzz()               const;

    std::string str_date()                       const;

    std::string str_time()                       const;
    std::string str_time_zzz()                   const;

    std::string str_datetime_for_filename()      const;
    std::string str_datetime_zzz_for_filenames() const;

private:
    timepoint_type _tp;
};
//=======================================================================================
//      GENERAL TEMPLATE
//=======================================================================================



//=======================================================================================
// https://habr.com/post/140357/
// Литералами пользоваться так: 1_second; -20_millisec; 200_microsec; -3000_nanosec; ...
std::chrono::seconds        operator "" _seconds    ( unsigned long long  s );
std::chrono::milliseconds   operator "" _millisec   ( unsigned long long ms );
std::chrono::microseconds   operator "" _microsec   ( unsigned long long us );
std::chrono::nanoseconds    operator "" _nanosec    ( unsigned long long ns );
//=======================================================================================
template<typename Other> std::chrono::seconds       to_seconds  ( Other && other );
template<typename Other> std::chrono::milliseconds  to_millisec ( Other && other );
template<typename Other> std::chrono::microseconds  to_microsec ( Other && other );
template<typename Other> std::chrono::nanoseconds   to_nanosec  ( Other && other );
//=======================================================================================




//=======================================================================================
// Старый компилятор не умеет прокси конструкторов, пишем костыль.
#define V_GNUC_VERSION_ELPD ((__GNUC__ * 100) + __GNUC_MINOR__)
#if V_GNUC_VERSION_ELPD > 408       // версии компилятора выше 4.8
    #define V_GNUC_CAN_USE_CTOR_PROXY
#endif

#ifdef V_GNUC_CAN_USE_CTOR_PROXY
//=======================================================================================
//      System time point
//=======================================================================================
class VSystemTimePoint final : public _vTimePoint< std::chrono::system_clock,
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
#else
//=======================================================================================
//      System time point
//=======================================================================================
class VSystemTimePoint final : public _vTimePoint< std::chrono::system_clock,
                                                   VSystemTimePoint >
{
    using _base = _vTimePoint<std::chrono::system_clock, VSystemTimePoint>;
public:
    explicit VSystemTimePoint()                         : _base()   {}
    explicit VSystemTimePoint(const timepoint_type &tp) : _base(tp) {}
    explicit VSystemTimePoint(time_t tt)                : _base(tt) {}

    template<typename Duration2>
    explicit VSystemTimePoint(const Duration2 &d2)      : _base(d2) {}
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
    using _base = _vTimePoint<std::chrono::steady_clock, VSteadyTimePoint>;
public:
    explicit VSteadyTimePoint()                         : _base()   {}
    explicit VSteadyTimePoint(const timepoint_type &tp) : _base(tp) {}
    // нету, похоже...
    //explicit VSteadyTimePoint(time_t tt)                : _base(tt) {}

    template<typename Duration2>
    explicit VSteadyTimePoint(const Duration2 &d2)      : _base(d2) {}
};
//=======================================================================================
//      Steady time point
//=======================================================================================
//      High resolution time point
//=======================================================================================
class VHighResolutionTimePoint : public _vTimePoint< std::chrono::high_resolution_clock,
                                                     VHighResolutionTimePoint >
{
    using _base = _vTimePoint<std::chrono::high_resolution_clock,
                              VHighResolutionTimePoint>;
public:
    explicit VHighResolutionTimePoint()                         : _base()   {}
    explicit VHighResolutionTimePoint(const timepoint_type &tp) : _base(tp) {}
    explicit VHighResolutionTimePoint(time_t tt)                : _base(tt) {}

    template<typename Duration2>
    explicit VHighResolutionTimePoint(const Duration2 &d2)      : _base(d2) {}
};
//=======================================================================================
//      High resolution time point
//=======================================================================================
#endif // V_GNUC_CAN_USE_CTOR_PROXY


//=======================================================================================
//      Streaming for my and std types.
//=======================================================================================
template<typename Clk, typename Derived>
std::ostream & operator << ( std::ostream & os, const _vTimePoint<Clk,Derived> & val )
{
    os << "TimePoint(" << val.str_datetime_zzz() << ")";
    return os;
}
//=======================================================================================
std::ostream & operator << ( std::ostream & os, const std::chrono::seconds      & val );
std::ostream & operator << ( std::ostream & os, const std::chrono::milliseconds & val );
std::ostream & operator << ( std::ostream & os, const std::chrono::microseconds & val );
std::ostream & operator << ( std::ostream & os, const std::chrono::nanoseconds  & val );
//=======================================================================================
//      Streaming for std types.
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
bool _vTimePoint<Clk,Derived>::is_steady()
{
    return Clk::is_steady;
}
//=======================================================================================
template<typename Clk, typename Derived>
Derived _vTimePoint<Clk,Derived>::now()
{
    return Derived( Clk::now() );
}
//=======================================================================================
template<typename Clk, typename Derived>
Derived _vTimePoint<Clk,Derived>::from_format( const std::string &dt,
                                               const std::string &fmt )
{
    auto tm = _from_format( dt, fmt );
    return Derived( _tm_to_time_t(&tm) );
}
//=======================================================================================
template<typename Clk, typename Derived>
Derived _vTimePoint<Clk,Derived>::from_datetime( const std::string &dt )
{
    return from_format( dt, fmt_datetime() );
}
//=======================================================================================
template<typename Clk, typename Derived>
_vTimePoint<Clk,Derived>::_vTimePoint()
{}
//=======================================================================================
template<typename Clk, typename Derived>
_vTimePoint<Clk,Derived>::_vTimePoint( const _vTimePoint::timepoint_type &tp )
    : _tp(tp)
{}
//=======================================================================================
template<typename Clk, typename Derived>
_vTimePoint<Clk,Derived>::_vTimePoint( time_t tt )
    : _tp( Clk::from_time_t(tt) )
{}
//=======================================================================================
template<typename Clk, typename Derived>
typename _vTimePoint<Clk,Derived>::timepoint_type
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
    : _vTimePoint( timepoint_type(d2) )
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
int _vTimePoint<Clk,Derived>::millisecond() const
{
    return milliseconds().count() % 1000;
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
bool _vTimePoint<Clk,Derived>::operator < (const Duration &rhs) const
{
    return time_point().time_since_epoch() < rhs;
}
//=======================================================================================
template<typename Clk, typename Derived>
template<typename Duration>
bool _vTimePoint<Clk,Derived>::operator > (const Duration &rhs) const
{
    return time_point().time_since_epoch() > rhs;
}
//=======================================================================================
template<typename Clk, typename Derived>
template<typename Duration>
bool _vTimePoint<Clk,Derived>::operator <= (const Duration &rhs) const
{
    return time_point().time_since_epoch() <= rhs;
}
//=======================================================================================
template<typename Clk, typename Derived>
template<typename Duration>
bool _vTimePoint<Clk,Derived>::operator >= (const Duration &rhs) const
{
    return time_point().time_since_epoch() >= rhs;
}
//=======================================================================================
template<typename Clk, typename Derived>
template<typename Duration>
bool _vTimePoint<Clk,Derived>::operator == (const Duration &rhs) const
{
    return time_point().time_since_epoch() == rhs;
}
//=======================================================================================
template<typename Clk, typename Derived>
template<typename Duration>
bool _vTimePoint<Clk,Derived>::operator != (const Duration &rhs) const
{
    return time_point().time_since_epoch() != rhs;
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
//---------------------------------------------------------------------------------------
template<typename Clk, typename Derived>
Derived _vTimePoint<Clk,Derived>::operator - ( const Derived &rhs ) const
{
    return Derived( this->time_point() - rhs.time_point() );
}
//=======================================================================================
//template<typename Clk, typename Derived>
//template<typename Duration>
//Derived &_vTimePoint<Clk,Derived>::operator +=( const Duration &rhs )
//{
//    _tp += rhs;
//    return *this;
//}
//=======================================================================================
//template<typename Clk, typename Derived>
//Derived _vTimePoint<Clk,Derived>::operator +(const Derived &rhs) const
//{
//    return Derived( this->time_point() + rhs.time_point() );
//}
//=======================================================================================
template<typename Clk, typename Derived>
std::string _vTimePoint<Clk,Derived>::str_format( const std::string &fmt ) const
{
    auto tt = Clk::to_time_t( _tp );
    return _str_format( tt, fmt );
}
//=======================================================================================
template<typename Clk, typename Derived>
std::string _vTimePoint<Clk,Derived>::str_datetime() const
{
    return str_format( fmt_datetime() );
}
//=======================================================================================
template<typename Clk, typename Derived>
std::string _vTimePoint<Clk,Derived>::str_datetime_zzz() const
{
    return vcat(str_datetime())(".").num(millisecond(), 3, '0');
}
//=======================================================================================
template<typename Clk, typename Derived>
std::string _vTimePoint<Clk,Derived>::str_date() const
{
    return str_format( fmt_date() );
}
//=======================================================================================
template<typename Clk, typename Derived>
std::string _vTimePoint<Clk,Derived>::str_time() const
{
    return str_format( fmt_time() );
}
//=======================================================================================
template<typename Clk, typename Derived>
std::string _vTimePoint<Clk,Derived>::str_time_zzz() const
{
    return vcat(str_time())(".").num(millisecond(), 3, '0');
}
//=======================================================================================
template<typename Clk, typename Derived>
std::string _vTimePoint<Clk,Derived>::str_datetime_for_filename() const
{
    return str_format( fmt_datetime_for_filename() );
}
//=======================================================================================
template<typename Clk, typename Derived>
std::string _vTimePoint<Clk,Derived>::str_datetime_zzz_for_filenames() const
{
    return vcat(str_datetime_for_filename())('.').num(millisecond(), 3, '0');
}
//=======================================================================================
//      v_TimePoint
//=======================================================================================
//      to_* converters
//=======================================================================================
template<typename Other>
std::chrono::seconds to_seconds( Other && other )
{
    return std::chrono::duration_cast<std::chrono::seconds>( std::forward(other) );
}
//=======================================================================================
template<typename Other>
std::chrono::milliseconds to_millisec( Other && other )
{
    return std::chrono::duration_cast<std::chrono::milliseconds>( std::forward(other) );
}
//=======================================================================================
template<typename Other>
std::chrono::microseconds to_microsec( Other && other )
{
    return std::chrono::duration_cast<std::chrono::microseconds>( std::forward(other) );
}
//=======================================================================================
template<typename Other>
std::chrono::nanoseconds to_nanosec( Other && other )
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>( std::forward(other) );
}
//=======================================================================================
//      to_* converters
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================







#endif // VTIMEPOINT_H
