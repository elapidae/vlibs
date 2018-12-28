#include <iostream>
#include "gtest/gtest.h"


#include "vapplication.h"
#include "vlog_pretty.h"
#include "vtimer.h"


//  11.12.2018  by Elapidae
//  Ничего, кроме сборки, не проверяется! Сейчас сделано для демонстрации.

using namespace std;


class VTimer_Test: public testing::Test
{};

//=======================================================================================
TEST_F( VTimer_Test, set_random )
{
    srandom( VTimePoint::now().microseconds().count() );
}
//=======================================================================================
TEST_F( VTimer_Test, dev_polling )
{
    VApplication app;

    vdeb << "==========================================================================";

    VTimer timer1;
    timer1.timeout.connect( [&]()
    {
        vdeb << "Single shot timer, about to stop.";
        VApplication::app()->stop();    // Singleton for once VApplication instance,
                                        // like as Qt "qApp" macros.
    });
    timer1.singleshot( chrono::seconds(1) );


    VTimer timer2;
    timer2.timeout_count.connect( [](int cnt)
    {
        vdeb << "quick timer, count of episodes =" << cnt;
    });
    //timer2.start( chrono::microseconds(10) ); // Будет в количестве давать 1, скучно...
    timer2.start( chrono::nanoseconds(10) );

    app.poll();
    vdeb << "==========================================================================";

    //EXPECT_EQ();
}
//=======================================================================================

//=======================================================================================


