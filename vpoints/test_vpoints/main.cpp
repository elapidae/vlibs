#include <iostream>
#include "gtest/gtest.h"


#include "vpoints.h"
#include "vlog_pretty.h"


using namespace std;


class VPoints_Test: public testing::Test
{};

//=======================================================================================
TEST_F( VPoints_Test, set_random )
{
    srandom( VTimePoint::now().microseconds().count() );
}
//=======================================================================================
TEST_F( VPoints_Test, simple_use )
{
    VPointF p1 {3, 4};
    EXPECT_EQ( p1.distance(), 5 );

    using PointD = VPoint<double>;
    PointD dp {3, 4};
    EXPECT_EQ( dp.distance(), 5 );

    PointD dr { random(), random() };

    auto diff = dp - dr;
    diff += dr;
    EXPECT_EQ( diff, dp );

    VPoint<int> ip;
    EXPECT_EQ( ip, ip );
}

//=======================================================================================
//=======================================================================================


