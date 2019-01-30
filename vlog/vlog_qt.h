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


#ifndef VLOG_QT_H
#define VLOG_QT_H

#include "vlog.h"
#include <ostream>

#include <QString>
#include <QByteArray>
#include <QSize>

std::ostream & operator << ( std::ostream & os, const QString& str );

std::ostream & operator << ( std::ostream & os, const QByteArray& arr );

std::ostream & operator << ( std::ostream & os, const QSize& sz );


#endif // VLOG_QT_H
