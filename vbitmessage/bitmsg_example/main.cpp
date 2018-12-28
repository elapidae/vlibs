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
