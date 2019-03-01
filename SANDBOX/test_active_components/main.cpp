#include <iostream>

#include "vapplication.h"
#include "vudpsocket.h"
#include "vtimer.h"
#include "vlog.h"

static constexpr auto port = 12345;

int main( int argc, char **argv )
{
    VApplication app( argc, argv );

    VUdpSocket udp;
    udp.bind_any( port );

    udp.ready_read.connect( [&]()
    {
        vdeb << VTimePoint::now() << udp.receive();
    });

    VTimer timer;
    timer.timeout = [&]()
    {
        static int counter = 0;
        udp.send_to( vcat("hello world! ", ++counter, " times"), "127.0.0.1", port );
    };
    timer.start( std::chrono::milliseconds(500) );
    app.poll();
    return 0;
}
