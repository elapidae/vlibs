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
