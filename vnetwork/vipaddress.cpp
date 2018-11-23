#include "vipaddress.h"

#include <netinet/in.h>
#include <vposix_network.h>

using namespace vposix;

//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
VIpAddress VIpAddress::any()
{
    return INADDR_ANY;
}
#pragma GCC diagnostic pop
//=======================================================================================


//=======================================================================================
VIpAddress::VIpAddress( uint32_t host )
    : _host( host )
{}
//=======================================================================================
VIpAddress::VIpAddress( const std::string &ipv4 )
    : _host( Socket::parse_ip(ipv4) )
{}
//=======================================================================================
uint32_t VIpAddress::raw_ip4() const
{
    return _host;
}
//=======================================================================================
VIpAddress::VIpAddress()
{}
//=======================================================================================
uint32_t VIpAddress::_get_host() const
{
    return _host;
}
//=======================================================================================
void VIpAddress::_set_host(uint32_t h)
{
    _host = h;
}
//=======================================================================================
