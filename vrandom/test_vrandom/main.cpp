#include <iostream>
#include "gtest/gtest.h"


#include <ctime>
#include "vlog_pretty.h"
#include "vrandom.h"

using namespace std;


class VRandom_Test: public testing::Test
{};

//=======================================================================================
TEST_F( VRandom_Test, simple )
{
    VRandom_mt19937 mt;
    vdeb << mt.u32() << mt.u64() << mt();
}

//=======================================================================================
