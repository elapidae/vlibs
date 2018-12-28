#ifndef RTP_SINK_QT_H
#define RTP_SINK_QT_H

#include <QObject>
#include "rtp_sink.h"

class RTP_Sink_Qt : public QObject
{
    Q_OBJECT
public:
    explicit RTP_Sink_Qt( quint16 port, QObject *parent = nullptr );

signals:
    void image_received( const QImage& img );


private:
    RTP_Sink _sink;
};

#endif // RTP_SINK_QT_H
