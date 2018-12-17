#include "hdlc_parser.h"

#include <assert.h>
#include "verror.h"

static constexpr char ch_5D = 0x5D;
static constexpr char ch_5E = 0x5E;
static constexpr char ch_7D = 0x7D;
static constexpr char ch_7E = 0x7E;

using std::vector;
using std::string;
using std::pair;

//=======================================================================================
HDLC_Parser::HDLC_Parser(HDLC_Parser::ThrowErrors te)
    : _throw_errors( te )
{}
//=======================================================================================
void HDLC_Parser::append( const std::string &app_data )
{
    for ( char ch: app_data )
    {
        //  Пока не найдем первый символ 7E -- ничего не читаем.
        if ( !_packet_began )
        {
            if ( ch == ch_7E ) _packet_began = true;
            continue;
        }

        // Ожидаем только второй символ escape-последовательности.
        if ( _escaped )
        {
            if      ( ch == ch_5D ) _buffer.append( ch_7D );
            else if ( ch == ch_5E ) _buffer.append( ch_7E );
            else    _error( vcat().hex()("Unexpected escape symbol: ", int(ch)) );
            _escaped = false;
            continue;
        }

        // Нашли начало или конец пакета.
        if ( ch == ch_7E )
        {
            if ( _escaped )
                _error( vcat().hex()("Unexpected escape before 0x7E.") );

            if ( !_buffer.empty() )
                received( _buffer );

            _buffer.clear();
            continue;
        }

        // Начало escape последовательности.
        if ( ch == ch_7D )
        {
            _escaped = true;
            continue;
        }

        //Ничего необычного, нормальный символ. Просто кладем в буффер.
        _buffer.append( ch );

    } // for ( char ch: app_data )
}
//=======================================================================================
void HDLC_Parser::_error( const std::string &msg )
{
    if ( _throw_errors == ThrowErrors::Yes )
        throw verror( msg );
    else
        VWARNING << msg;

    _buffer.clear();
    _packet_began = false;
    _escaped = false;
}
//=======================================================================================
void HDLC_Parser::test()
{
    using pair_type = pair<VString,VString>;
    vector< pair_type > pairs;

    pair_type p;
    p.first  = VString::from_hex(" 01 02 03 7e 01 02 03 04 7e ");
    p.second = VString::from_hex("    01 02 03 04    ");
    pairs.push_back(p);

    p.first  = VString::from_hex(" 7e 01 7d5d 07 7e ");
    p.second = VString::from_hex("    01 7d   07    ");
    pairs.push_back(p);

    p.first  = VString::from_hex(" 7e 34 7d5e 43 7e ");
    p.second = VString::from_hex("    34 7e   43    ");
    pairs.push_back(p);

    //    p.first  = VString::from_hex(" 7e 7e ");
    //    p.second = VString::from_hex("       ");
    //    pairs.push_back(p);

    HDLC_Parser parser;
    VString cur_dst;
    parser.received.connect( [&](VString packet)
    {
        if ( cur_dst != packet ) throw verror( "Bad test for packet='", packet,
                                               "', expected '", cur_dst, "'." );
    });
    for ( auto p: pairs )
    {
        cur_dst = p.second;
        for (auto ch: p.first)
            parser.append( VString( 1, ch ) ); // Добавляем побайтно, чтоб неповадно было
    }

    auto bad = VString::from_hex("7e 34 7d must_skp_sym 7e ");
    try
    {
        parser.append( bad );
    }
    catch ( const VError& )
    {
        return;
    }
    throw verror("Expected bad escape");
}
//=======================================================================================
