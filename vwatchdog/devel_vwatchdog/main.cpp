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

#include "vwatchdog.h"
#include "vapplication.h"
#include "vlog_pretty.h"


using namespace std::chrono;

int main()
{
    VApplication app;

    VWatchDog wd( milliseconds(100), 4 );

    wd.expired = []()
    {
        static int cnt = 0;
        vdeb << "expired" << ++cnt;
    };

    VTimer timer;
    timer.timeout = [&]()
    {
        wd.relax();
        static int cnt = 0;
        vdeb << "relaxed" << ++cnt;
    };
    timer.start( milliseconds(350) );

    app.poll();
    return 0;
}
