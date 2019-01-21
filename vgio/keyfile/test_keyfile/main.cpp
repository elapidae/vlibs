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


#include "vgio_keyfile_schema.h"
#include "vlog_pretty.h"
#include "vcat_containers.h"

using namespace std;
using namespace vgio;


class KF_Test: public testing::Test
{};

//=======================================================================================
TEST_F( KF_Test, getters )
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

//=======================================================================================

TEST_F(KF_Test, setters)
{
    std::string kf_str;
    {
        auto k = KeyFile::from_data( "# first comment" );

        k.set_bool(   "g", "b", true);
        k.set_int(    "g", "i", 42);
        k.set_double( "g", "d", 123.45);
        k.set_string( "g", "s", "Привет мир!");

        k.set_bool_list(   "gl", "b", {true}   );
        k.set_int_list(    "gl", "i", {42}     );
        k.set_double_list( "gl", "d", {123.45} );
        k.set_string_list( "gl", "s", {"Привет мир!"} );

        kf_str = k.to_data();
    }

    auto rk = KeyFile::from_data( kf_str );

    EXPECT_EQ( rk.get_bool(   "g","b"), true );
    EXPECT_EQ( rk.get_int(    "g","i"), 42 );
    EXPECT_EQ( rk.get_string( "g","s"), "Привет мир!" );
    EXPECT_DOUBLE_EQ( rk.get_double( "g","d"), 123.45 );

    EXPECT_EQ( rk.get_bool_list( "g","b"),   KeyFile::BoolList{true} );
    EXPECT_EQ( rk.get_int_list( "g","i"),    KeyFile::IntList{42} );
    EXPECT_EQ( rk.get_string_list( "g","s"), KeyFile::StringList{"Привет мир!"} );
    EXPECT_EQ( rk.get_double_list("g","d"),  KeyFile::DoubleList{123.45} );
}

//=======================================================================================

TEST_F(KF_Test, simple_shema)
{
    //  NB! Можно читать и писать ТОЛЬКО ЧЕТЫРЕ ТИПА (и их вектора)!
    //  bool, int, double, std::string

    //  Код захардкоржен, т.к. здесь задача -- проверить вызываемость и реакцию методов.

    bool    b = false;
    int     i = -1;
    double  d = -1;
    string  s = "not correct";

    vector<bool>    vb;
    vector<int>     vi;
    vector<double>  vd;
    vector<string>  vs;

    KeyFile_Schema schema;

    schema.set_current_group("Vals");
    schema.append( "b", &b, true,   "comment b" );
    schema.append( "i", &i, 42,     "comment i", {-1000, 1000} );
    schema.append( "d", &d, 123.45, "comment d", {-1234, 1234} );
    schema.append( "s", &s, "HW!",  "comment s" );

    schema.set_current_group("Lists");
    schema.append( "b", &vb, {true,false},    "comment b" );
    schema.append( "i", &vi, {42,43},         "comment i" );
    schema.append( "d", &vd, {123.45,234.56}, "comment d" );
    schema.append( "s", &vs, {"HW!", "HW2!"}, "comment s" );


    // Сохраним начальные значения схемы в файл.
    {
        // Сама схема KeyFile не является, она на нем "паразитирует".

        // Можно попросить схему создать пустой KeyFile и записать
        // туда начальные значения.
        KeyFile key_file = schema.build("# Seed line, comment for example...\n"
                                        "# May be empty!");

        key_file.to_file( "keyfile_test.conf" );

        // Можно сохранять в уже существующий KeyFile:
        KeyFile kf2;

        // Запишем что-нибудь кроме основной схемы.
        kf2.set_int( "Other gorup", "other key", -42 );

        // Запишем схему в существующий KeyFile.
        schema.fill( &kf2 );
        kf2.to_file( "keyfile_test.conf" );
    }
    //----------------------------------------------------------
    // Теперь прочитаем сохраненный файл.
    auto kf = KeyFile::from_file( "keyfile_test.conf" );

    // NB! Захват всех перечисленных в схеме полей.
    schema.capture( kf );

    EXPECT_EQ( b, true );
    EXPECT_EQ( i, 42 );
    EXPECT_DOUBLE_EQ( d, 123.45 );
    EXPECT_EQ( s, "HW!" );

    EXPECT_EQ( vb, KeyFile::BoolList({true,false}) );
    EXPECT_EQ( vi, KeyFile::IntList({42,43}) );
    EXPECT_EQ( vd, KeyFile::DoubleList({123.45,234.56}) );
    EXPECT_EQ( vs, KeyFile::StringList({"HW!", "HW2!"}) );

    // Поменяем значения так, чтобы они не прошли валидацию.
    kf.set_int( "Vals", "i", 1001 ); // Валидатор установлен в {-1000,1000}

    EXPECT_THROW( schema.capture(kf), KeyFile_Schema::ValidateException );

    // Кроме схемы сохраняли и дополнительное поле:
    EXPECT_EQ( kf.get_int("Other gorup", "other key"), -42 );
}

//=======================================================================================

TEST_F(KF_Test, extended_shema)
{
    int8_t i8;
    uint8_t u8;
    int16_t i16;
    uint16_t u16;
    float f;

    KeyFile_Schema sh;
    sh.set_current_group("Gr");
    sh.append("i8", &i8, 110, "", {-120,120} );
    sh.append("u8", &u8, 110, "", {100,120} );
    sh.append("i16", &i16, 110, "", {-120,120} );
    sh.append("u16", &u16, 110, "", {100,120} );
    sh.append("f", &f, 110., "", {-120,120} );


    uint32_t bad;
    EXPECT_THROW( sh.append("bad", &bad, uint32_t(110), "", {-120,120}), VError );

    auto kf = sh.build();
    //vdeb << kf.to_data();
    //sh.capture( kf );
}

//=======================================================================================
