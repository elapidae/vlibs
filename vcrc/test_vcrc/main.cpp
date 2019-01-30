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
