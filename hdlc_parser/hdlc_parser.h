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


#ifndef HDLC_PARSER_H
#define HDLC_PARSER_H

#include <stdexcept>
#include "vstring.h"
#include "vcallback.h"

//=======================================================================================
//  Standard parser for HDLC protocol.
//  https://ru.wikipedia.org/wiki/HDLC
//=======================================================================================

//=======================================================================================
/*  UPD 26.12.2018  by Elapidae
 *
 *  - VSignal заменен на VCallBack.
 *
 *  - received не вызывается для пустых пакетов.
 *
 *  - Маркер начала/конца пакета (7E) считается границей между пакетами.
 *    Т.е. последовательность байт 7E 7E 7E считается двумя правильными пустыми пакетами,
 *    которые будут отброшены, что бы они не значили.
 *
 *  - Обрабатывается ситуация, когда вылавливаем поток не с начала, до появления
 *    маркера начала пакета (7E) будет вызываться lost_from_begin(). Можно контролировать
 *    качество/количество выкинутых из потока данных.
 *
 *  - Добавлена ошибка Error, которая бросается при некорректном потоке данных.
 *    Если надо не падать, ее надо вылавливать во внешнем коде. Перед бросанием
 *    исключения, объект сбрасывается. Т.е. переходит в состояние до приема маркера
 *    начала пакета.
*/
//=======================================================================================


//=======================================================================================
class HDLC_Parser
{
public:
    class Error;

    //  Подается по приеме нового пакета. М/б пустым (между двумя маркерами 7E 7E).
    VCallBack<VString> received;

    //  Если первые символы до 7E не были захвачены, то этот сигнал сообщит о потерях.
    VCallBack<char> lost_from_begin;

    //  Сюда заливаем куски потока данных.
    void append( const std::string& app_data );

private:
    VString _buffer;
    bool    _packet_began = false; // Обозначает что нашли первый 7E.
    bool    _escaped      = false;

    void _throw_error( const std::string& msg );
};
//=======================================================================================
class HDLC_Parser::Error : public std::runtime_error
{
public:
    Error( const std::string& msg );
};
//=======================================================================================


#endif // HDLC_PARSER_H
