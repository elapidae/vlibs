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
#include "gtest/gtest.h"


#include "vstring.h"
#include "vlog_pretty.h"
#include <list>
#include <deque>


using namespace std;


class VString_Test: public testing::Test
{};

//=======================================================================================
TEST_F( VString_Test, set_random )
{
    srandom( VTimePoint::now().microseconds().count() );
}
//=======================================================================================
TEST_F( VString_Test, ASCII_hex )
{
    auto abra = VString::from_hex( "Abracadabra" ).to_Hex();
    EXPECT_EQ( abra, "0A BA CA DA BA" );

    //При нечетном количестве шестнадцатеричных символов, считается, что первый байт
    //обозначен одним символом:
    auto odd_syms = VString::from_hex("123").to_Hex();
    EXPECT_EQ( odd_syms, "01 23" );

    VString test;
    test.append( char(0x05) );
    test.append( char(0x0A) );
    test.append( char(0x1B) );

    auto res = test.tohex();        // "050a1b"
    EXPECT_EQ( res, "050a1b" );

    res = test.toHex();             // "050A1B"
    EXPECT_EQ( res, "050A1B" );

    res = test.to_hex();            // "05 0a 1b"
    EXPECT_EQ( res, "05 0a 1b" );

    res = test.to_Hex();            // "05 0A 1B"
    EXPECT_EQ( res, "05 0A 1B" );

    res = test.to_Hex('#');         // "05#0A#1B"
    EXPECT_EQ( res, "05#0A#1B" );
}

//=======================================================================================

TEST_F( VString_Test, prepend_append )
{
    VString str = " ";

    // Проверка приращения строк.
    str.prepend( "Hello" );
    str.append( "world!" );
    EXPECT_EQ( str, "Hello world!" );

    // Проверка приращения произвольных контейнеров.
    list<uint8_t> p;
    deque<int8_t> a;

    p.push_back('H');
    p.push_back('e');
    p.push_back('l');
    p.push_back('l');
    p.push_back('o');

    a.push_back('w');
    a.push_back('o');
    a.push_back('r');
    a.push_back('l');
    a.push_back('d');
    a.push_back('!');

    str = " ";
    str.append( a.begin(), a.end() );
    str.prepend( p.begin(), p.end() );
    EXPECT_EQ( str, "Hello world!" );
}
//=======================================================================================
TEST_F( VString_Test, prepend_append_LE_BE )
{
    VString str = " ";

    char     center = 0x00;
    int32_t  i32    = 0x12345678;
    uint16_t u16    = 0xABCD;

    VString be, le;

    be.append(center);
    be.prepend_BE(i32);
    be.append_BE(u16);
    auto be_Hex = be.to_Hex();
    EXPECT_EQ( be_Hex, "12 34 56 78 00 AB CD" );

    le.prepend_LE(center);
    le.append_LE(u16);
    le.prepend_LE(i32);
    auto le_Hex = le.to_Hex();
    EXPECT_EQ( le_Hex, "78 56 34 12 00 CD AB" );
}
//=======================================================================================
TEST_F( VString_Test, front_back_str_LE_BE )
{
    // front/back str
    VString H = "Hello ";
    VString W = "world!";
    VString str = H + W;

    auto fH = str.front_str ( H.size() );
    auto bW = str.back_str  ( W.size() );

    EXPECT_EQ( H, fH );
    EXPECT_EQ( W, bW );


    // front/back LE/BE
    int32_t i32    = 0x12345678;
    int32_t i32rev = 0x78563412; // реверсное значение.

    str.clear();
    str.append_LE( i32 );
    // Простмотр что с начала, что с конца.
    EXPECT_EQ( str.front_LE<int32_t>(), str.back_LE<int32_t>() );
    EXPECT_EQ( str.front_BE<int32_t>(), str.back_BE<int32_t>() );

    EXPECT_EQ( str.front_LE<int32_t>(), i32    );
    EXPECT_EQ( str.front_BE<int32_t>(), i32rev );


    // То же самое, только теперь закладываем как BE
    str.clear();
    str.append_BE( i32 );

    EXPECT_EQ( str.front_LE<int32_t>(), str.back_LE<int32_t>() );
    EXPECT_EQ( str.front_BE<int32_t>(), str.back_BE<int32_t>() );

    EXPECT_EQ( str.front_LE<int32_t>(), i32rev );
    EXPECT_EQ( str.front_BE<int32_t>(), i32    );

    {
        float f = 7.93094e+08f;
        str.clear();
        str.append_BE( f );
        EXPECT_EQ( f, str.front_BE<float>() );
        EXPECT_EQ( f, str.back_BE<float>() );

        str.clear();
        str.append_LE( f );
        EXPECT_EQ( f, str.front_LE<float>() );
        EXPECT_EQ( f, str.back_LE<float>() );
    } // float

    {
        double d = random();
        str.clear();
        str.append_BE( d );
        EXPECT_EQ( d, str.front_BE<double>() );
        EXPECT_EQ( d, str.back_BE<double>() );

        str.clear();
        str.append_LE( d );
        EXPECT_EQ( d, str.front_LE<double>() );
        EXPECT_EQ( d, str.back_LE<double>() );
    } // double
}
//=======================================================================================
TEST_F( VString_Test, take_front_back_str_LE_BE )
{
    // Тест скопипащен, сделано следующее: в тестах происходит шесть извлечений, поэтому
    // значение просто проталкивается шесть раз.

    // front/back str
    VString H = "Hello ";
    VString W = "world!";
    VString str = H + W;

    auto fH = str.take_front_str ( H.size() );
    auto bW = str.take_back_str  ( W.size() );

    EXPECT_EQ( H, fH );
    EXPECT_EQ( W, bW );
    EXPECT_TRUE( str.empty() );

    // front/back LE/BE
    int32_t i32    = 0x12345678;
    int32_t i32rev = 0x78563412; // реверсное значение.

    for ( int i = 1; i <= 6; ++i )
        str.append_LE( i32 );

    // Простмотр что с начала, что с конца.
    EXPECT_EQ( str.take_front_LE<int32_t>(), str.take_back_LE<int32_t>() );
    EXPECT_EQ( str.take_front_BE<int32_t>(), str.take_back_BE<int32_t>() );

    EXPECT_EQ( str.take_front_LE<int32_t>(), i32    );
    EXPECT_EQ( str.take_front_BE<int32_t>(), i32rev );
    EXPECT_TRUE( str.empty() );


    // То же самое, только теперь закладываем как BE
    for ( int i = 1; i <= 6; ++i )
        str.append_BE( i32 );

    EXPECT_EQ( str.take_front_LE<int32_t>(), str.take_back_LE<int32_t>() );
    EXPECT_EQ( str.take_front_BE<int32_t>(), str.take_back_BE<int32_t>() );

    EXPECT_EQ( str.take_front_LE<int32_t>(), i32rev );
    EXPECT_EQ( str.take_front_BE<int32_t>(), i32    );
    EXPECT_TRUE( str.empty() );
}
//=======================================================================================
TEST_F( VString_Test, chop_front_back )
{
    VString str = "Hello world!";
    VString c1 = "ello world!";
    VString c2 = "ello worl";

    str.chop_front( 1 );
    EXPECT_EQ( str, c1 );

    str.chop_back( 2 );
    EXPECT_EQ( str, c2 );


    // Если байт не хватает -- должен оставить пустую строку.

    str.chop_front( 1000 );
    EXPECT_TRUE( str.empty() );

    str = "Hello world!";
    str.chop_back( 1000 );
    EXPECT_TRUE( str.empty() );
}
//=======================================================================================
TEST_F( VString_Test, begins_with_ends_with )
{
    VString str = "Hello world!";

    EXPECT_TRUE( str.begins_with("Hello world!") );
    EXPECT_TRUE( str.begins_with("Hello ") );
    EXPECT_TRUE( str.begins_with("H") );
    EXPECT_TRUE( str.begins_with("") ); // вполне законно.

    for ( int ch = 0; ch < 256; ++ch )
    {
        if (ch != 'H')
        {
            std::string s;
            s.push_back( ch );
            EXPECT_FALSE( str.begins_with(s) );
        }
    }


    EXPECT_TRUE( str.ends_with("Hello world!") );
    EXPECT_TRUE( str.ends_with(" world!") );
    EXPECT_TRUE( str.ends_with("!") );
    EXPECT_TRUE( str.ends_with("") ); // вполне законно.

    for ( int ch = 0; ch < 256; ++ch )
    {
        if (ch != '!')
        {
            std::string s;
            s.push_back( ch );
            EXPECT_FALSE( str.ends_with(s) );
        }
    }

}
//=======================================================================================

TEST_F( VString_Test, forward_view )
{
    const VString  test_str = "Hello world!";
    const char     ch  = random();
    const int8_t   i8  = random();
    const uint8_t  u8  = random();
    const int16_t  i16 = random();
    const uint16_t u16 = random();
    const int32_t  i32 = random();
    const uint32_t u32 = random();
    const int64_t  i64 = random();
    const uint64_t u64 = random();

    const float  f = random() / 1.5f;
    const double d = random() / 1.4;


    VString str = test_str;

    str.append( ch );

    str.append_BE( i8  );
    str.append_BE( u8  );
    str.append_BE( i16 );
    str.append_BE( u16 );
    str.append_BE( i32 );
    str.append_BE( u32 );
    str.append_BE( i64 );
    str.append_BE( u64 );
    str.append_BE( f );
    str.append_BE( d );

    str.append_LE( i8  );
    str.append_LE( u8  );
    str.append_LE( i16 );
    str.append_LE( u16 );
    str.append_LE( i32 );
    str.append_LE( u32 );
    str.append_LE( i64 );
    str.append_LE( u64 );
    str.append_LE( f );
    str.append_LE( d );


    auto fwd_view = str.forward_view();

    // str & ch
    EXPECT_EQ( fwd_view.take_str(test_str.size()), test_str );
    EXPECT_EQ( fwd_view.take_ch(), ch );

    // BE
    EXPECT_EQ( fwd_view.take_i8(), i8 );
    EXPECT_EQ( fwd_view.take_u8(), u8 );
    EXPECT_EQ( fwd_view.take_i16_BE(), i16 );
    EXPECT_EQ( fwd_view.take_u16_BE(), u16 );
    EXPECT_EQ( fwd_view.take_i32_BE(), i32 );
    EXPECT_EQ( fwd_view.take_u32_BE(), u32 );
    EXPECT_EQ( fwd_view.take_i64_BE(), i64 );
    EXPECT_EQ( fwd_view.take_u64_BE(), u64 );

    EXPECT_EQ( fwd_view.take_float_BE(),  f );
    EXPECT_EQ( fwd_view.take_double_BE(), d );

    // LE
    EXPECT_EQ( fwd_view.take_i8(), i8 );
    EXPECT_EQ( fwd_view.take_u8(), u8 );
    EXPECT_EQ( fwd_view.take_i16_LE(), i16 );
    EXPECT_EQ( fwd_view.take_u16_LE(), u16 );
    EXPECT_EQ( fwd_view.take_i32_LE(), i32 );
    EXPECT_EQ( fwd_view.take_u32_LE(), u32 );
    EXPECT_EQ( fwd_view.take_i64_LE(), i64 );
    EXPECT_EQ( fwd_view.take_u64_LE(), u64 );

    EXPECT_EQ( fwd_view.take_float_LE(),  f );
    EXPECT_EQ( fwd_view.take_double_LE(), d );

    EXPECT_TRUE( fwd_view.finished() );
}
//=======================================================================================
TEST_F( VString_Test, substr )
{
    VString str = "Hello world!";

    // LE
    EXPECT_EQ( str.take_front_str(5), "Hello" );
    EXPECT_EQ( str.take_back_str(3), "ld!" );

    EXPECT_THROW( str.front_str(str.size() + 1), std::out_of_range );
}
//=======================================================================================
TEST_F( VString_Test, app_prep_new_syntax )
{
    //  Хочется проверить, что все нормально возвращается, синтаксис работает.
    //  Имеет смысл применять, чтобы, например, переводить одну или несколько переменных
    //  в бинарный буффер "на лету". А также делать преобразования из/в шестнадцатеричный
    //  вид.
    VString str = VString().append_LE  ( uint16_t(0x1234) )
                           .prepend_BE ( uint16_t(0x5678) );

    EXPECT_TRUE( (str.to_Hex() == "56 78 34 12") );

    //------------------------------

    VString nmea_msg = "AnyMany";
    uint8_t crc = 0xAC; // some crc value.

    // port.send (
        auto nmea_res = nmea_msg + '*' + VString().append_as_sys(crc).toHex() + "\r\n";
    // );
    EXPECT_TRUE( (nmea_res == "AnyMany*AC\r\n") );
}
//=======================================================================================


