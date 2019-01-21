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
#include "vtimer.h"


//  11.12.2018  by Elapidae
//  Ничего, кроме сборки, не проверяется! Сейчас сделано для демонстрации.

using namespace std;


class VTimer_Test: public testing::Test
{};

//=======================================================================================
TEST_F( VTimer_Test, set_random )
{
    srandom( VTimePoint::now().microseconds().count() );
}
//=======================================================================================
TEST_F( VTimer_Test, dev_polling )
{
    VApplication app;

    vdeb << "==========================================================================";

    VTimer timer1;
    timer1.timeout.connect( [&]()
    {
        vdeb << "Single shot timer, about to stop.";
        VApplication::app()->stop();    // Singleton for once VApplication instance,
                                        // like as Qt "qApp" macros.
    });
    timer1.singleshot( chrono::seconds(1) );


    VTimer timer2;
    timer2.timeout_count.connect( [](int cnt)
    {
        vdeb << "quick timer, count of episodes =" << cnt;
    });
    //timer2.start( chrono::microseconds(10) ); // Будет в количестве давать 1, скучно...
    timer2.start( chrono::nanoseconds(10) );

    app.poll();
    vdeb << "==========================================================================";

    //EXPECT_EQ();
}
//=======================================================================================

//=======================================================================================


