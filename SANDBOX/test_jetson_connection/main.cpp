#include "mainwindow.h"
#include <QApplication>

#include <QTcpSocket>
#include "vlog_qt.h"
#include <QTimer>
#include <QBuffer>
#include "vimagewidget.h"
#include "vstring.h"

#include <QPainter>
#include <QDateTime>

#include <gst/gst.h>
#include <gst/video/videooverlay.h>


static auto constexpr host = "10.0.1.250";
//static auto constexpr host = "192.168.0.160";
//static auto constexpr host = "127.0.0.1";
static auto constexpr port = 4951;
//static auto constexpr port = 722;


int main(int argc, char *argv[])
{
    gst_init (&argc, &argv);

    QApplication a(argc, argv);
    VImageWidget w;
    w.show();

    GstElement *pipeline = gst_parse_launch ("playbin uri=rtsp://admin:12345@10.0.1.250:1554", NULL);


    WId xwinid = w.winId();
    //this is the call to overlay the gstreamer's output to the Qt Widgets...
    gst_video_overlay_set_window_handle( GST_VIDEO_OVERLAY(pipeline), xwinid);


    // run the pipeline
    GstStateChangeReturn sret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
    if (sret == GST_STATE_CHANGE_FAILURE)
    {
        gst_element_set_state (pipeline, GST_STATE_NULL);
        gst_object_unref (pipeline);

        return 1;
    }

    return a.exec();
//    QImage img;
//    //auto ok = img.load("/home/el/team-working.png");
//    auto ok = img.load("/home/el/1.png");
//    Q_ASSERT(ok);

//    QTimer timer2;
//    timer2.start(40);
//    QObject::connect( &timer2, &QTimer::timeout, [&]()
//    {
//        static int cnt = 0;
//        vdeb << ++cnt;
//        QImage im2 = img;
//        im2.detach();
//        {
//            QPainter p( &im2 );
//            auto dt = QDateTime::currentDateTime();
//            p.scale( 3, 3 );
//            p.drawText( 20, 70, dt.toString("yyyy-MM-dd hh:mm:ss.zzz") );
//        }

//        w.set_image( im2 );
//    });
//    return a.exec();


//    QTcpSocket s;

//    QObject::connect( &s, &QTcpSocket::connected, [&]()
//    {
//        vdeb << "Connected!!!";
//        s.write( "2018-12-04 -- Hello world!" );
//    });

//    QByteArray buffer;
//    int32_t sz = 0;
//    QObject::connect( &s, &QTcpSocket::readyRead, [&]()
//    {
//        auto rall = s.readAll();
//        buffer += rall;
//        //vdeb << "received " << rall.count() << buffer.count();
//        if (sz == 0)
//        {
//            if ( buffer.size() < int(sizeof(sz)) ) return;
//            {
//                VString sz_str(buffer.data(), buffer.data() + sizeof(sz) );
//                auto usz = sz_str.front_LE<uint32_t>();
//                sz = int(usz);
//                vdeb << "NEW SIZE = " << sz;
//            }
//            auto bsz = buffer.size();
//            buffer.remove(0, sizeof(sz));
//            Q_ASSERT( buffer.size() + int(sizeof(sz)) == bsz );
//        }

//        if ( buffer.size() < sz ) return;

//        auto cur_jpg = buffer.left( sz );
//        buffer.remove( 0, sz );
//        sz = 0;

//        VString l{cur_jpg.begin(), cur_jpg.begin() + 16};
//        VString r{cur_jpg.end() - 16, cur_jpg.end()};
//        vdeb << "cur_jpg.sz =" << cur_jpg.size();
//        vdeb << "B" << l.to_hex();
//        vdeb << "E" << r.to_hex();
//        //vdeb << "after rem left part, buf.sz =" << buffer.size();
//        //Q_ASSERT( cur_jpg.size() + buffer.size() == sz );

//        QImage img;
//        bool ok;
//        {
//            QBuffer buf( &cur_jpg );
//            ok = img.load( &buf, "JPEG" );
//        }
//        s.write( VTimePoint::now().str_datetime_zzz().c_str() );
//        if ( !ok )
//        {
//            vdeb << "Bad JPEG!";
//            return;
//        }
//        w.set_image( img );
//    });



//    QTimer timer;
//    timer.start(400);
//    int cnt = 0;
//    QObject::connect( &timer, &QTimer::timeout, [&]()
//    {
//        if ( s.state() == QAbstractSocket::UnconnectedState )
//        {
//            s.connectToHost( host, port );
//            vdeb.nospace() << "About to connect to " << host << ":" << port
//                           << ", try " << ++cnt;
//        }
//    });

//    return a.exec();
}
