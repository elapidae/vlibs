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
 *    исключения, объект сбрасывается. Т.е. переходит в состояние до приема первого
 *    маркера начала пакета.
 *
 * UPD 2019-01-23 by Elapidae
 *  - Предполагается, что парсер может начать работу с произвольного места,
 *    следовательно, должен сначала найти начало следующего пакета. Если по условию
 *    задачи нужно, чтобы поток принимался с начала, следует присоединиться  к колбэку
 *    lost_from_begin и при вызове обработать ошибку. NB! не вздумайте убивать парсер,
 *    вы будете на вызове из него.
 *
 *  - Добавлен контроль размера пакетов, чтобы поведение по умолчанию предусматривало
 *    контроль переполнения. Максимальный размер по умолчанию: Max_Packet_Size = 1500.
*/
//=======================================================================================


//=======================================================================================
class HDLC_Parser
{
    enum { Max_Packet_Size = 1500 };

public:
    class Error;

    //  Выдаст легитимный пакет с экранированными 7E и 7D.
    static std::string encode( const std::string& packet );

    //  Для контроля переполнения контролируется максимальный размер пакета.
    //  0 -- не контролировать.
    explicit HDLC_Parser( size_t max_packet_size = Max_Packet_Size );

    //  Подается по приеме нового пакета.
    VCallBack<VString> received;

    //  Если первые символы до 7E не были захвачены, то этот сигнал сообщит о потерях.
    VCallBack<char> lost_from_begin;

    //  Сюда заливаем куски потока данных.
    void append( const std::string& app_data );

private:
    VString _buffer;
    bool    _packet_began = false; // Обозначает что нашли первый 7E.
    bool    _escaped      = false;
    size_t  _max_packet_size;

    void _buf_append( char ch );
    void _buf_send();
    [[noreturn]] void _throw_error( const std::string& msg );
};
//=======================================================================================
class HDLC_Parser::Error : public std::runtime_error
{
public:
    Error( const std::string& msg );
};
//=======================================================================================


#endif // HDLC_PARSER_H
