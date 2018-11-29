
#include "main.cpp"


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#include <new>


#include "vtcpsocket.h"

int main_1()
{
    //LOG4CPLUS_DEBUG_FMT(IsdModule::ModuleLogger::logger(), "Socket closed: %d", fd_socket);
    VApplication app;

    VTcpSocket sock;
    sock.socket_connected.connect( [&]()
    {
        vdeb << "connected signal";
        sock.send( "Hello world!" );
    });
    sock.ready_read.connect( [&]()
    {
        auto msg = sock.receive_all();
        vdeb << "Received:" << msg;
        auto num = msg.text_to_any<int>();
        sock.send( VString::any_to_text(++num) );
    });
    //sock.connect_to_host( "127.0.0.1", 2345 );
    sock.connect_to_host( "192.168.0.65", 2345 );

    vdeb << "before polling";
    app.poll();
    vdeb <<"after epol";
    return 0;
}
