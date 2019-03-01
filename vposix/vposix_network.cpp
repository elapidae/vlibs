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


#include "vposix_network.h"

#include <sys/socket.h>
#include "verror.h"
#include "vlog.h"

#include <string.h>     // only for memset()
#include <netinet/in.h> // sockeaddr_in
#include <assert.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "vposix_core.h"
#include "vposix_network_ip.h"

using namespace vposix;


//=======================================================================================
//Socket::Type Socket::get_type( int fd )
//{
//    auto t = _getsockopt_int32( fd, SOL_SOCKET, SO_TYPE );
//    switch (t)
//    {
//    case SOCK_STREAM: return Type::STREAM;
//    case SOCK_DGRAM:  return Type::DGRAM;
//    }
//    throw verror( "Unknown socket type: ", t );
//}
//=======================================================================================
ssize_t Socket::_recv_or_err( int fd, void *buf, size_t n, int flags )
{
    if ( do_trace() ) vtrace( "V::recv(", fd, buf, n, flags, ")" );

    return Core::linux_call_or_err( ::recv, fd, buf, n, flags );
}
//=======================================================================================
ssize_t Socket::pending_datagram_size(int fd)
{
    char c;
    auto res = _recv_or_err( fd, &c, 1, MSG_PEEK | MSG_TRUNC );
    if ( res == -1 )
    {
        Errno e;
        if ( e.again_or_wouldblock() ) return 0;
        e.throw_verror( "pending_datagram_size" );
    }
    return res;
}
//=======================================================================================
ssize_t Socket::_recvfrom( int fd, void *buf, size_t n, int flags,
                           sockaddr* addr, my_socklen_t* addr_len )
{
    assert( buf && n > 0 );

    return Core::linux_call( ::recvfrom, "::recvfrom",
                             fd, buf, n, flags, addr, addr_len );
}
//=======================================================================================
ssize_t Socket::_recvfrom_sa4( int fd, void *buf, size_t n, int flags, sockaddr_in *addr)
{
    auto ptr = static_cast<sockaddr*>( static_cast<void*>(addr) );
    socklen_t len = sizeof( *addr );
    auto res = _recvfrom( fd, buf, n, flags, ptr, &len );

    assert( len == sizeof(*addr) );
    assert( addr->sin_family == AF_INET );
    return res;
}
//=======================================================================================
ssize_t Socket::_recvfrom_sa6(int fd, void *buf, size_t n, int flags, sockaddr_in6* addr)
{
    auto ptr = static_cast<sockaddr*>( static_cast<void*>(addr) );
    socklen_t len = sizeof( *addr );
    auto res = _recvfrom( fd, buf, n, flags, ptr, &len );

    assert( len == sizeof(*addr) );
    assert( addr->sin6_family == AF_INET6 );
    return res;
}
//=======================================================================================
ssize_t Socket::receive_from( int fd, void *buf, size_t n,
                              my_ip_addr *dst, uint16_t *port )
{
    sockaddr_in6 sa6;
    auto *sa = static_cast<sockaddr*>( static_cast<void*>(&sa6) );
    socklen_t len = sizeof(sa6);
    int flags = MSG_NOSIGNAL;
    auto res = _recvfrom( fd, buf, n, flags, sa, &len );

    if ( sa->sa_family == AF_INET )
    {
        auto *sa4 = static_cast<sockaddr_in*>(static_cast<void*>(sa) );
        assert( len == sizeof(*sa4) );

        dst->set_a4( sa4->sin_addr );
        *port = _port_of_sa( *sa4 );
        return res;
    }

    if ( sa->sa_family == AF_INET6 )
    {
        assert( len == sizeof(sa6) );

        dst->set_a6( sa6.sin6_addr );
        *port = _port_of_sa( sa6 );
        return res;
    }

    throw verror( "Bad received: family=", sa->sa_family );
}
//=======================================================================================
//ssize_t Socket::recvfrom( int fd, void *buf, size_t n, int flags,
//                          uint32_t *host, uint16_t *port )
//{
//    assert( host && port );

//    sockaddr_in res_addr;
//    auto res = _recvfrom( fd, buf, n, flags, &res_addr );
//    *host = _get_host( res_addr );
//    *port = _get_port( res_addr );
//    return res;
//}
//=======================================================================================
ssize_t Socket::_recv( int fd, void *buf, size_t n, int flags )
{
    auto res = _recv_or_err( fd, buf, n, flags );
    if ( res < 0 )
        Errno().throw_verror( "Socket::recv" );
    return res;
}
//=======================================================================================



//=======================================================================================
//      ::socket
//=======================================================================================
//  protocol == 0 --> default for domain & type.
int Socket::_socket( int domain, int type, int protocol )
{
    if ( do_trace() )
        vtrace.nospace()( "V::socket( ", NetDebug::domain_str(domain), ", ",
                          NetDebug::type_str(type), ", protocol=", protocol, " )" );

    if ( protocol != 0 ) vwarning( "Non standard protocol =", protocol );

    return Core::linux_call( ::socket, "::socket", domain, type, protocol );
}
//=======================================================================================
int Socket::tcp_socket( const my_ip_addr& for_ip_type )
{
    return _socket( for_ip_type.af(), SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC );
}
//=======================================================================================
int Socket::udp_socket( const my_ip_addr& for_ip_type )
{
    return _socket( for_ip_type.af(), SOCK_DGRAM | SOCK_NONBLOCK | SOCK_CLOEXEC );
}
//=======================================================================================
//      ::socket
//=======================================================================================


//=======================================================================================
void Socket::_setsockopt( int fd, int level, int optname,
                          const void *optval, my_socklen_t optlen )
{
    static_assert ( std::is_same<my_socklen_t, ::socklen_t>::value, "" );

    if ( do_trace() )
    {
        std::string val;
        if ( optlen == sizeof(int) )
            val = vcat("[int=", *static_cast<const int*>(optval), ']');
        else throw verror("Crypted optval with size = ", optlen);

        vtrace.nospace()( "V::setsockopt("
                          "fd:", fd,
                          ", ", NetDebug::level_str(level),
                          ", ", NetDebug::option_str(optname),
                          ", ", val, " )" );
    }

    Core::linux_call( ::setsockopt, "::setsockopt", fd, level, optname, optval, optlen );
}
//=======================================================================================
void Socket::_init_sa4( sockaddr_in *sa, const in_addr& a, uint16_t port )
{
    bzero( sa, sizeof(*sa) );
    sa->sin_family = AF_INET;
    sa->sin_addr   = a;
    sa->sin_port   = htons( port );
}
//=======================================================================================
void Socket::_init_sa6( sockaddr_in6 *sa, const in6_addr& a, uint16_t port )
{
    bzero( sa, sizeof(*sa) );
    sa->sin6_family = AF_INET6;
    sa->sin6_addr   = a;
    sa->sin6_port   = htons( port );
}
//=======================================================================================
uint16_t Socket::_port_of_sa( const sockaddr_in& sa4 )
{
    return ntohs( sa4.sin_port );
}
//=======================================================================================
uint16_t Socket::_port_of_sa( const sockaddr_in6& sa6 )
{
    return ntohs( sa6.sin6_port );
}
//=======================================================================================
void Socket::_bind( int fd, const sockaddr *addr, my_socklen_t len )
{
    if ( do_trace() ) vtrace.nospace()( "V::bind( ", fd, ", ", addr, ", ", len, " )" );
    auto res = Core::linux_call( ::bind, "::bind", fd, addr, len );
    assert( res == 0 );
}
//=======================================================================================
void Socket::_bind_ip4( int fd, const sockaddr_in& addr )
{
    auto ptr = static_cast<const sockaddr*>( static_cast<const void*>(&addr) );
    _bind( fd, ptr, sizeof(addr) );
}
//=======================================================================================
void Socket::_bind_ip6( int fd, const sockaddr_in6& addr )
{
    auto ptr = static_cast<const sockaddr*>( static_cast<const void*>(&addr) );
    _bind( fd, ptr, sizeof(addr) );
}
//=======================================================================================
void Socket::bind( int fd, const my_ip_addr& addr, uint16_t port )
{
    if ( addr.ip_type == IpType::Ip4 )
    {
        sockaddr_in sock;
        _init_sa4( &sock, addr.ip4, port );
        _bind_ip4( fd, sock );
        return;
    }
    if ( addr.ip_type == IpType::Ip6 )
    {
        sockaddr_in6 sock;
        _init_sa6( &sock, addr.ip6, port );
        _bind_ip6( fd, sock );
        return;
    }
    throw verror("Bind to unknown address.");
}
//=======================================================================================
//=======================================================================================
//int Socket::_getsockname( int fd, sockaddr_in* addr )
//{
//    auto ptr = static_cast<sockaddr*>( static_cast<void*>(addr) );
//    my_socklen_t len = sizeof(sockaddr_in);
//    auto res = _getsockname( fd, ptr, &len );
//    assert( len == sizeof(sockaddr_in) );
//    return res;
//}
//=======================================================================================
//uint32_t Socket::_get_host( const sockaddr_in& sock )
//{
//    assert( sock.sin_family == AF_INET );
//    return ntohl( sock.sin_addr.s_addr );
//}
//=======================================================================================
//uint16_t Socket::_get_port( const sockaddr_in& sock )
//{
//    assert( sock.sin_family == AF_INET );
//    return ntffohs_BADDDD( sock.sin_port );
//}
//=======================================================================================
//void Socket::get_bind_point( int fd, uint32_t* host, uint16_t* port )
//{
//    sockaddr_in addr;
//    _getsockname( fd, &addr );
//    *host = _get_host( addr );
//    *port = _get_port( addr );
//}
//=======================================================================================
bool Socket::listen( int fd, int queued_count )
{
    if ( do_trace() ) vtrace( "V::listen(", fd, queued_count, ")" );
    return 0 == Core::linux_call( ::listen, "::listen", fd, queued_count );
}
//=======================================================================================
int Socket::_connect_or_err( int fd, const sockaddr* addr, my_socklen_t len )
{
    if ( do_trace() ) vtrace( "V::connect(", fd, addr->sa_family, len, ");" );
    return Core::linux_call_or_err( ::connect, fd, addr, len );
}
//=======================================================================================
int Socket::_connect_a4_or_err( int fd, const in_addr &addr, uint16_t port )
{
    sockaddr_in sa;
    _init_sa4( &sa, addr, port );
    auto ptr = static_cast<sockaddr*>( static_cast<void*>(&sa) );
    return _connect_or_err( fd, ptr, sizeof(sa) );
}
//=======================================================================================
int Socket::_connect_a6_or_err( int fd, const in6_addr& addr, uint16_t port )
{
    sockaddr_in6 sa;
    _init_sa6( &sa, addr, port );
    auto ptr = static_cast<sockaddr*>( static_cast<void*>(&sa) );
    return _connect_or_err( fd, ptr, sizeof(sa) );
}
//=======================================================================================
int Socket::connect_or_err( int fd, const my_ip_addr& addr, uint16_t port )
{
    if ( addr.ip_type == IpType::Ip4 )
        return _connect_a4_or_err( fd, addr.ip4, port );

    if ( addr.ip_type == IpType::Ip6 )
        return _connect_a6_or_err( fd, addr.ip6, port );

    throw verror("Bad ip");
}
//=======================================================================================


//=======================================================================================
int Socket::_accept4_or_err( int fd, sockaddr* addr, my_socklen_t *addr_len, int flags)
{
    if ( do_trace() ) vtrace("V::accept(", fd, addr->sa_family, addr_len, flags, ");");

    return Core::linux_call_or_err( ::accept4, fd, addr, addr_len, flags );
}
//=======================================================================================
int Socket::_accept4_or_err( int fd, sockaddr_in *addr, int flags )
{
    auto ptr = static_cast<sockaddr*>( static_cast<void*>(addr) );
    ::socklen_t slen = sizeof( sockaddr_in );
    auto res = _accept4_or_err( fd, ptr, &slen, flags );
    if (res < 0) return res;

    assert( slen == sizeof(sockaddr_in) );
    assert( addr->sin_family == AF_INET );
    return res;
}
//=======================================================================================
int Socket::accept_or_err( int fd, uint32_t *host, uint16_t *port )
{
    assert( host && port );

    int flags = SOCK_NONBLOCK | SOCK_CLOEXEC;

    sockaddr_in sock;
    bzero( &sock, sizeof(sock) );
    auto res = _accept4_or_err( fd, &sock, flags );
    if ( res < 0 ) return res;

    *host = ntohl( sock.sin_addr.s_addr );
    *port = _port_of_sa( sock );
    return res;
}
//=======================================================================================
int Socket::accept( int fd, uint32_t *host, uint16_t *port )
{
    auto res = accept_or_err( fd, host, port );
    if (res < 0) Errno().throw_verror( vcat("accept(", fd, ")") );
    return res;
}
//=======================================================================================
ssize_t Socket::_sendmsg( int fd, const msghdr *message, int flags )
{
    assert(false);
    (void)fd; (void)message; (void)flags;
    //return linux_call_eintr<ssize_t>( ::sendmsg );
}
//=======================================================================================
ssize_t Socket::_sendto( int fd, const void *buf, size_t n, int flags,
                         const sockaddr* addr, my_socklen_t addr_len )
{
    if ( do_trace() ) vtrace("V::sendto(", fd, buf, n, flags, '[', addr_len, "] )" );

    return Core::linux_call( ::sendto, "::sendto", fd, buf, n, flags, addr, addr_len );
}
//=======================================================================================
ssize_t Socket::_sendto_sa4( int fd, const void *buf, size_t n, int flags,
                             const sockaddr_in& addr )
{
    if ( do_trace() ) vtrace << "To: " << NetDebug::sa4_str( addr );

    auto ptr = static_cast<const sockaddr*>( static_cast<const void*>(&addr) );
    return _sendto( fd, buf, n, flags, ptr, sizeof(addr) );
}
//=======================================================================================
ssize_t Socket::_sendto_sa6( int fd, const void *buf, size_t n, int flags,
                             const sockaddr_in6& addr )
{
    if ( do_trace() ) vtrace << "To: " << NetDebug::sa6_str( addr );

    auto ptr = static_cast<const sockaddr*>( static_cast<const void*>(&addr) );
    return _sendto( fd, buf, n, flags, ptr, sizeof(addr) );
}
//=======================================================================================
ssize_t Socket::send_to( int fd, const std::string &buf, const my_ip_addr &addr,
                         uint16_t port )
{
    if ( addr.ip_type == IpType::Ip4 )
    {
        sockaddr_in sa4;
        _init_sa4( &sa4, addr.ip4, port );
        return _sendto_sa4( fd, buf.c_str(), buf.size(), MSG_NOSIGNAL, sa4 );
    }
    if ( addr.ip_type == IpType::Ip6 )
    {
        sockaddr_in6 sa6;
        _init_sa6( &sa6, addr.ip6, port );
        return _sendto_sa6( fd, buf.c_str(), buf.size(), MSG_NOSIGNAL, sa6 );
    }
    throw verror("Bad ip type");
}
//=======================================================================================
ssize_t Socket::_send( int fd, const void *buf, size_t n, int flags )
{
    return Core::linux_call( ::send, "::send", fd, buf, n, flags );
}
//=======================================================================================
ssize_t Socket::send( int fd, const std::string &buf, int flags )
{
    return _send( fd, buf.c_str(), buf.size(), flags | MSG_NOSIGNAL );
}
//=======================================================================================


//=======================================================================================
int Socket::_getsockname( int fd, sockaddr* addr, my_socklen_t* len )
{
    return Core::linux_call( ::getsockname, "::getsockname", fd, addr, len );
}
//=======================================================================================
void Socket::get_sock_addr( int fd, my_ip_addr* addr, uint16_t *port )
{
    sockaddr_in6 sa6{};
    auto v_ptr = static_cast<void*>(&sa6);
    auto *sa_ptr = static_cast<sockaddr*>( v_ptr );
    my_socklen_t len = sizeof( sa6 );
    _getsockname( fd, sa_ptr, &len );

    if ( sa_ptr->sa_family == AF_INET )
    {
        auto sa4 = static_cast<sockaddr_in*>(v_ptr);
        assert( len == sizeof(*sa4) );
        addr->set_a4( sa4->sin_addr );
        *port = _port_of_sa( *sa4 );
        return;
    }

    if ( sa_ptr->sa_family == AF_INET6 )
    {
        assert( len == sizeof(sa6) );
        addr->set_a6( sa6.sin6_addr );
        *port = _port_of_sa( sa6 );
        return;
    }

    throw verror("Bad socket address");
}
//=======================================================================================


//=======================================================================================
//int Socket::_socket( IpType ip_type, int type, Cloexec ce, Nonblock nb )
//{
//    int domain = ip_type == IpType::Ip4 ? AF_INET
//               : ip_type == IpType::Ip6 ? AF_INET6
//               : (throw verror("Bad ip type"));

//    if ( ce == Cloexec::Yes  ) typ |= SOCK_CLOEXEC;
//    if ( nb == Nonblock::Yes ) typ |= SOCK_NONBLOCK;

//    return _socket( domain, typ, 0 );
//}
//=======================================================================================
void Socket::set_out_of_band_data( int fd )
{
    int val = 1;
    _setsockopt( fd, SOL_SOCKET, SO_OOBINLINE, &val, sizeof(val) );
}
//=======================================================================================
void Socket::set_reuse_address( int fd )
{
    int val = 1;
    _setsockopt( fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val) );
}
//=======================================================================================
void Socket::set_broadcast( int fd )
{
    int val = 1;
    _setsockopt( fd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val) );
}
//=======================================================================================
void Socket::set_ip_receive_packet_information( int fd )
{
    int val = 1;
    _setsockopt( fd, IPPROTO_IP, IP_PKTINFO, &val, sizeof(val) );
}
//=======================================================================================
void Socket::set_ip_receive_hop_limit( int fd )
{
    int val = 1;
    _setsockopt( fd, IPPROTO_IP, IP_RECVTTL, &val, sizeof(val) );
}
//=======================================================================================


//=======================================================================================
void Socket::_getsockopt( int fd, int level, int optname,
                          void *optval, my_socklen_t *optlen )
{
    //auto res = Core::linux_call<int>(::getsockopt, fd, level, optname, optval, optlen);
    auto res = Core::linux_call( ::getsockopt, "::getsockopt",
                                 fd, level, optname, optval, optlen );
    assert( res == 0 );
}
//=======================================================================================
int32_t Socket::_getsockopt_int32( int fd, int level, int optname )
{
    int32_t opt;
    socklen_t len = sizeof( opt );
    _getsockopt( fd, level, optname, &opt, &len );
    assert( len == sizeof(opt) );
    return opt;
}
//=======================================================================================



//=======================================================================================
//      Net
//=======================================================================================
//  Используется, чтобы проверять и сразу же сбрасывать флаги и значения.
//  Пример использования см. в Net::type_str()
static bool check_and_clear( int *smth, int flag )
{
    bool res = *smth & flag;
    *smth &= ~flag;
    return res;
}
//=======================================================================================
std::string NetDebug::level_str( int lvl )
{
    switch ( lvl )
    {
    case SOL_SOCKET:    return "SOL_SOCKET";
    case IPPROTO_TCP:   return "IPPROTO_TCP";
    case IPPROTO_IPV6:  return "IPPROTO_IPV6";
    case IPPROTO_IP:    return "IPPROTO_IP";
    }
    throw verror( "Unknown Net::level type: ", lvl );
}
//=======================================================================================
std::string NetDebug::option_str( int opt )
{
    switch (opt)
    {
    case SO_OOBINLINE:  return "SO_OOBINLINE";
    case SO_REUSEADDR:  return "SO_REUSEADDR";
    case SO_BROADCAST:  return "SO_BROADCAST";
    case IP_PKTINFO:    return "IP_PKTINFO";
    case IP_RECVTTL:    return "IP_RECVTTL";
    }
    throw verror( "Unknown Net::option type: ", opt );
}
//=======================================================================================
std::string NetDebug::domain_str( int domain )
{
    switch (domain)
    {
    case AF_INET:  return "AF_INET";
    case AF_INET6: return "AF_INET_6";
    }
    throw verror( "Unknown Net::domain type: ", domain );
}
//=======================================================================================
std::string NetDebug::type_str( int type )
{
    std::string res;

    if      ( check_and_clear(&type, SOCK_DGRAM)  ) res = "SOCK_DGRAM";
    else if ( check_and_clear(&type, SOCK_STREAM) ) res = "SOCK_STREAM";
    else throw verror("Unknown Net::type = ", type);

    if ( check_and_clear(&type, SOCK_CLOEXEC)  ) res += "|CLOEXEC";
    if ( check_and_clear(&type, SOCK_NONBLOCK) ) res += "|NONBLOCK";

    if ( type != 0 ) throw verror("Not all flags cauched, type = ", type);

    return res;
}
//=======================================================================================
std::string NetDebug::sa4_str( const sockaddr_in& addr )
{
    return vcat("::sockaddr_in{fam:", NetDebug::sa_family(addr.sin_family), ",")
               ("addr:", Socket::addr4_to_str(addr.sin_addr), ",")
                .dec()("port:", addr.sin_port, "}" );
}
//=======================================================================================
std::string NetDebug::sa6_str( const sockaddr_in6 &addr )
{
    assert(false);
    (void)addr;
}
//=======================================================================================
//      NetDebug
//=======================================================================================



//=======================================================================================
//      Addr
//=======================================================================================
std::string Socket::_inet_ntop( int af, const void *src )
{
    // Так всегда места хватит :).
    static constexpr auto addr_len = INET6_ADDRSTRLEN + INET_ADDRSTRLEN;

    char buf[ addr_len ];
    auto cres = ::inet_ntop( af, src, buf, socklen_t(addr_len) );
    assert( cres );
    return cres;
}
//=======================================================================================
std::string Socket::addr4_to_str( const in_addr &src )
{
    return Socket::_inet_ntop( AF_INET, &src );
}
//=======================================================================================
std::string Socket::addr6_to_str( const in6_addr &src )
{
    return Socket::_inet_ntop( AF_INET6, &src );
}
//=======================================================================================
std::string Socket::addr_to_str( const my_ip_addr& src )
{
    switch ( src.ip_type )
    {
    case IpType::Ip4: return addr4_to_str( src.ip4 );
    case IpType::Ip6: return addr6_to_str( src.ip6 );
    default: break;
    }
    throw verror("Bad ip addr");
}
//=======================================================================================
//=======================================================================================
//  int inet_pton(int af, const char *src, void *dst);
//  returns
//      1 on success (network address was successfully converted).
//
//      0 is returned if src does not contain a character string representing a valid
//          network address in the specified address family.
//
//      If af does not contain a valid address family,
//      -1 is returned and errno is set to EAFNOSUPPORT.
//
bool Socket::_inet_pton( int af, const char *cp, void *buf )
{
    if ( do_trace() )
        vtrace( "::inet_pton(", NetDebug::sa_family(af), cp, ");" );

    return 1 == Core::linux_call( ::inet_pton, "::inet_pton", af, cp, buf );
}
//=======================================================================================
static bool from_str_ip4( const std::string& src, in_addr* dst )
{
    return Socket::_inet_pton( AF_INET, src.c_str(), dst );
}
//=======================================================================================
static bool from_str_ip6( const std::string& src, in6_addr* dst )
{
    return Socket::_inet_pton( AF_INET6, src.c_str(), dst );
}
//=======================================================================================
bool Socket::str_to_addr( const std::string &src, my_ip_addr* dst )
{
    dst->ip_type = IpType::Unknown;

    if ( from_str_ip4(src, &dst->ip4) )
    {
        dst->ip_type = IpType::Ip4;
        return true;
    }

    if ( from_str_ip6(src, &dst->ip6) )
    {
        dst->ip_type = IpType::Ip6;
        return true;
    }

    return false;
}
//=======================================================================================
