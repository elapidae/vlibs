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


#include <iostream>

#include "voutbitmessage.h"
#include "vlog_pretty.h"


int main()
{
    VOutBitMessage msg( 24 );

    msg.set( 1, 1, 1 );         // Второй бит в единичку.
    msg.set( 4, 15, 0xFAAA );   // F фтопку, AAA == 1010 1010 1010
    msg.set( 20, 23, 0xFF );    // единички в хвост.

    //msg.set( 23, 22, 0xFF ); // ошибка -- from > to
    //msg.set( 23, 24, 0xFF ); // ошибка -- 24 == 25й бит за пределами сообщения.

    vdebug << msg.str_as_bits();

    return 0;
}
