#include <iostream>

#include <zcm/zcm-cpp.hpp>
#include "vtcpsocket.h"
#include "vtcpserver.h"
#include "vtimer.h"
#include "vlog_pretty.h"
#include "vapplication.h"

#include "vthread.h"
#include "cpp_types_basler/ZcmCameraBaslerJpegFrame.hpp"
#include "vzcm_subscriber.h"

static constexpr auto z_target  = "udpm://239.255.76.67:7667?ttl=10";
static constexpr auto z_channel = "FRZcmCameraBaslerJpegFrame";

static constexpr auto destaddr = "192.168.0.90";
static constexpr auto port = 4951;


using namespace std;
int main_client();
int main_server();

int main()
{
    return main_server();
    return main_client();
}

int main_server()
{
    VApplication app;

    VTcpServer server;
    server.listen_any( port );

    std::shared_ptr<VTcpSocket> socket;
    server.peer_connected.connect( [&](VTcpSocket::Peer peer)
    {
        socket.reset( new VTcpSocket(&peer) );
        socket->ready_read.connect( [&]()
        {
            auto msg = socket->receive_all();
            vdeb << msg;
        });
        socket->socket_disconnected.connect([&]()
        {
            VApplication::app()->invoke( [&](){ socket.reset(); } );
        });
    });

    zcm::ZCM *zcm = nullptr;
    VThread th;
    th.finvoke( [&]()
    {
        zcm = new zcm::ZCM{z_target};
        VZCM_Subscriber<ZcmCameraBaslerJpegFrame> subs( zcm, z_channel );
        subs.received.connect( [&](const ZcmCameraBaslerJpegFrame& jpg)
        {
            std::string jstr{ jpg.jpeg.begin(), jpg.jpeg.end() };
            app.invoke( [&,jstr]()
            {
                if ( !socket ) return;

                VString sz;
                uint32_t size = jstr.size();
                sz.append_LE( size );
                socket->send( sz );
                socket->send( jstr );
                vdeb << "Sended " << size;
                VString l{jstr.begin(), jstr.begin() + 16};
                VString r{jstr.end() - 16, jstr.end()};
                vdeb << "B" << l.to_hex();
                vdeb << "E" << r.to_hex();
            });
        });
        zcm->run();
    });

    app.poll();

    zcm->stop();
    return 0;
}


int main_client()
{
    VApplication app;
    VTcpSocket socket;
    int cnt = 0;

    socket.socket_connected.connect( []()
    { vdeb << "GOTCHA!"; });

    socket.socket_disconnected.connect( [&]()
    { vdeb << "disconnected :(" << ++cnt; });

    VTimer timer;
    timer.start( 400ms );
    timer.timeout.connect( [&](int)
    {
        if ( !socket.is_connected() )
        {
            socket.connect_to_host( destaddr, port );
            return;
        }
        socket.send( vcat("Hello world! ", ++cnt).str() );
    });

    app.poll();
    return 0;
}
