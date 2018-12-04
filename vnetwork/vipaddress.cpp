#include "vipaddress.h"

#include <netinet/in.h>
#include <vposix_network.h>
#include <vposix_network_ip.h>
#include "verror.h"
#include <assert.h>


using namespace vposix;

//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
//=======================================================================================
VIpAddress VIpAddress::any_ip4()
{
    static my_ip_addr res = []()
    {
        my_ip_addr maddr;
        maddr.set_a4( {INADDR_ANY} );
        return maddr;
    }();
    return {res};
}
//=======================================================================================
VIpAddress VIpAddress::loopback_ip4()
{
    static my_ip_addr res = []()
    {
        my_ip_addr maddr;
        maddr.set_a4( {INADDR_LOOPBACK} );
        return maddr;
    }();
    return {res};
}
//=======================================================================================
#pragma GCC diagnostic pop
//=======================================================================================


//=======================================================================================
VIpAddress VIpAddress::any()
{
    return any_ip4();
}
//=======================================================================================
VIpAddress VIpAddress::any_ip6()
{
    static my_ip_addr res = []()
    {
        my_ip_addr maddr;
        maddr.set_a6( in6addr_any );
        return maddr;
    }();
    return {res};
}
//=======================================================================================
VIpAddress VIpAddress::loopback()
{
    return loopback_ip4();
}
//=======================================================================================
VIpAddress VIpAddress::loopback_ip6()
{
    static my_ip_addr res = []()
    {
        my_ip_addr maddr;
        maddr.set_a6( in6addr_loopback );
        return maddr;
    }();
    return {res};
}
//=======================================================================================
class VIpAddress::Pimpl
{
public:
    vposix::my_ip_addr addr;
};
//=======================================================================================
VIpAddress::VIpAddress()
    : p( std::make_shared<Pimpl>() )
{}
//=======================================================================================
VIpAddress::VIpAddress( const std::string &ip )
    : p( std::make_shared<Pimpl>() )
{
    bool ok = vposix::Socket::str_to_addr( ip, &p->addr );
    if (!ok)
    {
        throw verror("Ip '", ip, "' cannot be parsed. May replace without exceptions.");
    }
}
//=======================================================================================
VIpAddress::VIpAddress(const my_ip_addr &maddr)
    : p( std::make_shared<Pimpl>() )
{
    p->addr = maddr;
}
//=======================================================================================
const my_ip_addr& VIpAddress::_addr() const
{
    return p->addr;
}
//=======================================================================================
my_ip_addr* VIpAddress::_addr_ptr()
{
    // Чтобы не изменяли разделяемый объект. Этот метод нужен только в VUdpSocket.
    assert( p.unique() );

    return &p->addr;
}
//=======================================================================================
//uint16_t VIpAddress::port() const
//{
//    switch ( p->addr.stype )
//    {
//    case SockAddr::my_addr::Ip4: return ntohs( p->addr.sa4.sin_port  );
//    case SockAddr::my_addr::Ip6: return ntohs( p->addr.sa6.sin6_port );
//    default: throw verror( "Cannot get port" );
//    }
//}
//=======================================================================================
//SockAddr::my_addr *VIpAddress::my_addr()
//{
//    return &p->addr;
//}
//=======================================================================================
