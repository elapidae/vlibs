#include "voutbitmessage.h"

#include <sstream>
#include <assert.h>

VOutBitMessage::VOutBitMessage( uint bits )
    : _data( bits, 0 )
{
    assert( bits % 8 == 0 ); // Проверка, что запрашивают ровное количество байт.
}

void VOutBitMessage::set( uint from, uint to, uint32_t val )
{
    assert( from <= to );           // Правильно указан диапазон.
    assert( to < _data.size() );    // Не вылезаем за границы диапазона.

    // маска первого нужного нам бита.
    uint32_t mask = 1 << (to - from);

    auto b = _data.begin() + from;
    auto e = _data.begin() + to + 1;
    while ( b != e )
    {
        *b++ = val & mask ? 1 : 0;
        val <<= 1;
    }
}

std::string VOutBitMessage::result() const
{
    std::string res;
    char ch = 0;
    int pos = 0;
    for ( auto bit: _data )
    {
        ch <<= 1;
        ch |= bit ? 1 : 0;

        if (++pos != 8) continue;
        res.push_back( ch );
        pos = 0;
    }
    return res;
}

std::string VOutBitMessage::str_as_bits() const
{
    std::stringstream ss;

    auto res = result();
    for ( auto ch: res )
    {
        for (int i = 0; i < 8; ++i)
        {
            ss << ( ch & 0x80 ? '1' : '0' );
            ch <<= 1;
        }
        ss << ' ';
    }

    return ss.str();
}

