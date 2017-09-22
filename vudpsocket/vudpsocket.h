#ifndef VUDPSOCKET_H
#define VUDPSOCKET_H

#include <memory>

#include "vhostaddress.h"
#include "vsignal.h"
#include "vbytearray.h"



class VUdpSocket final
{
public:

    VSignal< VByteArray, VHostAddress > received;

    VUdpSocket();
    ~VUdpSocket();

    bool bind( uint16_t port );
    void close();

    bool write_datagram( const VByteArray &datagram , const VHostAddress &addr );

private:
    class Pimpl;
    std::unique_ptr<Pimpl> p;
    //Pimpl *p;
};



#endif // VUDPSOCKET_H
