#ifndef NSOCKETADDRESS_H
#define NSOCKETADDRESS_H

#include <gio/gio.h>
#include "nobject.h"

//=======================================================================================
//  Native interface:
// GSocketAddress * 	g_socket_address_new_from_native ()
// GSocketFamily 	g_socket_address_get_family ()
// gboolean 	g_socket_address_to_native ()
// gssize 	g_socket_address_get_native_size ()
class NInetSocketAddress;
class NSocketAddress : public NObject
{
public:
    NSocketAddress();

    GSocketFamily get_family() const;

    bool is_inet_socket_address() const;
    NInetSocketAddress to_inet_socket_address() const;

protected:
    NSocketAddress( GSocketAddress *a );

private:
    friend class NSocket;
    GSocketAddress *_g_socket_address = nullptr;
};
//=======================================================================================
class NInetAddress : public NObject
{
public:
    static NInetAddress from_string( const std::string &addr );
    static NInetAddress any_ip4();
    static NInetAddress any_ip6();
    //static NInetAddress any();
    static NInetAddress loopback_ip4();
    static NInetAddress loopback_ip6();

    static NInetAddress loopback_unix();

    //g_inet_address_get_family(inetaddress)

    NInetAddress( const std::string &addr );

    std::string to_string() const;

private:
    NInetAddress( GInetAddress *a );

    friend class NInetSocketAddress;
    friend class NSocket;
    GInetAddress *_g_inet_address = nullptr;
};
//=======================================================================================


//=======================================================================================
//GSocketAddress * 	g_inet_socket_address_new ()
//GSocketAddress * 	g_inet_socket_address_new_from_string ()
//GInetAddress * 	g_inet_socket_address_get_address ()
//guint16 	g_inet_socket_address_get_port ()
//guint32 	g_inet_socket_address_get_flowinfo ()
//guint32 	g_inet_socket_address_get_scope_id ()
//Properties
//GInetAddress * 	address 	Read / Write / Construct Only
//guint 	flowinfo 	Read / Write / Construct Only
//guint 	port 	Read / Write / Construct Only
//guint 	scope-id
class NInetSocketAddress : public NSocketAddress
{
public:
    NInetSocketAddress( NInetAddress addr, uint16_t port );
    NInetSocketAddress( const std::string &addr, uint16_t port );

    uint16_t port() const;

private:
    friend class NSocketAddress;
    NInetSocketAddress( GSocketAddress *a );
    GInetSocketAddress *_g_inet_socket_address = nullptr;
};
//=======================================================================================


#endif // NSOCKETADDRESS_H
