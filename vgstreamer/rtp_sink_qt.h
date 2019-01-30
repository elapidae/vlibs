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
