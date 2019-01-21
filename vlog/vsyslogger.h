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


#ifndef VSYSLOGGER_H
#define VSYSLOGGER_H

#include "vlogentry.h"

//=======================================================================================
class VSysLogger final
{
public:
    static void open( const std::string &ident );
    static void register_self();
    static void execute( const VLogEntry &entry );
};
//=======================================================================================






//=======================================================================================
//  [1]
//      Описание из просторов интернета:
//
//  Аргумент ident при вызове openlog() сохраняется как есть. Поэтому, если
//  строка меняется, syslog() может начать добавлять уже изменённую строку.
//  Если строка перестаёт существовать, то это может привести к непредвиденным
//  результатам. Наиболее переносимый способ в данном случае --- использовать
//  строковую константу.
//
//=======================================================================================



#endif // VSYSLOGGER_H
