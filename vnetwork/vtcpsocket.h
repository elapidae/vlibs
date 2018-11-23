#ifndef VTCPSOCKET_H
#define VTCPSOCKET_H

#include "vipaddress.h"
#include <memory>

class VTcpSocket
{
public:
    VTcpSocket();

    void connect_to_host(VIpAddress addr, uint16_t port );
    void close();

private:
    class Pimpl; Pimpl *p = nullptr;
};


#endif // VTCPSOCKET_H
