#ifndef VIPADDRESS_H
#define VIPADDRESS_H

#include <string>
#include <stdint.h>


//=======================================================================================
class VIpAddress
{
public:
    static VIpAddress any();

    VIpAddress();
    VIpAddress( const char* ip4 );
    VIpAddress( const std::string& ipv4 );

    uint32_t raw_ip4() const;

private:
    uint32_t _host = 0;

    friend class VTcpServer;
    friend class VTcpSocket;
    friend class VUdpSocket;
    uint32_t _get_host() const;
    void _set_host( uint32_t h );
    VIpAddress( uint32_t host );
};
//=======================================================================================



#endif // VIPADDRESS_H
