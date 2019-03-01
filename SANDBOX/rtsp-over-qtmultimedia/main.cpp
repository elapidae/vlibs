#include <QApplication>

#include <QGLWidget>
#include <QMediaPlayer>
#include <QNetworkRequest>
#include <QVideoWidget>
#include <QGridLayout>
#include <QPainter>
#include <QDateTime>
#include "vlog_qt.h"

#include <QVideoProbe>
#include <QTimer>

#include "vimagewidget.h"
#include "vimage.h"

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

#include "four_images.h"

#include <QFile>
#include <QtAV/QtAV>
#include <QtAV/AVTranscoder.h>
#include <QDir>

#include "vmacroses.h"

int main_qtav(int argc, char *argv[]);
int main_qtav_m2(int argc, char *argv[]);
int main_rtsp(int argc, char *argv[]);



int main(int argc, char *argv[])
{
    return main_rtsp(argc, argv);
    //return main_qtav(argc, argv);
    return main_qtav_m2(argc, argv);
}



using namespace QtAV;

//=======================================================================================
static QImage no_signal( int cnt )
{
    auto w = 1280;
    auto h = 720;
    auto rect = QRect(0,0,w,h);
    QImage res(w, h, QImage::Format_RGB888);
    QPainter p( &res );
    p.setPen( Qt::NoPen);
    p.setBrush( Qt::darkBlue );
    p.drawRect( rect );

    auto font = p.font();
    font.setPixelSize( 60 );
    font.setBold( true );
    p.setFont( font );
    p.setPen( Qt::red );
    p.translate( w/2, h/2);
    p.rotate( -25 );
    rect = QRect(-w/2, -h/2, w, h);
    //p.drawText( rect, Qt::AlignCenter, QString("No signal [%1]").arg(cnt) );
    p.drawLine(-w/2, -h/2, w, h);

    return res;
}
//=======================================================================================


//=======================================================================================
int main_qtav(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug("QtAV simpletranscode");
    qDebug("./simpletranscode -i infile -o outfile [-async] [-c:v video_codec (default: libx264)] [-hwdev dev] [-f format] [-an] [-ss HH:mm:ss.z]");
    qDebug("-an: disable audio");
    qDebug() << "examples:\n"
             << "./simpletranscode -i test.mp4 -o /tmp/test-%05d.png -f image2 -c:v png\n"
             << "./simpletranscode -i test.mp4 -o /tmp/bbb%04d.ts -f segment\n"
             << "./simpletranscode -i test.mp4 -o /tmp/test.mkv\n"
             ;
    if (a.arguments().contains(QString::fromLatin1("-h"))) {
        return 0;
    }
    QString file = QString::fromLatin1("/home/el/test.avi");
    int idx = a.arguments().indexOf(QLatin1String("-i"));
    if (idx > 0)
        file = a.arguments().at(idx + 1);
    QString outFile = QString::fromLatin1("/home/el/trash/out.mp4");
    idx = a.arguments().indexOf(QLatin1String("-o"));
    if (idx > 0)
        outFile = a.arguments().at(idx + 1);
    QDir().mkpath(outFile.left(outFile.lastIndexOf(QLatin1Char('/'))+1));

    QString cv = QString::fromLatin1("libx264");
    idx = a.arguments().indexOf(QLatin1String("-c:v"));
    if (idx > 0)
        cv = a.arguments().at(idx + 1);
    QString ca = QString::fromLatin1("aac");
    idx = a.arguments().indexOf(QLatin1String("-c:a"));
    if (idx > 0)
        ca = a.arguments().at(idx + 1);
    QString fmt;
    idx = a.arguments().indexOf(QLatin1String("-f"));
    if (idx > 0)
        fmt = a.arguments().at(idx + 1);
    QString hwdev;
    idx = a.arguments().indexOf(QLatin1String("-hwdev"));
    if (idx > 0)
        hwdev = a.arguments().at(idx + 1);

    //const bool an = a.arguments().contains(QLatin1String("-an"));
    const bool an = true;

    const bool async = a.arguments().contains(QLatin1String("-async"));
    qint64 ss = 0;
    idx = a.arguments().indexOf(QLatin1String("-ss"));
    if (idx > 0)
        ss = QTime(0, 0, 0).msecsTo(QTime::fromString(a.arguments().at(idx + 1), QLatin1String("HH:mm:ss.z")));
    QVariantHash muxopt, avfopt;
    avfopt[QString::fromLatin1("segment_time")] = 4;
    avfopt[QString::fromLatin1("segment_list_size")] = 0;
    avfopt[QString::fromLatin1("segment_list")] = outFile.left(outFile.lastIndexOf(QLatin1Char('/'))+1).arg(QString::fromLatin1("index.m3u8"));
    avfopt[QString::fromLatin1("segment_format")] = QString::fromLatin1("mpegts");
    muxopt[QString::fromLatin1("avformat")] = avfopt;

    AVPlayer player;
    player.setFile(file);
    player.setFrameRate(10000.0); // as fast as possible. FIXME: why 1000 may block source player?
    player.audio()->setBackends(QStringList() << QString::fromLatin1("null"));

    AVTranscoder avt;
    if (ss > 0)
        avt.setStartTime(ss);
    avt.setMediaSource(&player);
    avt.setOutputMedia(outFile);
    avt.setOutputOptions(muxopt);
    if (!fmt.isEmpty())
        avt.setOutputFormat(fmt); // segment, image2
    if (!avt.createVideoEncoder()) {
        qWarning("Failed to create video encoder");
        return 1;
    }
    VideoEncoder *venc = avt.videoEncoder();
    venc->setCodecName(cv); // "png"
    venc->setBitRate(1024*1024);
    if (!hwdev.isEmpty())
        venc->setProperty("hwdevice", hwdev);
    if (fmt == QLatin1String("image2"))
        venc->setPixelFormat(VideoFormat::Format_RGBA32);
    if (an) {
        avt.sourcePlayer()->setAudioStream(-1);
    } else {
        if (!avt.createAudioEncoder()) {
            qWarning("Failed to create audio encoder");
            return 1;
        }
        AudioEncoder *aenc = avt.audioEncoder();
        aenc->setCodecName(ca);
    }

    QObject::connect(&avt, SIGNAL(stopped()), qApp, SLOT(quit()));
    avt.setAsync(async);
    avt.start(); //start transcoder first
    player.play();

    return a.exec();
}
//=======================================================================================
int main_qtav_m2( int argc, char *argv[] )
{
    QCoreApplication a(argc, argv);

    QString outFile = QString::fromLatin1("/home/el/trash/out2.mp4");
    QString cv = QString::fromLatin1("libx264");
    QString ca = QString::fromLatin1("aac");
    QString fmt;
    QString hwdev;
    //const bool an = a.arguments().contains(QLatin1String("-an"));
    const bool async = false;
    qint64 ss = 0;

    QVariantHash muxopt, avfopt;
    avfopt[QString::fromLatin1("segment_time")] = 4;
    avfopt[QString::fromLatin1("segment_list_size")] = 0;
    avfopt[QString::fromLatin1("segment_list")] = "/home/el/trash/index.m3u8";
    avfopt[QString::fromLatin1("segment_format")] = QString::fromLatin1("mpegts");
    muxopt[QString::fromLatin1("avformat")] = avfopt;

//    AVPlayer player;
//    player.setFile(file);
//    player.setFrameRate(10000.0); // as fast as possible. FIXME: why 1000 may block source player?
//    player.audio()->setBackends(QStringList() << QString::fromLatin1("null"));

    AVTranscoder avt;
    if (ss > 0)
        avt.setStartTime(ss);
    //avt.setMediaSource(&player);
    avt.setOutputMedia(outFile);
    avt.setOutputOptions(muxopt);
    if (!fmt.isEmpty())
        avt.setOutputFormat(fmt); // segment, image2
    if (!avt.createVideoEncoder()) {
        qWarning("Failed to create video encoder");
        return 1;
    }
    VideoEncoder *venc = avt.videoEncoder();
    venc->setCodecName(cv); // "png"
    venc->setBitRate(1024*1024);
    if (!hwdev.isEmpty())
        venc->setProperty("hwdevice", hwdev);
//    if (fmt == QLatin1String("image2"))
//        venc->setPixelFormat(VideoFormat::Format_RGBA32);
    venc->setPixelFormat(VideoFormat::Format_RGB24);
//    if (an) {
//        avt.sourcePlayer()->setAudioStream(-1);
//    } else {
//        if (!avt.createAudioEncoder()) {
//            qWarning("Failed to create audio encoder");
//            return 1;
//        }
//        AudioEncoder *aenc = avt.audioEncoder();
//        aenc->setCodecName(ca);
//    }

    QObject::connect(&avt, SIGNAL(stopped()), qApp, SLOT(quit()));
    avt.setAsync(async);
    avt.start(); //start transcoder first
//    player.play();

    QFont::initialize();

    //AVPlayer ppp;
    //ppp.setIODevice()

    //VImageWidget().set_image()

    QTimer timer;
    QObject::connect( &timer, &QTimer::timeout, [&]()
    {
        static int cnt = 0;
        auto img = no_signal(cnt++);
        auto vf = VideoFrame(img);
        bool ok = venc->encode( vf );
        Q_ASSERT(ok);
        if (cnt > 100) a.quit();
    });
    timer.start(100);

    return a.exec();
}
//=======================================================================================






//=======================================================================================
class Receiver : QObject
{
public:
    Receiver( Four_Images *imgs )
    {
        tune_cam( &imgs->i1, "rtsp://admin:12345@10.0.1.250:1554" );
        tune_cam( &imgs->i2, "rtsp://admin:12345@10.0.1.250:2554" );
        //tune_cam( &imgs->i3, "rtsp://admin:pass12345@10.0.1.250:5554" );
      //  tune_cam( &imgs->i3, "rtsp://admin:Niias0987@192.168.33.50:554" );
      //  tune_cam( &imgs->i4, "rtsp://admin:12345@10.0.1.250:1554" );
    }
private:
    int cnt = 0;
    void tune_cam( VImageWidget *w, QString url )
    {
        QMediaPlayer *player = new QMediaPlayer(this);

        auto err_ptr = static_cast<void(QMediaPlayer::*)(QMediaPlayer::Error error)>
                (&QMediaPlayer::error);

        connect( player, err_ptr, [player,w,this](QMediaPlayer::Error error)
        {
            w->set_image( no_signal(++cnt) );
            vdeb << "====> error occured:" << error;
            player->play();
        });

        auto probe = new QVideoProbe(this);
        connect(probe, &QVideoProbe::videoFrameProbed, [w,url](const QVideoFrame &vf_)
        {
            auto vf = vf_;
            vf.map( QAbstractVideoBuffer::ReadOnly );
            //===========================================================================
            Q_ASSERT( vf.pixelFormat() == QVideoFrame::Format_YUV420P );
            cv::Size actual_size(vf.width(), vf.height());
            cv::Size half_size = actual_size / 2;

            cv::Mat y( actual_size, CV_8UC1, vf.bits(0), vf.bytesPerLine(0) );
            cv::Mat u( half_size,   CV_8UC1, vf.bits(1), vf.bytesPerLine(1) );
            cv::Mat v( half_size,   CV_8UC1, vf.bits(2), vf.bytesPerLine(2) );

//            cv::Mat y1;
//            cv::resize(y, y1, actual_size, 0, 0, cv::INTER_NEAREST); //copy for zeroing slices
//            y = y1;

            cv::resize(u, u, actual_size, 0, 0, cv::INTER_NEAREST); //repeat u values 4 times
            cv::resize(v, v, actual_size, 0, 0, cv::INTER_NEAREST); //repeat v values 4 times
            //vdeb << y.step1() << u.step1() << v.step1();
            Q_ASSERT( (y.step1() == u.step1()) && (u.step1() == v.step1()) );

            cv::Mat yuv;
            std::vector<cv::Mat> yuv_channels = {y, u, v};
            cv::merge( yuv_channels, yuv );

            cv::Mat rgb;
            cv::cvtColor( yuv, rgb, cv::COLOR_YUV2RGB );

            //cv::Mat t1( vf.height() * 3 / 2, vf.width(), CV_8UC1, vf.bits(), vf.bytesPerLine() );
            //cv::cvtColor( t1, rgb, cv::COLOR_YUV2RGB_NV21 );

            QImage img( rgb.data, rgb.size().width, rgb.size().height,
                        rgb.step1(), QImage::Format_RGB888 );
            //===========================================================================
            auto dt = QDateTime::currentDateTime();
            {
                QPainter p( &img );

                p.save();
                p.setPen(Qt::green);
                p.translate( 3, img.height() - 3);
                p.scale(2,2);
                p.drawText( 0, 0, QString("%1, %2x%3")
                                        .arg(url).arg(img.width()).arg(img.height()) );
                p.restore();

                p.save();
                p.scale(5,5);
                p.setPen(Qt::red);
                p.drawText( 1, 11, dt.toString("yyyy-MM-dd hh:mm:ss.zzz") );
                p.restore();

                //p.save();
            }
            w->set_image( img );
            vf.unmap();
        });
        auto ok = probe->setSource(player);
        Q_ASSERT(ok);

        const QUrl qurl = QUrl( url );
        const QNetworkRequest requestRtsp( qurl );
        player->setMedia( requestRtsp );
        player->play();
    } // tune one cam.
};
//=======================================================================================
int main_rtsp(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Four_Images imgs;
    imgs.showMaximized();

    Receiver rec( &imgs );

    return a.exec();
}
