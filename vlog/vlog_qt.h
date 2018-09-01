#ifndef VLOG_QT_H
#define VLOG_QT_H

#include "vlog_pretty.h"
#include <ostream>

#include <QString>
#include <QByteArray>

std::ostream & operator << ( std::ostream & os, const QString& str );

std::ostream & operator << ( std::ostream & os, const QByteArray& arr );


#endif // VLOG_QT_H
