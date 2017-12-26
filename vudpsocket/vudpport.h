#ifndef VUDPPORT_H
#define VUDPPORT_H

#include "vbytearray.h"
#include "vhostaddress.h"


class VUdpPort
{
public:

    explicit VUdpPort();

    virtual ~VUdpPort();

    bool is_opened() const { return _handle; }

    bool bind( uint16_t port );
    void close();

    VByteArray read_datagram( bool *ok );
    VByteArray read_datagram_from( VHostAddress *peer, bool *ok );

    bool write_datagram( const VByteArray &datagram , const VHostAddress &addr );

    int handle() const { return _handle; }

private:
    int _handle = 0;
    int _last_errno = 0;
};





#endif // VUDPPORT_H
