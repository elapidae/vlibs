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


#include "vhdlc.h"
#include "vcat.h"

static constexpr char ch_5D = 0x5D;
static constexpr char ch_5E = 0x5E;
static constexpr char ch_7D = 0x7D;
static constexpr char ch_7E = 0x7E;

//=======================================================================================
VHDLC::Decoder::Error::Error(const std::string &msg)
    : std::runtime_error( msg )
{}
//=======================================================================================


//=======================================================================================
VHDLC::Decoder::Decoder( size_t max_packet_size )
    : _packet_began    ( false           )
    , _escaped         ( false           )
    , _max_packet_size ( max_packet_size )
{}
//=======================================================================================
void VHDLC::Decoder::append( const std::string& app_data )
{
    for ( char ch: app_data )
    {
        //  Пока не найдем первый символ 7E -- ничего не читаем.
        if ( !_packet_began )
        {
            if ( ch == ch_7E )  _packet_began = true;
            else                lost_from_begin( ch );
            continue;
        }

        //  Ожидаем только второй символ escape-последовательности.
        if ( _escaped )
        {
            if      ( ch == ch_5D ) _buf_append( ch_7D );
            else if ( ch == ch_5E ) _buf_append( ch_7E );
            else    _throw_error( vcat().hex()("Unexpected escape symbol: ", int(ch)) );
            _escaped = false;
            continue;
        }

        //  Разбираемся кто к нам пожаловал.
        switch ( ch )
        {
        case ch_7E: _buf_send();        break;  //  Нашли границу пакета.
        case ch_7D: _escaped = true;    break;  //  Начало escape последовательности.
        default:    _buf_append( ch );          //  Нормальный символ.
        }

    } // for ( char ch: app_data )
}
//=======================================================================================
void VHDLC::Decoder::_buf_append( char ch )
{
    _buffer.push_back( ch );
    
    if ( _max_packet_size == 0 ) return;
    
    if ( _buffer.size() > _max_packet_size )
        _throw_error( "Buffer overflow" );
}
//=======================================================================================
void VHDLC::Decoder::_buf_send()
{
    if ( _buffer.empty() ) return;
    
    received( _buffer );
    _buffer.clear();
}
//=======================================================================================
V_NORETURN
void VHDLC::Decoder::_throw_error( const std::string& msg )
{
    //  Возвращаемся в начальное состояние, все равно поток уже неконсистентный.
    _buffer.clear();
    _packet_began = false; 
    _escaped      = false;

    throw Error( msg );
}
//=======================================================================================


//=======================================================================================
std::string VHDLC::encode( const std::string& packet )
{
    std::string res( 1, ch_7E );
    for ( char ch: packet )
    {
        switch ( ch )
        {
        case ch_7E:
            res.push_back( ch_7D );
            res.push_back( ch_5E );
            break;
        case ch_7D:
            res.push_back( ch_7D );
            res.push_back( ch_5D );
            break;
        default:
            res.push_back( ch );
        }
    }
    res.push_back( ch_7E );
    return res;
}
//=======================================================================================

/*
//  Для кодирования на ардуинках.
static void hdlc_send( char ch )
{
    static const char ch_7E[] = { 0x7D, 0x5E };
    static const char ch_7D[] = { 0x7D, 0x5D };

    switch ( ch )
    {
    case 0x7E:  Serial.write( ch_7E, 2 );   break;
    case 0x7D:  Serial.write( ch_7D, 2 );   break;
    default:    Serial.write( ch );
    }
}
*/

//=======================================================================================

