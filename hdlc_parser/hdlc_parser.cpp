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


#include "hdlc_parser.h"

#include <assert.h>
#include "verror.h"

static constexpr char ch_5D = 0x5D;
static constexpr char ch_5E = 0x5E;
static constexpr char ch_7D = 0x7D;
static constexpr char ch_7E = 0x7E;


//=======================================================================================
HDLC_Parser::Error::Error(const std::string &msg)
    : std::runtime_error( msg )
{}
//=======================================================================================



//=======================================================================================
void HDLC_Parser::append( const std::string &app_data )
{
    for ( char ch: app_data )
    {
        //  Пока не найдем первый символ 7E -- ничего не читаем.
        if ( !_packet_began )
        {
            if ( ch == ch_7E ) { _packet_began = true; }
            else               { lost_from_begin(ch);  }

            continue;
        }

        //  Ожидаем только второй символ escape-последовательности.
        if ( _escaped )
        {
            if      ( ch == ch_5D ) _buffer.append( ch_7D );
            else if ( ch == ch_5E ) _buffer.append( ch_7E );
            else    _throw_error( vcat().hex()("Unexpected escape symbol: ", int(ch)) );
            _escaped = false;
            continue;
        }

        //  Нашли начало или конец пакета.
        if ( ch == ch_7E )
        {
            if ( _escaped )
                _throw_error( vcat().hex()("Unexpected escape before 0x7E.") );

            if ( !_buffer.empty() )
                received( _buffer );


            _buffer.clear();
            continue;
        }

        //  Начало escape последовательности.
        if ( ch == ch_7D )
        {
            _escaped = true;
            continue;
        }

        //  Ничего необычного, нормальный символ. Просто кладем в буффер.
        _buffer.append( ch );

    } // for ( char ch: app_data )
}
//=======================================================================================
void HDLC_Parser::_throw_error( const std::string &msg )
{
    _buffer.clear();
    _packet_began = false; // Обозначает что нашли в последовательности первый 7E.
    _escaped      = false;

    throw Error( msg );
}
//=======================================================================================
