#include <iostream>
#include "gtest/gtest.h"


#include "vlog_pretty.h"
#include "vudpsocket.h"
#include "vapplication.h"
#include "vsyssignal.h"
#include "vtimer.h"


using namespace std;


class VNetwork_Test: public testing::Test
{};

//=======================================================================================
TEST_F( VNetwork_Test, set_random )
{
    srandom( VTimePoint::now().microseconds().count() );
}
//=======================================================================================
TEST_F( VNetwork_Test, dev_udp )
{    
    VApplication app;

    VUdpSocket s1;
    s1.ready_read.connect( [&](){ vdeb << s1.receive(); });
    s1.bind_any(12345);

    VTimer timer;
    timer.timeout.connect( [](int c) { vdeb << "timeout " << c; });
    timer.start( 40ms );

    VSysSignal::watch( [&]() { app.stop(); });
    app.poll();

    //EXPECT_EQ();
}
//=======================================================================================

//=======================================================================================
