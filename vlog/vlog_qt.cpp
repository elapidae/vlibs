#include "vlog_qt.h"


std::ostream &operator << ( std::ostream &os, const QString &str )
{
    os << str.toStdString();
    return os;
}

std::ostream &operator << ( std::ostream &os, const QByteArray &arr )
{
    os << arr.data();
    return os;
}
