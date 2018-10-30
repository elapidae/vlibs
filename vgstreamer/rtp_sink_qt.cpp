#include "rtp_sink_qt.h"

#include "vimage_qt.h"

RTP_Sink_Qt::RTP_Sink_Qt(quint16 port, QObject *parent)
    : QObject ( parent )
    , _sink   ( port   )
{
    _sink.new_sample.connect( [this]( VGstSample sample )
    {
        QImage res;
        auto extractor = [&res](const VImage& vimg)
        {
            res = VImage_Qt::convert(vimg);
            res.detach();
        };
        sample.extract_image( extractor );

        emit this->image_received( res );
    });
}
