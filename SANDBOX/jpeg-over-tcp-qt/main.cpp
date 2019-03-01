#include <QCoreApplication>

#include <zcm/zcm-cpp.hpp>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include "vzcm_subscriber.h"
#include "ZcmCameraBaslerJpegFrame.hpp"
#include "qt_vinvoke.h"
#include "vlog_qt.h"

static constexpr auto z_target  = "udpm://239.255.76.67:7667?ttl=10";
static constexpr auto z_channel = "FRZcmCameraBaslerJpegFrame";


zcm::ZCM *zcm_ptr = nullptr;
QTcpSocket *socket = nullptr;


class ZThread : public QThread
{
    void run() override
    {
        zcm_ptr = new zcm::ZCM{z_target};
        VZCM_Subscriber<ZcmCameraBaslerJpegFrame> subs( zcm_ptr, z_channel );
        subs.received.connect( [&](const ZcmCameraBaslerJpegFrame& jpg)
        {
            auto cptr = (const char*)jpg.jpeg.data();
            QByteArray jarr(cptr, jpg.jpeg.size());
            jarr.detach();

            if (socket)
                qt::vinvoke_queue( socket, "write", Q_ARG(QByteArray,jarr) );
//            app.invoke( [&,jstr]()
//            {
//                if ( !socket ) return;

//                VString sz;
//                uint32_t size = jstr.size();
//                sz.append_LE( size );
//                socket->send( sz );
//                socket->send( jstr );
//                vdeb << "Sended " << size;
//                VString l{jstr.begin(), jstr.begin() + 16};
//                VString r{jstr.end() - 16, jstr.end()};
//                vdeb << "B" << l.to_hex();
//                vdeb << "E" << r.to_hex();
//            });
        });
        zcm_ptr->run();
    }
};



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTcpServer server;
    auto ok = server.listen( QHostAddress::Any, 4951 );
    Q_ASSERT(ok);
    vdeb << "listened" << server.serverAddress().toString() << server.serverPort();

    QObject::connect( &server, &QTcpServer::newConnection, [&]()
    {
        vdeb << "new connection...";
        if (socket) { socket->deleteLater(); socket = nullptr; }
        socket = server.nextPendingConnection();
    });

    ZThread th;
    th.start();

    return a.exec();
}
