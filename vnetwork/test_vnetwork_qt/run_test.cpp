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
    //VIpAddress
    sock.connect_to_host( "192.168.0.65", 2345 );

    vdeb << "before polling";
    app.poll();
    vdeb <<"after epol";
    return 0;
}
