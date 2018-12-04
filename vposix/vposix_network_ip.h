#ifndef VPOSIX_NETWORK_IP_H
#define VPOSIX_NETWORK_IP_H

#include <arpa/inet.h>
#include "vposix_network.h"

//=======================================================================================
namespace vposix
{
    //===================================================================================
    struct my_ip_addr
    {
    public:

        void set_a4( const in_addr&  a4 );
        void set_a6( const in6_addr& a6 );

        union
        {
            in_addr  ip4;
            in6_addr ip6;
        };        

        // Use it instead of hand switch. Return AF_INET or AF_INET6 (or throw verror).
        int af() const;

        IpType ip_type = IpType::Unknown;

        static my_ip_addr any();         // any4();
        static my_ip_addr any4();
        static my_ip_addr any6();
    };
    //===================================================================================
} // vposix namespace
//=======================================================================================

#endif // VPOSIX_NETWORK_IP_H
