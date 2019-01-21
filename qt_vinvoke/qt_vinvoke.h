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


#ifndef QTVINVOKE_H
#define QTVINVOKE_H

#include <qobjectdefs.h>

//=======================================================================================
/*  Обертка вокруг вызова QMetaObject::invokeMethod для вызова Qt слотов.
 *
 *  Проверяет результат вызова (в дебаге), чтобы программа ломалась,
 *  а не в консоль ворнинги сыпались.
 *
 *  Синтаксис такой же как в Qt: имя слота передается через строку, аргументы через
 *  Q_ARG( type, value ).
 *
 *  Пример:
 *  class SomeQtObject : public QObject
 *  {
 *      ...
 *  public slots:
 *      void some_slot( int val );
 *      ...
 *  }
 *  ...
 *  SomeQtObject obj;
 *  qt::vinvoke( &obj, "some_slot", Q_ARG(int,42) );        // по умолчанию, используется
 *                                                          // Qt::AutoConnection
 *
 *  qt::vinvoke_queue( &obj, "some_slot", Q_ARG(int,42) );  // Qt::QueuedConnection
*/
//=======================================================================================



//=======================================================================================
namespace qt
{
    //-------------------------------------------------------------------------------
    void vinvoke( QObject *obj, const char *member,
                  QGenericArgument val0 = QGenericArgument(Q_NULLPTR),
                  QGenericArgument val1 = QGenericArgument(),
                  QGenericArgument val2 = QGenericArgument(),
                  QGenericArgument val3 = QGenericArgument(),
                  QGenericArgument val4 = QGenericArgument());
    //-------------------------------------------------------------------------------
    void vinvoke_queue( QObject *obj, const char *member,
                        QGenericArgument val0 = QGenericArgument(Q_NULLPTR),
                        QGenericArgument val1 = QGenericArgument(),
                        QGenericArgument val2 = QGenericArgument(),
                        QGenericArgument val3 = QGenericArgument(),
                        QGenericArgument val4 = QGenericArgument());
    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    // using by other functions.
    bool vinvokeMethod( QObject *obj, const char *member,
                        Qt::ConnectionType type,
                        QGenericArgument val0 = QGenericArgument(Q_NULLPTR),
                        QGenericArgument val1 = QGenericArgument(),
                        QGenericArgument val2 = QGenericArgument(),
                        QGenericArgument val3 = QGenericArgument(),
                        QGenericArgument val4 = QGenericArgument());
    //-------------------------------------------------------------------------------
} // qt namespace
//=======================================================================================



#endif // QTVINVOKE_H
