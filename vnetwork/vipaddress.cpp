/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


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
        maddr.set_a4( {htonl(INADDR_ANY)} );
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
        maddr.set_a4( {htonl(INADDR_LOOPBACK)} );
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
VIpAddress::VIpAddress( const char* ip )
    : p( std::make_shared<Pimpl>() )
{
    _set( ip );
}
//=======================================================================================
VIpAddress::VIpAddress( const std::string& ip )
    : p( std::make_shared<Pimpl>() )
{
    _set( ip );
}
//=======================================================================================
bool VIpAddress::is_ip4() const
{
    return p->addr.ip_type == IpType::Ip4;
}
//=======================================================================================
bool VIpAddress::is_ip6() const
{
    return p->addr.ip_type == IpType::Ip6;
}
//=======================================================================================
bool VIpAddress::inited() const
{
    return is_ip4() || is_ip6();
}
//=======================================================================================
std::string VIpAddress::str() const
{
    return Socket::addr_to_str( p->addr );
}
//=======================================================================================
void VIpAddress::_set( const std::string& ip )
{
    bool ok = vposix::Socket::str_to_addr( ip, &p->addr );
    if (!ok)
        throw verror("Ip '", ip, "' cannot be parsed. May replace without exceptions.");
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
std::ostream &operator << ( std::ostream &os, const VIpAddress &addr )
{
    os << "VIpAddress(";

    if ( !addr.inited() ) os << "unknown";
    else                  os << addr.str();

    os << ")";

    return os;
}
//=======================================================================================
