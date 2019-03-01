#include "test_net.h"


#include "vlog.h"

test_net::test_net()
{
    t1.timeout = [this]() { u1.send_to( vcat(++pk," first"),  "127.0.0.1", 2020 ); };
    t2.timeout = [this]() { u2.send_to( vcat(++pk," second"), "127.0.0.1", 2019 ); };

    u1.ready_read.connect( [this]()
    {
        vdeb << u1.receive();
    });
    u2.ready_read.connect( [this]()
    {
        vdeb << u2.receive();
    });

    u1.bind_any( 2019 );
    u2.bind_any( 2020 );

    t1.start( std::chrono::milliseconds(1000) );
    t2.start( std::chrono::milliseconds(1500) );
}
