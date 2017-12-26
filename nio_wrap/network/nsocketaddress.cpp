#include "nsocketaddress.h"

#include <assert.h>
#include "impl/ncastinghelper.h"
#include "impl/nconvertinghelper.h"



//=======================================================================================
//      Inet Address
//=======================================================================================
NInetAddress::NInetAddress( GInetAddress *a )
    : NObject( gcast_to_gobject(a) )
    , _g_inet_address( a )
{}
//=======================================================================================
NInetAddress NInetAddress::from_string( const std::string &addr )
{
    return addr;
}
//=======================================================================================
NInetAddress NInetAddress::any_ip4()
{
    return g_inet_address_new_any( G_SOCKET_FAMILY_IPV4 );
}
//=======================================================================================
NInetAddress NInetAddress::any_ip6()
{
    return g_inet_address_new_any( G_SOCKET_FAMILY_IPV6 );
}
//=======================================================================================
//NInetAddress NInetAddress::any()
//{
//    auto both = GSocketFamily(G_SOCKET_FAMILY_IPV6 | G_SOCKET_FAMILY_IPV6);
//    return g_inet_address_new_any( both );
//}
//=======================================================================================
NInetAddress NInetAddress::loopback_ip4()
{
    return g_inet_address_new_loopback( G_SOCKET_FAMILY_IPV4 );
}
//=======================================================================================
NInetAddress NInetAddress::loopback_ip6()
{
    return g_inet_address_new_loopback( G_SOCKET_FAMILY_IPV6 );
}
//=======================================================================================
NInetAddress NInetAddress::loopback_unix()
{
    return g_inet_address_new_loopback( G_SOCKET_FAMILY_UNIX );
}
//=======================================================================================
NInetAddress::NInetAddress( const std::string &addr )
    : NInetAddress( g_inet_address_new_from_string(addr.c_str()) )
{}
//=======================================================================================
std::string NInetAddress::to_string() const
{
    return n_convert_and_free( g_inet_address_to_string(_g_inet_address) );
}
//=======================================================================================
//      Inet Address
//=======================================================================================




//=======================================================================================
//      Socket Address
//=======================================================================================
NSocketAddress::NSocketAddress( GSocketAddress *a )
    : NObject( gcast_to_gobject(a) )
    , _g_socket_address( a )
{}
//=======================================================================================
NSocketAddress::NSocketAddress()
    : NSocketAddress( nullptr )
{}
//=======================================================================================
GSocketFamily NSocketAddress::get_family() const
{
    return g_socket_address_get_family( _g_socket_address );
}
//=======================================================================================
bool NSocketAddress::is_inet_socket_address() const
{
    return type_name() == "GInetSocketAddress";
}
//=======================================================================================
NInetSocketAddress NSocketAddress::to_inet_socket_address() const
{
    assert( is_inet_socket_address() );
    g_object_ref( _g_socket_address );
    return NInetSocketAddress( _g_socket_address );
}
//=======================================================================================
//      Socket Address
//=======================================================================================




//=======================================================================================
//      Inet Socket Address
//=======================================================================================
NInetSocketAddress::NInetSocketAddress( NInetAddress addr, uint16_t port )
    : NInetSocketAddress( g_inet_socket_address_new(addr._g_inet_address, port) )
{}
//=======================================================================================
NInetSocketAddress::NInetSocketAddress( const std::string &addr, uint16_t port )
    : NInetSocketAddress( NInetAddress(addr.c_str()), port )
{}
//=======================================================================================
NInetSocketAddress::NInetSocketAddress( GSocketAddress *a )
    : NSocketAddress( a )
    , _g_inet_socket_address( gcast_to_ginet_socket_address(a) )
{}
//=======================================================================================
uint16_t NInetSocketAddress::port() const
{
    return g_inet_socket_address_get_port( _g_inet_socket_address );
}
//=======================================================================================
//      Inet Socket Address
//=======================================================================================



