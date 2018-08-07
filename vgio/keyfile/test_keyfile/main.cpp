#include <iostream>
#include "gtest/gtest.h"

#include "vgio_keyfile.h"


using namespace std;
using namespace vgio;


class KF_Test: public testing::Test
{};


TEST_F(KF_Test, test_getters)
{
    auto kf_test =
    R"( # test getters
    [тестовая группа]
    # b comment
    b=true
    i=42
    d=42.42
    s=строка
    [тестовые списки]
    b=true;false;true;
    i=10;11;12
    d=1.2;3.4;5.6;
    s=a;b;c
    )";

    auto k = KeyFile::from_data( kf_test );
    EXPECT_EQ( k.get_bool("тестовая группа", "b"), true );
    EXPECT_EQ( k.get_int("тестовая группа", "i"), 42 );
    EXPECT_EQ( k.get_double("тестовая группа", "d"), 42.42 );
    EXPECT_EQ( k.get_string("тестовая группа", "s"), string("строка") );

    vector<bool> vb = {true,false,true};
    EXPECT_EQ( k.get_bool_list("тестовые списки", "b"), vb );
    vector<int> vi = {10,11,12};
    EXPECT_EQ( k.get_int_list("тестовые списки", "i"), vi );

    auto td = k.get_double_list("тестовые списки", "d");
    vector<double> vd = {1.2,3.4,5.6};
    EXPECT_EQ( td.size(), vd.size() );

    for (uint i = 0; i < td.size(); ++i )
        EXPECT_DOUBLE_EQ( vd[i], td[i] );

    auto ts = k.get_string_list("тестовые списки", "s");
    vector<string> vs = {"a","b","c"};
    EXPECT_EQ( ts.size(), vs.size() );
    for (uint i = 0; i<vd.size(); ++i)
        EXPECT_EQ( ts[i], vs[i] );
}


TEST_F(KF_Test, shifts)
{
}
