#include "vdatetime.h"

#include <assert.h>
#include <sys/time.h>
#include "varg.h"


using namespace std;
using namespace std::chrono;


//=======================================================================================
//  Костыль, чтобы в дате и времени были ведущие нули.
static string i2s(int i, uint len = 2)
{
    stringstream ss;
    ss << i;

    auto res = ss.str();

    while (res.size() < len)
        res.insert(res.begin(),'0');

    return res;
}
//=======================================================================================


//=======================================================================================
VDateTime::VDateTime()
    : _timestamp( system_clock::from_time_t(0) )
{}
//=======================================================================================
VDateTime::VDateTime( const VDateTime::time_point_t &tp )
    : _timestamp( tp )
{}
//=======================================================================================
VDateTime::time_point_t VDateTime::time_point() const
{
    return _timestamp;
}
//=======================================================================================
void VDateTime::_set_cstyle_time() const
{
    auto tt = system_clock::to_time_t( _timestamp );
    _cstyle_time = localtime( &tt );
}
//=======================================================================================
// http://www.cplusplus.com/reference/ctime/strftime/
string VDateTime::str_iso() const
{
    auto tse = _timestamp.time_since_epoch();
    auto ms = duration_cast<chrono::milliseconds>(tse).count() % 1000;

    _set_cstyle_time();


    char buffer[32];
    auto res_size = strftime( buffer, sizeof buffer, "%F %T", _cstyle_time );
    (void)(res_size); assert(res_size < 30);

    return varg( buffer, '.', i2s(ms, 3) ).str();

//    auto time = _cstyle_time;
//    return varg( year(),                "-",
//                 i2s(time->tm_mon + 1), "-", // months since January 0-11
//                 i2s(time->tm_mday),    "/",
//                 i2s(time->tm_hour),    ":",
//                 i2s(time->tm_min),     ":",
//                 i2s(time->tm_sec),     ".",
    //                 i2s(ms, 3) ).str();
}
//=======================================================================================
string VDateTime::str_date() const
{
    auto y = year();
    return varg (y, "-")
                .with_zeroes(_cstyle_time->tm_mon + 1, 2)("-")
                .with_zeroes(_cstyle_time->tm_mday, 2);
}
//=======================================================================================
string VDateTime::str_time() const
{
    auto h = hour();
    return varg( h, "-")
                 .with_zeroes(_cstyle_time->tm_min, 2)("-")
                 .with_zeroes(_cstyle_time->tm_sec, 2);
}
//=======================================================================================
int VDateTime::year() const
{
    _set_cstyle_time();
    return _cstyle_time->tm_year + 1900;
}
//=======================================================================================
int VDateTime::hour() const
{
    _set_cstyle_time();
    return _cstyle_time->tm_hour;
}
//=======================================================================================
VDateTime VDateTime::now()
{
    return VDateTime( system_clock::now() );
}

VDateTime VDateTime::from_time_t( time_t t )
{
    return VDateTime( chrono::seconds(t) );
}
//=======================================================================================
bool VDateTime::set_system_time() const
{
    struct timeval  cur_sys_time;
    struct timezone cur_sys_zone;

    if ( gettimeofday(&cur_sys_time, &cur_sys_zone) != 0 )
    {
        return false;
    }

    struct timeval  new_sys_time;

    new_sys_time.tv_sec = seconds();
    new_sys_time.tv_usec = microseconds() % 1000000;

    return 0 == settimeofday( &new_sys_time, &cur_sys_zone );
}
//=======================================================================================
bool VDateTime::operator <(const VDateTime &rhs) const
{
    return _timestamp < rhs._timestamp;
}
//=======================================================================================
bool VDateTime::operator >(const VDateTime &rhs) const
{
    return _timestamp > rhs._timestamp;
}
//=======================================================================================
VDateTime::time_point_t::duration VDateTime::duration() const
{
    return _timestamp.time_since_epoch();
}
//=======================================================================================
int64_t VDateTime::seconds() const
{
    return duration_cast<chrono::seconds>(_timestamp.time_since_epoch()).count();
}
//=======================================================================================
int64_t VDateTime::milliseconds() const
{
    return duration_cast<chrono::milliseconds>(_timestamp.time_since_epoch()).count();
}
//=======================================================================================
int64_t VDateTime::microseconds() const
{
    return duration_cast<chrono::microseconds>(_timestamp.time_since_epoch()).count();
}
//=======================================================================================
int64_t VDateTime::nanoseconds() const
{
    return duration_cast<chrono::nanoseconds>(_timestamp.time_since_epoch()).count();
}
//=======================================================================================


VDateTime operator -(const VDateTime &lhs, const VDateTime &rhs)
{
    return VDateTime( VDateTime::time_point_t(lhs.time_point() - rhs.time_point()) );
}
