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
#include "../vtransformation.h"


class TransformTest: public testing::Test
{

protected:
    const float eps = 0.00001;
};

TEST_F(TransformTest, null_matrix)
{
    TransformationUtils t_u(0,0,0,0,0);

    float x = 0, y = 0, z = 0;

    t_u.shift(&x, &y);
    EXPECT_FLOAT_EQ(x, 0);
    EXPECT_FLOAT_EQ(y, 0);

    t_u.shift(&x, &y, &z);
    EXPECT_FLOAT_EQ(x, 0);
    EXPECT_FLOAT_EQ(y, 0);
    EXPECT_FLOAT_EQ(z, 0);

    t_u.route_angle_y(&x, &z);
    EXPECT_FLOAT_EQ(x, 0);
    EXPECT_FLOAT_EQ(z, 0);

    t_u.route_angle_z(&x, &y);
    EXPECT_FLOAT_EQ(x, 0);
    EXPECT_FLOAT_EQ(y, 0);
}


TEST_F(TransformTest, shifts)
{
    TransformationUtils t_1(0.4,0.002,0.0017, 0.0, 0.0);

    float x = 0, y = 0, z = 0;

    t_1.shift(&x, &y);

    EXPECT_NEAR(x, 0.4, eps);
    EXPECT_NEAR(y, 0.002, eps);

    x = -2.0, y = -2.0, z = -2.0;
    t_1.shift(&x, &y, &z);
    EXPECT_NEAR(x, -1.6, eps);
    EXPECT_NEAR(y, -1.998, eps);
    EXPECT_NEAR(z, -1.9983, eps);

}

TEST_F(TransformTest, route_z)
{
    float x = 0, y = 0, z = 0;

    TransformationUtils t_1(0, 0, 0, 0.0, 90.0);

    t_1.route_angle_z(&x, &y);
    EXPECT_NEAR(x, 0, eps);
    EXPECT_NEAR(y, 0, eps);
    EXPECT_NEAR(z, 0, eps);

    x = 10, y = 10;
    t_1.route_angle_z(&x, &y);
    EXPECT_NEAR(x, -10.0, eps);
    EXPECT_NEAR(y, 10.0, eps);
    EXPECT_NEAR(z, 0, eps);

    x = -10, y = -10;
    t_1.route_angle_z(&x, &y);
    EXPECT_NEAR(x, 10.0, eps);
    EXPECT_NEAR(y, -10.0, eps);
    EXPECT_NEAR(z, 0, eps);


    TransformationUtils t_2(0, 0, 0, 0.0, -90.0);

    x = 10, y = 10;
    t_2.route_angle_z(&x, &y);
    EXPECT_NEAR(x, 10.0, eps);
    EXPECT_NEAR(y, -10.0, eps);
    EXPECT_NEAR(z, 0, eps);

    x = -10, y = -10;
    t_2.route_angle_z(&x, &y);
    EXPECT_NEAR(x, -10.0, eps);
    EXPECT_NEAR(y, 10.0, eps);
    EXPECT_NEAR(z, 0, eps);


    TransformationUtils t_3(0, 0, 0, 0.0, 360.0);

    x = 10, y = 10;
    t_3.route_angle_z(&x, &y);
    EXPECT_NEAR(x, 10.0, eps);
    EXPECT_NEAR(y, 10.0, eps);
    EXPECT_NEAR(z, 0, eps);

    x = -10, y = -10;
    t_3.route_angle_z(&x, &y);
    EXPECT_NEAR(x, -10.0, eps);
    EXPECT_NEAR(y, -10.0, eps);
    EXPECT_NEAR(z, 0, eps);

    TransformationUtils t_4(0, 0, 0, 0.0, -360.0);

    x = 10, y = 10;
    t_4.route_angle_z(&x, &y);
    EXPECT_NEAR(x, 10.0, eps);
    EXPECT_NEAR(y, 10.0, eps);
    EXPECT_NEAR(z, 0, eps);

    x = -10, y = -10;
    t_4.route_angle_z(&x, &y);
    EXPECT_NEAR(x, -10.0, eps);
    EXPECT_NEAR(y, -10.0, eps);
    EXPECT_NEAR(z, 0, eps);



    TransformationUtils t_5(0, 0, 0, 0.0, 1.8);

    x = 10, y = 20;
    t_5.route_angle_z(&x, &y);
    EXPECT_NEAR(x, 9.36685, eps);
    EXPECT_NEAR(y, 20.30423, eps);
    EXPECT_NEAR(z, 0, eps);

    x = 10, y = -20;
    t_5.route_angle_z(&x, &y);
    EXPECT_NEAR(x, 10.62328, eps);
    EXPECT_NEAR(y, -19.67602, eps);
    EXPECT_NEAR(z, 0, eps);


    TransformationUtils t_6(0, 0, 0, 0.0, -1.8);

    x = 10, y = 20;
    t_6.route_angle_z(&x, &y);
    EXPECT_NEAR(x, 10.62328, eps);
    EXPECT_NEAR(y, 19.67602, eps);
    EXPECT_NEAR(z, 0, eps);

    x = 10, y = -20;
    t_6.route_angle_z(&x, &y);
    EXPECT_NEAR(x, 9.36685, eps);
    EXPECT_NEAR(y, -20.30423, eps);
    EXPECT_NEAR(z, 0, eps);

}




TEST_F(TransformTest, route_y)
{
    float x = 0, y = 0, z = 0;

    TransformationUtils t_1(0, 0, 0, 90.0, 0.0);

    x = 10, z = 10;
    t_1.route_angle_y(&x, &z);
    EXPECT_NEAR(x, 10.0, eps);
    EXPECT_NEAR(y, 0.0, eps);
    EXPECT_NEAR(z, -10.0, eps);

    x = -10, z = -10;
    t_1.route_angle_y(&x, &z);
    EXPECT_NEAR(x, -10.0, eps);
    EXPECT_NEAR(y, 0.0, eps);
    EXPECT_NEAR(z, 10, eps);


    TransformationUtils t_2(0, 0, 0, -90.0, 0.0);

    x = 10, z = 10;
    t_2.route_angle_y(&x, &z);
    EXPECT_NEAR(x, -10.0, eps);
    EXPECT_NEAR(y, 0.0, eps);
    EXPECT_NEAR(z, 10, eps);

    x = -10, z = -10;
    t_2.route_angle_y(&x, &z);
    EXPECT_NEAR(x, 10.0, eps);
    EXPECT_NEAR(y, 0.0, eps);
    EXPECT_NEAR(z, -10.0, eps);


    TransformationUtils t_3(0, 0, 0, 360.0, 0.0);

    x = 10, z = 10;
    t_3.route_angle_y(&x, &z);
    EXPECT_NEAR(x, 10.0, eps);
    EXPECT_NEAR(y, 0.0, eps);
    EXPECT_NEAR(z, 10, eps);

    x = -10, z = -10;
    t_3.route_angle_y(&x, &z);
    EXPECT_NEAR(x, -10.0, eps);
    EXPECT_NEAR(y, 0.0, eps);
    EXPECT_NEAR(z, -10.0, eps);



    TransformationUtils t_4(0, 0, 0, -360.0, 0.0);

    x = 10, z = 10;
    t_4.route_angle_y(&x, &z);
    EXPECT_NEAR(x, 10.0, eps);
    EXPECT_NEAR(y, 0.0, eps);
    EXPECT_NEAR(z, 10.0, eps);

    x = -10, z = -10;
    t_4.route_angle_y(&x, &z);
    EXPECT_NEAR(x, -10.0, eps);
    EXPECT_NEAR(y, 0.0, eps);
    EXPECT_NEAR(z, -10.0, eps);



    TransformationUtils t_5(0, 0, 0, 1.8, 0.0);

    x = 10, z = 20;
    t_5.route_angle_y(&x, &z);
    EXPECT_NEAR(x, 10.62328, eps);
    EXPECT_NEAR(y, 0, eps);
    EXPECT_NEAR(z, 19.67602, eps);

    x = 10, z = -20;
    t_5.route_angle_y(&x, &z);
    EXPECT_NEAR(x, 9.36685, eps);
    EXPECT_NEAR(y, 0, eps);
    EXPECT_NEAR(z, -20.30423, eps);


    TransformationUtils t_6(0, 0, 0, -1.8, 0.0);

    x = 10, z = 20;
    t_6.route_angle_y(&x, &z);
    EXPECT_NEAR(x, 9.36685, eps);
    EXPECT_NEAR(y, 0.0, eps);
    EXPECT_NEAR(z, 20.30423, eps);

    x = 10, z = -20;
    t_6.route_angle_y(&x, &z);
    EXPECT_NEAR(x, 10.62328, eps);
    EXPECT_NEAR(y, 0.0, eps);
    EXPECT_NEAR(z, -19.67602, eps);

}
