#include <iostream>
#include <assert.h>

#include "vlog_pretty.h"
#include "vposix_eventfd.h"

#include "vposix_epoll.h"
#include "vudpsocket.h"

#include "vposix_timerfd.h"
#include "vposix_files.h"
#include "vposix_core.h"

#include <thread>

//#include "vpoll/vinvokequeue.h"
#include "vpoll.h"

#include "vapplication.h"
#include "vcat_tuple.h"

template <class T>
class TD;

using namespace vposix;
using namespace std;
using namespace std::chrono;


///VPoll_Queue *ppp = nullptr;
bool lstop = false;
static void rec()
{
///    assert( ppp );
    static int i = 0;
    vdeb << "Hello world!" << i++;
    //ppp->finvoke( rec );
    //if (i > 20000) ppp->stop();
}

class C
{
public:
    void foo() { vdeb << "foo"; }
    bool bar(int) { vdeb << "bar"; return true; }
};

int main()
{
    VApplication app;
    app.invoke( [&](){ app.stop(); });
    app.invoke( [&](){ vdeb << "Hello world!"; });
    app.invoke( [&](){ vdeb << "Hello world!-2"; });
    app.poll();
    return 0;

//    VPoll::add_poll();

 ///   auto p = VPoll_Queue::get();
 ///   ppp = &p;

//    C c;
//    p.invoke( &c, &C::foo );
//    p.invoke( &c, &C::bar, 42 );

//    p.invoke( rec );

//    VPoll::poll

//    VPoll::poll_once();
////    auto vpoll = VPoll::current();
////    ppp = &vpoll;
//    vpoll.finvoke( [](){ vdeb << "Hello world - 1!";} );
//    vpoll.finvoke( [](){ vdeb << "Hello world - 2!";} );

//    vpoll.finvoke( rec );

//    vpoll.poll();

    return 0;

    VUdpSocket udp;
    udp.bind( VIpAddress::any(), 1234 );


    return 0;
}

#include "vline.h"
int WTF()
{
    VPointD p1(587746.8399999999674, 6610695.009999999776);
    VPointD p2(587841.7700000000186, 6610665.679999999702);
    {
        auto mmx = std::minmax(p1.x(), p2.x());
        auto mmy = std::minmax(p1.y(), p2.y());
        vdeb.max_precision() << mmx;
        vdeb.max_precision() << mmy;
    }
    {
        auto mx = std::minmax(587746.8399999999674, 587841.7700000000186);
        auto my = std::minmax(6610695.009999999776, 6610665.679999999702);
        vdeb.max_precision() << mx;
        vdeb.max_precision() << my;
    }
    std::cout << "==========================" << std::endl;
    std::cout << std::setprecision(20);
    {
        auto mx = std::minmax(587746.8399999999674, 587841.7700000000186);
        std::cout << mx.first << ",\t" << mx.second << std::endl;
    }
    std::cout << "==========================" << std::endl;
    {
        auto mx   = std::minmax(587746.8399999999674, 587841.7700000000186);
        auto minx = std::min(   587746.8399999999674, 587841.7700000000186);
        auto maxx = std::max(   587746.8399999999674, 587841.7700000000186);

        auto my   = std::minmax(6610695.009999999776, 6610665.679999999702);
        auto miny = std::min(   6610695.009999999776, 6610665.679999999702);
        auto maxy = std::max(   6610695.009999999776, 6610665.679999999702);
        std::cout << minx << ",\t" << maxx << std::endl;
        std::cout << miny << ",\t" << maxy << std::endl;

        std::cout << mx.first << ",\t" << mx.second << std::endl;
        std::cout << my.first << ",\t" << my.second << std::endl;
        //TD<decltype(maxx)> ddd;
    }
    std::cout << " ^^^^^ WTF? ^^^^^ " << std::endl;
    std::cout << "==========================" << std::endl;

    return 1;
}
