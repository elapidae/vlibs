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


#include "vlog_pretty.h"
#include "vudpsocket.h"
#include "vapplication.h"
#include "vsyssignal.h"
#include "vtimer.h"
#include "vipaddress.h"
#include "vtcpserver.h"
#include "vtcpsocket.h"

using namespace std;


class VNetwork_Test: public testing::Test
{};

//=======================================================================================
TEST_F( VNetwork_Test, set_random )
{
    srandom( VTimePoint::now().microseconds().count() );
}
//=======================================================================================
TEST_F( VNetwork_Test, vip_address )
{
    VIpAddress a1( "1:2:3:4:5:6:7:8" );
    EXPECT_TRUE( (a1.str() == "1:2:3:4:5:6:7:8") );

    VIpAddress a2( "127.0.0.1" );
    EXPECT_TRUE( (a2.str() == "127.0.0.1") );

    EXPECT_TRUE( (VIpAddress("17:0:0:0::18").str() == "17::18") );

    EXPECT_TRUE( (VIpAddress("1.2.3.4").str() == "1.2.3.4") );

    EXPECT_ANY_THROW( (VIpAddress("1.2.3.256").str()) );
}
//=======================================================================================
TEST_F( VNetwork_Test, dev_loopback_tcp )
{
    VApplication app;

    VTcpServer serv;
    vdeb << VIpAddress::loopback_ip6();
    serv.listen( VIpAddress::loopback_ip6(), 0 );
    vdeb << serv.address() << ":" << serv.port();

    VTcpSocket sock;
    sock.connect_to_host( VIpAddress::loopback_ip6(), serv.port() );

    sock.socket_connected.connect( []()
    {
        vdeb << "Socket has connected...!!!";
    });
    sock.socket_disconnected.connect( []()
    {
        vdeb << "Socket has DISconnected...!!!";
    });

    app.poll();
}
//=======================================================================================

//TEST_F( VNetwork_Test, dev_udp )
//{
//    VApplication app;

//    VUdpSocket s1;
//    s1.ready_read.connect( [&](){ vdeb << s1.receive(); });
//    s1.bind_any(12345); // port number

//    VTimer timer;
//    timer.timeout.connect( [](int c) { vdeb << "timeout " << c; });
//    timer.start( 40ms );

//    VSysSignal::watch( [&]() { app.stop(); });  // Ctrl+C
//    app.poll();

//    //EXPECT_EQ();
//}
//=======================================================================================

//=======================================================================================
