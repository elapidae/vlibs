#include "gtest/gtest.h"

#include "vinterval.h"
#include "vlog_pretty.h"

//=======================================================================================

class VInterval_Test: public testing::Test
{
protected:
//    const float eps = 0.00001;
};

//=======================================================================================

TEST_F(VInterval_Test, simples)
{
    VIntervalD id{ {1,0}, {2,1} };
    EXPECT_TRUE( id.angle_degrees() == 45.f );

    EXPECT_TRUE( !id.is_normal( {1,2.01} )  );
    EXPECT_TRUE( id.is_normal( {1,2} )      );
    EXPECT_TRUE( id.is_normal( {0,1} )      );
    EXPECT_TRUE( !id.is_normal( {0,0.99} )  );
}

//=======================================================================================

// TODO: More and more tests!
