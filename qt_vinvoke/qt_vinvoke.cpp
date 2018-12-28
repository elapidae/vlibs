#include "qt_vinvoke.h"



//=======================================================================================
void qt::vinvoke( QObject *obj, const char *member,
                  QGenericArgument val0,
                  QGenericArgument val1,
                  QGenericArgument val2,
                  QGenericArgument val3,
                  QGenericArgument val4)
{
    auto res = vinvokeMethod( obj, member, Qt::AutoConnection,
                              val0, val1, val2, val3, val4 );

    Q_ASSERT(res); Q_UNUSED(res)
}
//=======================================================================================
void qt::vinvoke_queue( QObject *obj, const char *member,
                        QGenericArgument val0,
                        QGenericArgument val1,
                        QGenericArgument val2,
                        QGenericArgument val3,
                        QGenericArgument val4)
{
    auto res = vinvokeMethod( obj, member, Qt::QueuedConnection,
                              val0, val1, val2, val3, val4 );

    Q_ASSERT(res); Q_UNUSED(res)
}
//=======================================================================================
bool qt::vinvokeMethod( QObject *obj, const char *member,
                        Qt::ConnectionType type,
                        QGenericArgument val0,
                        QGenericArgument val1,
                        QGenericArgument val2,
                        QGenericArgument val3,
                        QGenericArgument val4)
{
    return QMetaObject::invokeMethod( obj, member, type, val0, val1, val2, val3, val4 );
}
//=======================================================================================


