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


#include "gtest/gtest.h"
#include "vpoints.h"

#include "vlog_pretty.h"

//=======================================================================================

class VPoints_Test: public testing::Test
{
protected:
//    const float eps = 0.00001;
};

//=======================================================================================

TEST_F(VPoints_Test, quarters)
{
    //  Убеждаемся что углы оказываются в правильных четвертях.
    {
        VPointF p1( +1, +2 );
        VPointF p2( -1, +2 );
        VPointF p3( -1, -2 );
        VPointF p4( +1, -2 );

    //    vdeb << p1 << p1.angle() << p1.angle_degrees();
    //    vdeb << p2 << p2.angle() << p2.angle_degrees();
    //    vdeb << p3 << p3.angle() << p3.angle_degrees();
    //    vdeb << p4 << p4.angle() << p4.angle_degrees();

        EXPECT_TRUE( p1.angle_degrees() >    0  && p1.angle_degrees() <  90 );
        EXPECT_TRUE( p2.angle_degrees() >   90  && p2.angle_degrees() < 180 );
        EXPECT_TRUE( p3.angle_degrees() > -180  && p3.angle_degrees() < -90 );
        EXPECT_TRUE( p4.angle_degrees() >  -90  && p4.angle_degrees() <   0 );
    }
    {
        VPointF axis1( +1, 0 );
        VPointF axis2( 0, +2 );
        VPointF axis3( -1, 0 );
        VPointF axis4( 0, -2 );

//        vdeb << axis1 << axis1.angle() << axis1.angle_degrees();
//        vdeb << axis2 << axis2.angle() << axis2.angle_degrees();
//        vdeb << axis3 << axis3.angle() << axis3.angle_degrees();
//        vdeb << axis4 << axis4.angle() << axis4.angle_degrees();

        //  Здесь проверяются не в окрестностях, т.к. в точках нули заданы явно.
        EXPECT_TRUE( axis1.angle_degrees() == 0.f   );
        EXPECT_TRUE( axis2.angle_degrees() == 90.f  );
        EXPECT_TRUE( axis3.angle_degrees() == 180.f );
        EXPECT_TRUE( axis4.angle_degrees() == -90.f );
    }
}

//=======================================================================================

TEST_F(VPoints_Test, equals)
{
    // Важен факт сравнения.
    VPointF p1 ( 1, 2 );
    VPointF p1_( 1, 2 );
    VPointF p2 ( 0.9f, 2 );

    EXPECT_EQ( p1, p1_ );
    EXPECT_NE( p1, p2  );

    VPoint<int> i1 {1,2};
    VPoint<int> i1_{1,2};
    VPoint<int> i2 {0,2};

    EXPECT_EQ( i1, i1_ );
    EXPECT_NE( i1, i2  );
}

//=======================================================================================

TEST_F(VPoints_Test, avg_center)
{
    VPointF::Vector v
    {
        {1,1},
        {3,3},
        {5,5}
    };

    auto c = v.average_center();
    VPointF cc{3,3};
    EXPECT_EQ( c, cc );
}

//=======================================================================================
