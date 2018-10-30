#include <QApplication>

#include "rtp_sink_qt.h"
#include "vimagewidget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VImageWidget w;
    w.show();

    RTP_Sink_Qt sink(4951);
    QObject::connect( &sink, &RTP_Sink_Qt::image_received,
                      &w, &VImageWidget::set_image );

    return a.exec();
}
