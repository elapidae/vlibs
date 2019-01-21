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


