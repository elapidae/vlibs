#include <iostream>
#include "gtest/gtest.h"


#include "vlog_pretty.h"
#include "hdlc_parser.h"
#include <vector>
#include "verror.h"

using std::vector;
using std::string;
using std::pair;

using namespace std;


//=======================================================================================
class HDLC_Test: public testing::Test
{};
//=======================================================================================
//TEST_F( HDLC_Test, set_random )
//{
//    srandom( VTimePoint::now().microseconds().count() );
//}
//=======================================================================================
TEST_F( HDLC_Test, simple )
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

    HDLC_Parser parser;
    VString cur_dst;
    parser.received = [&](VString packet)
    {
        if ( cur_dst != packet ) throw verror( "Bad test for packet='", packet,
                                               "', expected '", cur_dst, "'." );
    };
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
    catch ( const HDLC_Parser::Error& )
    {
        return;
    }
    throw verror("Expected bad escape");

//    EXPECT_EQ( res, "05#0A#1B" );
}

//=======================================================================================

TEST_F( HDLC_Test, empty_packets )
{
    HDLC_Parser parser;
    int empties = 0;
    parser.received = [&]( const VString& packet )
    {
        if ( !packet.empty() )
            throw verror("unexpected not empty packet.", packet);

        ++empties;
    };

    parser.append( VString::from_hex(" 7e 7e 7e 7e ") );

    EXPECT_EQ( empties, 0 ); // пустые пакеты не должны подаваться.
}

//=======================================================================================
