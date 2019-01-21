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


#include "vapplication.h"
#include "vlog_pretty.h"
#include <list>
#include <deque>

//  На 23-11-2018 Тест реально ничего не проверяет, просто убеждается что все собирается
// и толкает в очередь пробные лямбды.

using namespace std;


//=======================================================================================
class VApplication_Test: public testing::Test
{};
//=======================================================================================
//TEST_F( VApplication_Test, set_random )
//{
//    srandom( VTimePoint::now().microseconds().count() );
//}
//=======================================================================================
TEST_F( VApplication_Test, dev_polling )
{
    VApplication app;

    app.invoke( [](int i){ vtrace << i;}, 42 );
    app.invoke( [](int i){ vtrace << i;}, 43 );
    app.invoke( [](int i){ vtrace << i;}, 44 );
    app.invoke( [](int i){ vtrace << i;}, 45 );
    app.invoke( [](int i){ vtrace << i;}, 46 );
    app.invoke( [](int i){ vtrace << i;}, 47 );
    app.invoke( [](int i){ vtrace << i;}, 48 );
    app.invoke( [&](){ vtrace << "stop"; app.stop(); } );
    app.poll();
    //EXPECT_EQ();
}
//=======================================================================================

//=======================================================================================


