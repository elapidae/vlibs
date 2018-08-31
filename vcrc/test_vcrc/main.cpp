#include <iostream>
#include "gtest/gtest.h"


#include "vcrc.h"

using namespace std;


class CRC_Test: public testing::Test
{};

//=======================================================================================
TEST_F( CRC_Test, poly_04C11DB7 )
{
    // TODO: Надо добавить такую проверку, чтобы она охватывала всю таблицу.

    //Это проверка из шапки CRC (см. vcrc.cpp)
    EXPECT_EQ( vcrc::poly_04C11DB7("123456789"), 0xCBF43926 );
}

//=======================================================================================
