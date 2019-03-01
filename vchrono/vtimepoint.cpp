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


//=======================================================================================
//      vtimepoint.cpp
//=======================================================================================
#include "vtimepoint.h"
#include <sys/time.h>

#include <stdexcept>



//=======================================================================================
//      Helper: formats & tranlations
//=======================================================================================
const char *_vtimepoint_helper::fmt_datetime()
{
    return "%Y-%m-%d %H:%M:%S";
}
//=======================================================================================
const char *_vtimepoint_helper::fmt_datetime_for_filename()
{
    return "%Y-%m-%d_T_%H_%M_%S";
}
//=======================================================================================
const char *_vtimepoint_helper::fmt_date()
{
    return "%Y-%m-%d";
}
//=======================================================================================
const char *_vtimepoint_helper::fmt_time()
{
    return "%H:%M:%S";
}
//=======================================================================================
// Милый mktime считает, что время локальное, не UTC.
// Еле нашел решение (которое "- timezone"):
// http://qaru.site/questions/221156/stdmktime-and-timezone-info
time_t _vtimepoint_helper::_tm_to_time_t( tm *tm )
{
    return std::mktime(tm) - timezone;
}
//=======================================================================================
std::tm _vtimepoint_helper::_time_t_to_tm( time_t tt )
{
    auto ptr = gmtime( &tt );
    return ptr ? *ptr : tm{};
}
//=======================================================================================

//=======================================================================================
//  Кто-то где-то использует старый компилятор, не поддерживающий метод std::get_time().
//  Для таких товарищей вместо преобразования будет исключение...
#ifdef V_USE_STD_GET_TIME_ELPD
  #undef V_USE_STD_GET_TIME_ELPD
#endif

#ifdef __GNUC__
  #if __GNUC__ >= 5
    #define V_USE_STD_GET_TIME_ELPD
  #endif // __GNUC__ >= 5
#endif // __GNUC__
//---------------------------------------------------------------------------------------
#ifdef V_USE_STD_GET_TIME_ELPD
std::tm _vtimepoint_helper::_from_format( const std::string &dt, const std::string &fmt )
{
    std::tm t = {};
    std::istringstream ss( dt );
    ss >> std::get_time( &t, fmt.c_str() );
    return ss.fail() ? tm{0,0,0,0,0,0,0,0,0,0,0} : t;
}
#else
#warning "This revision does not implement VTimePoint::from_format()... :("
std::tm from_format( const std::string &dt, const std::string &fmt )
{
    // Если спичит, давайте найдем как это делали в старом компиляторе, напишем.
    throw std::logic_error( "_vtimepoint_helper::_from_format(dt,fmt) not implemented "
                            "for this compiler. :(" );
}
#endif // V_USE_STD_GET_TIME_ELPD
//=======================================================================================

//=======================================================================================
std::string _vtimepoint_helper::_str_format( time_t tt, const std::string &fmt )
{
    std::tm tm = *std::gmtime( &tt );
    char res[257];
    auto sz = std::strftime( res, sizeof(res), fmt.c_str(), &tm );
    return std::string(res, sz);
}
//=======================================================================================
//      Helper: formats & tranlations
//=======================================================================================



//=======================================================================================
namespace _priv
{
    //-----------------------------------------------------------------------------------
    int _year_from_time_t( time_t tt )
    {
        return gmtime(&tt)->tm_year + 1900;
    }
    //-----------------------------------------------------------------------------------
    int _month_from_time_t(time_t tt)
    {
        return gmtime(&tt)->tm_mon + 1;
    }
    //-----------------------------------------------------------------------------------
    int _day_from_time_t(time_t tt)
    {
        return gmtime(&tt)->tm_mday;
    }
    //-----------------------------------------------------------------------------------
    int _hour_from_time_t(time_t tt)
    {
        return gmtime(&tt)->tm_hour;
    }
    //-----------------------------------------------------------------------------------
    int _minute_from_time_t(time_t tt)
    {
        return gmtime(&tt)->tm_min;
    }
    //-----------------------------------------------------------------------------------
    int _second_from_time_t(time_t tt)
    {
        return gmtime(&tt)->tm_sec;
    }
    //-----------------------------------------------------------------------------------
} // _priv namespace
//=======================================================================================
std::ostream &operator <<(std::ostream &os, const std::chrono::seconds &val)
{
    os << "seconds(" << val.count() << ')';
    return os;
}
//---------------------------------------------------------------------------------------
std::ostream &operator <<(std::ostream &os, const std::chrono::milliseconds &val)
{
    os << "milliseconds(" << val.count() << ')';
    return os;
}
//---------------------------------------------------------------------------------------
std::ostream &operator <<(std::ostream &os, const std::chrono::microseconds &val)
{
    os << "microseconds(" << val.count() << ')';
    return os;
}
//---------------------------------------------------------------------------------------
std::ostream &operator <<(std::ostream &os, const std::chrono::nanoseconds &val)
{
    os << "nanoseconds(" << val.count() << ')';
    return os;
}
//=======================================================================================
//      vtimepoint.cpp
//=======================================================================================



//=======================================================================================
std::chrono::seconds operator "" _seconds( unsigned long long s )
{
    return std::chrono::seconds( s );
}
//=======================================================================================
std::chrono::milliseconds operator "" _millisec( unsigned long long ms )
{
    return std::chrono::milliseconds( ms );
}
//=======================================================================================
std::chrono::microseconds operator "" _microsec( unsigned long long us )
{
    return std::chrono::microseconds( us );
}
//=======================================================================================
std::chrono::nanoseconds operator "" _nanosec( unsigned long long ns )
{
    return std::chrono::nanoseconds( ns );
}
//=======================================================================================
