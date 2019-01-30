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


#include "vlog.h"
#include "vhdlc.h"
#include <vector>
#include "verror.h"

using std::vector;
using std::string;
using std::pair;

using namespace std;


//=======================================================================================
class VHDLC_Test: public testing::Test
{};
//=======================================================================================
TEST_F( VHDLC_Test, set_random )
{
    srandom( uint(VTimePoint::now().microseconds().count()) );
}
//=======================================================================================
TEST_F( VHDLC_Test, simple )
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

    p.first  = VString::from_hex(" 7e 7e ");
    p.second = VString::from_hex("       ");
    pairs.push_back(p);

    p.first  = VString::from_hex(" 7e 34 7d5e 43 7e ");
    p.second = VString::from_hex("    34 7e   43    ");
    pairs.push_back(p);

    //    p.first  = VString::from_hex(" 7e 7e ");
    //    p.second = VString::from_hex("       ");
    //    pairs.push_back(p);

    VHDLC::Decoder decoder;
    VString cur_dst;
    decoder.received = [&](VString packet)
    {
        if ( cur_dst != packet ) throw verror( "Bad test for packet='", packet,
                                               "', expected '", cur_dst, "'." );
    };
    for ( auto p: pairs )
    {
        cur_dst = p.second;
        for (auto ch: p.first)
            decoder.append( VString( 1, ch ) ); // Добавляем побайтно, чтоб было
    }

    auto bad = VString::from_hex("7e 34 7d must_skp_sym 7e ");
    try
    {
        decoder.append( bad );
    }
    catch ( const VHDLC::Decoder::Error& )
    {
        return;
    }
    throw verror("Expected bad escape");

//    EXPECT_EQ( res, "05#0A#1B" );
}

//=======================================================================================

TEST_F( VHDLC_Test, empty_packets )
{
    VHDLC::Decoder decoder;
    int empties = 0;
    decoder.received = [&]( const VString& packet )
    {
        if ( !packet.empty() )
            throw verror("unexpected not empty packet.", packet);

        ++empties;
    };

    decoder.append( VString::from_hex(" 7e 7e 7e 7e ") );

    EXPECT_EQ( empties, 0 ); // пустые пакеты не должны подаваться.
}

//=======================================================================================
//  Будем набивать произвольные сообщения и проверять, чтобы на выходе они
//  обязательно появлялись. Также проверяем, чтобы симовлы 7E и 7D были хотя бы по разу.
static void test_any_packets( size_t sz = VHDLC::Decoder::Max_Packet_Size )
{
    bool tested_7d = false;
    bool tested_7e = false;
    for ( int cnt = 0; cnt < 100000 && !tested_7d && !tested_7e; ++cnt )
    {
        std::string test_msg;
        size_t maxs =(sz == 0 ? uint(VHDLC::Decoder::Max_Packet_Size) : sz);
        auto syms = uint(rand()) % maxs;
        if (syms == 0) syms = 1;

        for (uint i = 0; i < syms; ++i)
            test_msg.push_back( char(rand()) );

        tested_7d = tested_7d || test_msg.find(0x7D) != std::string::npos;
        tested_7e = tested_7e || test_msg.find(0x7E) != std::string::npos;

        VHDLC::Decoder decoder;
        bool equals = false;
        decoder.received = [&test_msg, &equals](const VString& res)
        {
            equals = test_msg == res;
            EXPECT_TRUE( equals );
        };
        decoder.append( VHDLC::encode(test_msg) );
        EXPECT_TRUE( equals );
    }
}
//=======================================================================================
TEST_F( VHDLC_Test, any_packets )
{
    for (uint i = 0; i <= VHDLC::Decoder::Max_Packet_Size; ++i)
        test_any_packets(i);
}

//=======================================================================================
