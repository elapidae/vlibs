#include <iostream>
#include "gtest/gtest.h"


#include "vapplication.h"
#include "vlog_pretty.h"
#include <list>
#include <deque>

//  На 23-11-2018 Тест реально ничего не проверяет, просто убеждается что все собирается
// и толкает в очередь пробные лямбды.

using namespace std;


class VApplication_Test: public testing::Test
{};

//=======================================================================================
TEST_F( VApplication_Test, set_random )
{
    srandom( VTimePoint::now().microseconds().count() );
}
//=======================================================================================
TEST_F( VApplication_Test, dev_polling )
{
    VApplication app;

    app.invoke( [](int i){ vtrace << i;}, 42 );
    app.invoke( [](int i){ vtrace << i;}, 43 );
    app.invoke( [](int i){ vtrace << i;}, 44 );
    app.invoke( [](int i){ vtrace << i;}, 45 );
    app.invoke( [](int i){ vtrace << i;}, 46 );
    app.invoke( [](int i){ vtrace << i;}, 47 );
    app.invoke( [](int i){ vtrace << i;}, 48 );
    app.invoke( [&](){ vtrace << "stop"; app.stop(); } );
    app.poll();
    //EXPECT_EQ();
}

//=======================================================================================

//=======================================================================================


