#include "vposix_network.h"

#include <sys/socket.h>
#include "verror.h"
#include "vlog_pretty.h"

#include <string.h>     // only for memset()
#include <netinet/in.h> // sockeaddr_in
#include <assert.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "vposix_core.h"

using namespace vposix;


//=======================================================================================
static int raw_domain( Socket::Domain d )
{
    switch (d)
    {
    case Socket::Domain::Inet4: return AF_INET;
    case Socket::Domain::Inet6: return AF_INET6;
    }
    throw verror << "Domain";
}
//=======================================================================================

//=======================================================================================
static int raw_type( Socket::Type t )
{
    switch (t)
    {
    case Socket::Type::STREAM:  return SOCK_STREAM;
    case Socket::Type::DGRAM:   return SOCK_DGRAM;
    }
    throw verror( "Type: ", int(t) );
}
//=======================================================================================
Socket::Type Socket::get_type( int fd )
{
    auto t = _getsockopt_int32( fd, SOL_SOCKET, SO_TYPE );
    switch (t)
    {
    case SOCK_STREAM: return Type::STREAM;
    case SOCK_DGRAM:  return Type::DGRAM;
    }
    throw verror( "Unknown socket type: ", t );
}
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
        if ( e.eagain() ) return 0;
        e.throw_verror( "pending_datagram_size" );
    }
    return res;
}
//=======================================================================================
ssize_t Socket::_recvfrom( int fd, void *buf, size_t n, int flags,
                           sockaddr *addr, my_socklen_t* addr_len )
{
    assert( buf && n > 0 );

    return Core::linux_call( ::recvfrom, "Socket::_recvfrom",
                             fd, buf, n, flags, addr, addr_len );
}
//=======================================================================================
ssize_t Socket::_recvfrom( int fd, void *buf, size_t n, int flags, sockaddr_in *addr )
{
    auto ptr = static_cast<sockaddr*>( static_cast<void*>(addr) );
    socklen_t len = sizeof( sockaddr_in );
    auto res = _recvfrom( fd, buf, n, flags, ptr, &len );

    assert( len == sizeof(sockaddr_in) );
    assert( addr->sin_family == AF_INET );
    return res;
}
//=======================================================================================
ssize_t Socket::recvfrom( int fd, void *buf, size_t n, int flags,
                          uint32_t *host, uint16_t *port )
{
    assert( host && port );

    sockaddr_in res_addr;
    auto res = _recvfrom( fd, buf, n, flags, &res_addr );
    *host = _get_host( res_addr );
    *port = _get_port( res_addr );
    return res;
}
//=======================================================================================
ssize_t Socket::recv( int fd, void *buf, size_t n, int flags )
{
    auto res = _recv_or_err( fd, buf, n, flags );
    if ( res < 0 )
        Errno().throw_verror( "Socket::recv" );
    return res;
}
//=======================================================================================



//=======================================================================================
int Socket::_socket( int domain, int type, int protocol )
{
    if ( do_trace() )
        vtrace.nospace()( "V::socket( ", Net::domain_str(domain), ", ",
                          Net::type_str(type), ", protocol=", protocol, " )" );

    return Core::linux_call( ::socket, "::socket", domain, type, protocol );
}
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
                          ", ", Net::level_str(level),
                          ", ", Net::option_str(optname),
                          ", ", val, " )" );
    }

    Core::linux_call( ::setsockopt, "::setsockopt", fd, level, optname, optval, optlen );
}
//=======================================================================================
void Socket::_init_sockaddr_in( uint32_t host, uint16_t port, sockaddr_in *sock )
{
    memset( sock, 0, sizeof(sockaddr_in));
    sock->sin_family        = AF_INET;
    sock->sin_port          = htons( port );
    sock->sin_addr.s_addr   = htonl( host );
}
//=======================================================================================
std::string Socket::_str_sockaddr_in( const sockaddr_in &addr )
{
    return vcat("::sockaddr_in{fam:", addr.sin_family, ",")
                .hex()("addr:", addr.sin_addr.s_addr, ",")
                .dec()("port:", addr.sin_port, "}" );
}
//=======================================================================================
void Socket::bind( int fd, uint32_t host, uint16_t port )
{
    sockaddr_in sock;
    _init_sockaddr_in( host, port, &sock );
    _bind( fd, sock );
}
//=======================================================================================
int Socket::_bind( int fd, const sockaddr *addr, Socket::my_socklen_t len )
{
    if ( do_trace() ) vtrace.nospace()( "V::bind( ", fd, ", ", addr, ", ", len, " )" );

    //return Core::linux_call<int>( ::bind, fd, addr, len );
    return Core::linux_call( ::bind, "::bind", fd, addr, len );
}
//=======================================================================================
int Socket::_bind( int fd, const sockaddr_in& addr )
{
    auto ptr = static_cast<const sockaddr*>( static_cast<const void*>(&addr) );
    return _bind( fd, ptr, sizeof(addr) );
}
//=======================================================================================
int Socket::_getsockname( int fd, sockaddr* addr, Socket::my_socklen_t *len )
{
    //return Core::linux_call<int>( ::getsockname, fd, addr, len );
    return Core::linux_call( ::getsockname, "::getsockname", fd, addr, len );
}
//=======================================================================================
int Socket::_getsockname( int fd, sockaddr_in* addr )
{
    auto ptr = static_cast<sockaddr*>( static_cast<void*>(addr) );
    my_socklen_t len = sizeof(sockaddr_in);
    auto res = _getsockname( fd, ptr, &len );
    assert( len == sizeof(sockaddr_in) );
    return res;
}
//=======================================================================================
uint32_t Socket::_get_host( const sockaddr_in& sock )
{
    assert( sock.sin_family == AF_INET );
    return ntohl( sock.sin_addr.s_addr );
}
//=======================================================================================
uint16_t Socket::_get_port( const sockaddr_in& sock )
{
    assert( sock.sin_family == AF_INET );
    return ntohs( sock.sin_port );
}
//=======================================================================================
void Socket::get_bind_point( int fd, uint32_t* host, uint16_t* port )
{
    sockaddr_in addr;
    _getsockname( fd, &addr );
    *host = _get_host( addr );
    *port = _get_port( addr );
}
//=======================================================================================
bool Socket::listen( int fd, int queued_count )
{
    if ( do_trace() ) vtrace( "V::listen(", fd, queued_count, ")" );
    //return 0 == Core::linux_call<int>( ::listen, fd, queued_count );
    return 0 == Core::linux_call( ::listen, "::listen", fd, queued_count );
}
//=======================================================================================
int Socket::_connect_or_err( int fd, const sockaddr *addr,
                             Socket::my_socklen_t len )
{
    if ( do_trace() ) vtrace( "V::connect_eintr(", fd, addr->sa_family, len, ");" );
    return Core::linux_call_or_err( ::connect, fd, addr, len );
}
//=======================================================================================
void Socket::connect( int fd, uint32_t addr, uint16_t port )
{
    sockaddr_in sock;
    auto ptr = static_cast<sockaddr*>( static_cast<void*>(&sock) );
    _init_sockaddr_in( addr, port, &sock );
    auto res = _connect_or_err( fd, ptr, sizeof(sock) );
    if ( res != -1 ) return;
    Errno().throw_verror( "Socket::connect" );
}
//=======================================================================================
int Socket::connect_or_err( int fd, uint32_t addr, uint16_t port )
{
    sockaddr_in sock;
    auto ptr = static_cast<sockaddr*>( static_cast<void*>(&sock) );
    _init_sockaddr_in( addr, port, &sock );
    return _connect_or_err( fd, ptr, sizeof(sock) );
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
    *port = ntohs( sock.sin_port        );
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
//int inet_aton(const char *cp, struct in_addr *inp);
//inet_aton() преобразовывает обычный вид IP-адреса cp (из номеров и точек) в двоичный код и сохраняет его в структуре, на которую указывает inp. inet_aton возвращает ненулевое значение, если адрес правильный, и возвращает ноль, если он неверен.
uint32_t Socket::parse_ip( Socket::cstr addr )
{
    in_addr res;
    auto ok = inet_aton( addr.c_str(), &res );
    if (ok == 0) throw verror("Incorrect address '", addr, "'.");
    return ntohl( res.s_addr );
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
    if ( do_trace() ) vtrace("V::sendto(", fd, buf, n, flags, addr, addr_len, ")" );

    return Core::linux_call( ::sendto, "::sendto", fd, buf, n, flags, addr, addr_len );
}
//=======================================================================================
ssize_t Socket::_sendto( int fd, const void *buf, size_t n, int flags,
                         const sockaddr_in *addr )
{
    if ( do_trace() ) vtrace << "To: " << _str_sockaddr_in(*addr);

    auto ptr = static_cast<const sockaddr*>( static_cast<const void*>(addr) );
    return _sendto( fd, buf, n, flags, ptr, sizeof(::sockaddr_in) );
}
//=======================================================================================
ssize_t Socket::_send(int fd, const void *buf, size_t n, int flags)
{
    return Core::linux_call( ::send, "::send", fd, buf, n, flags );
}
//=======================================================================================
ssize_t Socket::sendto( int fd,
                        const void *buf, size_t n,
                        uint32_t addr, uint16_t port,
                        int flags )
{
    flags |= MSG_NOSIGNAL;
    sockaddr_in sock;
    _init_sockaddr_in( addr, port, &sock );
    return _sendto( fd, buf, n, flags, &sock );
}
//=======================================================================================
ssize_t Socket::send( int fd, const std::string &buf, int flags )
{
    return _send( fd, buf.c_str(), buf.size(), flags | MSG_NOSIGNAL );
}
//=======================================================================================


//=======================================================================================
int Socket::socket( Domain domain, Type type, Cloexec ce, Nonblock nb )
{
    int d = raw_domain( domain );
    int t = raw_type( type );
    if ( ce == Cloexec::Yes  ) t |= SOCK_CLOEXEC;
    if ( nb == Nonblock::Yes ) t |= SOCK_NONBLOCK;

    return _socket( d, t, 0 );
}
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
//  Используется, чтобы проверять и сразу же сбрасывать флаги и значения.
//  Пример использования см. в Net::type_str()
static bool check_and_clear( int* smth, int flag )
{
    bool res = *smth & flag;
    *smth &= ~flag;
    return res;
}
//=======================================================================================
std::string Net::level_str( int lvl )
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
std::string Net::option_str( int opt )
{
    switch (opt)
    {
    case SO_OOBINLINE: return "SO_OOBINLINE";
    case SO_REUSEADDR: return "SO_REUSEADDR";
    }
    throw verror( "Unknown Net::option type: ", opt );
}
//=======================================================================================
std::string Net::domain_str( int domain )
{
    switch (domain)
    {
    case AF_INET:  return "AF_INET";
    case AF_INET6: return "AF_INET_6";
    }
    throw verror( "Unknown Net::domain type: ", domain );
}
//=======================================================================================
std::string Net::type_str( int type )
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



//=======================================================================================
std::string SockAddr::_ntop( int af, const void *src, char *dst, size_t cnt )
{
    auto cres = ::inet_ntop( af, src, dst, socklen_t(cnt) );
    assert( cres );
    return cres;
}
//=======================================================================================
std::string SockAddr::str( const in_addr& src )
{
    char buf[INET_ADDRSTRLEN];
    return _ntop( AF_INET, &src, buf, INET_ADDRSTRLEN );
}
//=======================================================================================
