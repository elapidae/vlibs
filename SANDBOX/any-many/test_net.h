#ifndef TEST_NET_H
#define TEST_NET_H

#include "vudpsocket.h"
#include "vtimer.h"

class test_net
{
public:
    test_net();


private:
    VTimer t1, t2;
    VUdpSocket u1, u2;
    int pk = 0;
};

#endif // TEST_NET_H
