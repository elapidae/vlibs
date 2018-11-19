#include <iostream>
#include "gtest/gtest.h"


#include "vapplication.h"
#include "vlog_pretty.h"
#include <list>
#include <deque>


using namespace std;


class VApplication_Test: public testing::Test
{};

//=======================================================================================
TEST_F( VApplication_Test, set_random )
{
    srandom( VTimePoint::now().microseconds().count() );
}
//=======================================================================================
TEST_F( VApplication_Test, simple_args )
{
    //EXPECT_EQ();
}

//=======================================================================================

//=======================================================================================


