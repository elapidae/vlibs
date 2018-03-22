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
