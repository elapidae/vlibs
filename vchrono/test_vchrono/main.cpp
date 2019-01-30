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


#include <iostream>
#include "gtest/gtest.h"


#include "vtimepoint.h"
#include "vtimemeter.h"
#include "vlog_pretty.h"
#include <list>
#include <deque>
#include "vstring.h"

//

using namespace std;
using namespace std::chrono;


class VChrono_Test: public testing::Test
{};

//=======================================================================================
TEST_F( VChrono_Test, set_random )
{
    srandom( VTimePoint::now().microseconds().count() );
}
//=======================================================================================
TEST_F( VChrono_Test, dev_timemeter )
{
    VTimeMeter meter;
    usleep(2000);
    vdeb << "e" << meter.elapsed().us();
    usleep(2000);
    vdeb << "r" << meter.restart().us();
    usleep(2000);
    vdeb << "p" << meter.pause().us();
    usleep(2000);
    vdeb << "p" << meter.pause().us();
    usleep(2000);
    vdeb << "p" << meter.pause().us();
    usleep(2000);
    vdeb << "u" << meter.unpause().us();
    usleep(2000);
    vdeb << "u" << meter.unpause().us();
    usleep(2000);
    vdeb << "u" << meter.unpause().us();
    usleep(2000);
    vdeb << "u" << meter.unpause().us();
    usleep(2000);
    vdeb << "u" << meter.unpause().us();
    usleep(2000);
    vdeb << "r" << meter.restart().us();
    usleep(2000);
    vdeb << "r" << meter.restart().us();
    usleep(2000);
    vdeb << "r" << meter.restart();
    usleep(2000);
    vdeb << "r" << meter.restart();
    usleep(2000);
    vdeb << "r" << meter.restart();
    usleep(2000);
    vdeb << "r" << meter.restart();
    usleep(2000);
    vdeb << "r" << meter.restart();
    //EXPECT_EQ();
}
//=======================================================================================
template<typename T>
static T reverse_as_ptr(T val)
{
    char* ch = static_cast<char*>( static_cast<void*>(&val) );
    constexpr auto tsize = sizeof(T);
    switch( tsize )
    {
    case 8: std::swap( ch[3], ch[tsize-4] );
            std::swap( ch[2], ch[tsize-3] );
    case 4: std::swap( ch[1], ch[tsize-2] );
    case 2: std::swap( ch[0], ch[tsize-1] );
    }
    return  val;
}
//=======================================================================================
template<typename T>
static T reverse_as_std(T val)
{
    char* ch = static_cast<char*>( static_cast<void*>(&val) );
    constexpr auto tsize = sizeof(T);
    std::reverse( ch, ch + tsize );
    return  val;
}
//=======================================================================================
TEST_F( VChrono_Test, dev_meter_reverse )
{
    VTimeMeter ptr_meter( VTimeMeter::Stopped );
    VTimeMeter std_meter( VTimeMeter::Stopped );
    VTimeMeter str_meter( VTimeMeter::Stopped );

    int circles = 1e6;
    for ( int i = 0; i < circles; ++i )
    {
        float  f = i * 13.5f;
        double d = i * 123.8;
        uint64_t u64 = uint64_t(i);
        int16_t  i16 = rand();

        auto f1 = f;
        auto d1 = d;
        auto u1 = u64;
        auto i1 = i16;

        std_meter.unpause();
            f1 = reverse_as_std( f1 );
            d1 = reverse_as_std( d1 );
            u1 = reverse_as_std( u1 );
            i1 = reverse_as_std( i1 );
        std_meter.pause();

        ptr_meter.unpause();
            f1 = reverse_as_ptr( f1 );
            d1 = reverse_as_ptr( d1 );
            u1 = reverse_as_ptr( u1 );
            i1 = reverse_as_ptr( i1 );
        ptr_meter.pause();

        EXPECT_EQ( f,   f1 );
        EXPECT_EQ( d,   d1 );
        EXPECT_EQ( u64, u1 );
        EXPECT_EQ( i16, i1 );

        VString str;
        str.append_BE(f1)
           .append_BE(d1)
           .append_BE(u1)
           .append_BE(i1);
        auto view = str.forward_view();

        str_meter.unpause();
            f   = view.take_float_BE();
            d   = view.take_double_BE();
            u64 = view.take_u64_BE();
            i16 = view.take_i16_BE();
        str_meter.pause();

        EXPECT_EQ( f,   f1 );
        EXPECT_EQ( d,   d1 );
        EXPECT_EQ( u64, u1 );
        EXPECT_EQ( i16, i1 );
    }
    vdeb <<   "PTR TIME:" << ptr_meter.elapsed()
         << ", STD TIME:" << std_meter.elapsed()
         << ", CUR STR TIME:" << str_meter.elapsed();
}
//=======================================================================================
TEST_F( VChrono_Test, creations )
{
    (void)VTimePoint();
    (void)VSystemTimePoint();
    (void)VSteadyTimePoint();
    (void)VHighResolutionTimePoint();
}
//=======================================================================================
