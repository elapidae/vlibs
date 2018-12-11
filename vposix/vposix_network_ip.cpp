#include "vposix_network_ip.h"

#include "verror.h"

using namespace vposix;

//=======================================================================================
void my_ip_addr::set_a4( const in_addr& a4 )
{
    ip4 = a4;
    ip_type = IpType::Ip4;
}
//=======================================================================================
void my_ip_addr::set_a6( const in6_addr& a6 )
{
    ip6 = a6;
    ip_type = IpType::Ip6;
}
//=======================================================================================
int my_ip_addr::af() const
{
    if ( ip_type == IpType::Ip4 ) return AF_INET;
    if ( ip_type == IpType::Ip6 ) return AF_INET6;

    throw verror("Bad ip type");
}
//=======================================================================================

