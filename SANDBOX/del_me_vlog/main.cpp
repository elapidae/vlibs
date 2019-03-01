
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

#include "vlog.h"
#include "vfilelog.h"
#include "vtimepoint.h"

#include "vtcpsocket.h"
#include "vapplication.h"

int main( int argc, char **argv )
{
    VApplication app;

    VTcpSocket tcp;
    tcp.connect_to_host("127.0.0.1", 1234);

    tcp.ready_read.connect([&]()
    {
        vdeb << tcp.receive_all();
    });

    app.poll();
    return 0;

    //cout << system_clock::now();
    cout << VTimePoint::now() << endl;

//    VLogger::clear_executers();

    VFileLog_Leveled leveled( vcat(argv[0], ".conf"), 10000, 3 );
    leveled.register_self();

    VFileLog_Shared shared( vcat(argv[0], ".shared.conf"), 10000, 3 );
    shared.register_self();

//    VLogger::add_executer( [&](const VLogEntry &e)
//    {
//        cout << e.timestamp() << endl;
//    });

//    VLogger::add_executer( [&](const VLogEntry& e)
//    {

//    });

    vtrace   << "Hello World!";
    vdeb     << "Hello World!";
    vrunlog  << "Hello World!";
    vwarning << "Hello World!";
    vfatal   << "Hello World!";

    return 0;
}
