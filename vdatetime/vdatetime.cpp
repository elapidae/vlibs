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
    auto ms = duration_cast<milliseconds>(tse).count() % 1000;

    _set_cstyle_time();


    char buffer[32];
    auto res_size = strftime( buffer, sizeof buffer, "%F %T", _cstyle_time );
    assert(res_size < 30);

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
int VDateTime::year() const
{
    _set_cstyle_time();
    return _cstyle_time->tm_year + 1900;
}
//=======================================================================================
VDateTime VDateTime::now()
{
    return VDateTime( system_clock::now() );
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
int64_t VDateTime::seconds() const
{
    return duration_cast<chrono::seconds>(_timestamp.time_since_epoch()).count();
}
//=======================================================================================
int64_t VDateTime::microseconds() const
{
    return duration_cast<chrono::microseconds>(_timestamp.time_since_epoch()).count();
}
//=======================================================================================
