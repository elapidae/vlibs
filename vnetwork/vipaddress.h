#ifndef VIPADDRESS_H
#define VIPADDRESS_H

#include <string>
#include <stdint.h>
#include <memory>
#include <iostream>


//=======================================================================================
namespace vposix { struct my_ip_addr; }
//=======================================================================================
class VIpAddress
{
public:
    static VIpAddress any();        // Will return as ip4.
    static VIpAddress any_ip4();
    static VIpAddress any_ip6();

    static VIpAddress loopback();        // Will return as ip4.
    static VIpAddress loopback_ip4();
    static VIpAddress loopback_ip6();

    VIpAddress();
    VIpAddress( const char* ip );
    VIpAddress( const std::string& ip );

    bool is_ip4() const;
    bool is_ip6() const;
    bool inited() const;
    std::string str() const;

private:
    void _set( const std::string& ip );
    VIpAddress( const vposix::my_ip_addr& maddr );
    class Pimpl; std::shared_ptr<Pimpl> p;

    friend class VTcpServer;
    friend class VTcpSocket;
    friend class VUdpSocket;
    const vposix::my_ip_addr& _addr() const;
    vposix::my_ip_addr* _addr_ptr();
};
//=======================================================================================
std::ostream& operator << (std::ostream& os, const VIpAddress& addr );
//=======================================================================================



#endif // VIPADDRESS_H
