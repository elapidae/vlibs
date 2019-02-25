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


#ifndef VPOSIX_NETWORK_H
#define VPOSIX_NETWORK_H

#include <string>
#include <memory>



//=======================================================================================
//  https://linux.die.net/man/2/sendmsg
//
// Парсинг строк-адресов. Для Ip6 тоже.
//  http://www.opennet.ru/man.shtml?topic=inet_pton&category=3&russian=2
//
//  О чудо! Нормальное описание поведения epoll!
//  https://habr.com/post/416669/
//
//  getaddrinfo -- какая-то токсичная концентрация всего и сразу за один запрос.
//  http://www.opennet.ru/cgi-bin/opennet/man.cgi?topic=getaddrinfo&category=3
//
//  inet_pton <-> inet_ntop -- перевод из строк в куски sockaddr и наоборот.
//  http://www.opennet.ru/man.shtml?topic=inet_pton&category=3&russian=2
//=======================================================================================


//=======================================================================================
struct sockaddr;
struct sockaddr_in;
struct sockaddr_in6;
struct in_addr;
struct in6_addr;
//struct msghdr;
//=======================================================================================


//=======================================================================================
namespace vposix
{
    //===================================================================================
    //  Развязка между функциями и VIpAddress.
    enum class IpType
    {
        Unknown,
        Ip4, Ip6
    };

    struct my_ip_addr;
    //===================================================================================
    //  Для трассировки действий, чтобы вызовы можно было читать по человечески.
    class NetDebug
    {
    public:
        // level_str() и option_str() предназначен по convertToLevelAndOption

        //  Так понимаю, что используется для вызова setsockopt
        // SOL_SOCKET, IPPROTO_TCP, IPPROTO_IPV6, IPPROTO_IP
        static std::string level_str( int lvl );

        //  TODO: descr
        static std::string option_str( int opt );

        // AF_INET, AF_INET6, etc...
        static std::string domain_str( int domain );
        //  В разных частях api называют по разному.
        static std::string sa_family ( int domain ) { return domain_str(domain); }

        //  SOCK_DGRAM, SOCK_STREAM + flags NONBLOCK, CLOEXEC etc.
        static std::string type_str( int type );

        static std::string sa4_str( const sockaddr_in& addr );
        static std::string sa6_str( const sockaddr_in6& addr );
    };
    //===================================================================================
    //  Основной класс-контейнер оберток.
    class Socket
    {
        //===============================================================================
        static constexpr bool do_trace() { return false; }
        //static constexpr bool do_trace() { return true; }
        //===============================================================================

    public:
        //===============================================================================
        //  Развязка на тип socklen_t, который в документации называют недопониманием.
        using my_socklen_t = unsigned int;

        //===============================================================================
        //  У sockaddr_in6 есть еще два поля непонятного назначения:
        //      + uint32_t sin6_flowinfo;	// IPv6 flow information
        //      + uint32_t sin6_scope_id;	// IPv6 scope-id
        //      При появлении понимания что это за трава, стОит (или нет) добавить
        //      ее в инициализацию.
        //
        static void _init_sa4( sockaddr_in*  sa, const in_addr&  a, uint16_t port );
        static void _init_sa6( sockaddr_in6* sa, const in6_addr& a, uint16_t port );

        //  При чтении пользоваться только ими!
        static uint16_t _port_of_sa( const sockaddr_in& sa4 );
        static uint16_t _port_of_sa( const sockaddr_in6& sa6 );
        //===============================================================================

        //===============================================================================
        static std::string _inet_ntop( int af, const void *src );
        static bool _inet_pton( int af, const char *cp, void *buf );

        static std::string addr4_to_str( const in_addr&  src );
        static std::string addr6_to_str( const in6_addr& src );

        static std::string addr_to_str( const my_ip_addr& src );
        static bool str_to_addr( const std::string& src, my_ip_addr* dst );
        //===============================================================================

        //===============================================================================
        //  protocol = 0 ==> default for type...
        static int _socket( int domain, int type, int protocol = 0 );

        //  With NONBLOCK and CLOEXEC...
        static int tcp_socket( const my_ip_addr& for_ip_type );
        static int udp_socket( const my_ip_addr& for_ip_type );
        //===============================================================================

        //===============================================================================
        static bool listen( int fd, int queued_count );
        //===============================================================================

        //===============================================================================
        static void set_out_of_band_data( int fd );
        static void set_reuse_address( int fd );
        static void set_broadcast( int fd );
        static void set_ip_receive_packet_information( int fd );
        static void set_ip_receive_hop_limit( int fd );

        static void _setsockopt( int fd,
                                 int level,
                                 int optname,
                                 const void *optval,
                                 my_socklen_t optlen );
        //===============================================================================

        //===============================================================================
        static void _bind( int fd, const sockaddr* addr, my_socklen_t len );
        static void _bind_ip4( int fd, const sockaddr_in& addr );
        static void _bind_ip6( int fd, const sockaddr_in6& addr );
        static void bind( int fd, const my_ip_addr& addr, uint16_t port );
        //===============================================================================

        //===============================================================================
        // Не реализована, там трэшшшшЪ.
        static ssize_t _sendmsg( int fd, const struct msghdr *message, int flags );

        //  http://www.opennet.ru/man.shtml?category=2&russian=&topic=sendto
        //  flags -- битовая маска, м/б флаг NOPIPE...
        static ssize_t _sendto( int fd, const void *buf, size_t n, int flags,
                                const sockaddr* addr, my_socklen_t addr_len );

        static ssize_t _sendto_sa4(int fd, const void *buf, size_t n,
                                    int flags, const sockaddr_in &addr );
        static ssize_t _sendto_sa6(int fd, const void *buf, size_t n,
                                    int flags, const sockaddr_in6 &addr );

        static ssize_t send_to( int fd, const std::string& buf,
                                const my_ip_addr& addr, uint16_t port );
        //===============================================================================
        static ssize_t _send( int fd, const void *buf, size_t n, int flags );


        // Добавляет флаг MSG_NOSIGNAL, см. интернет.
//        static ssize_t sendto( int fd,
//                               const void* buf, size_t n,
//                               uint32_t addr, uint16_t port,
//                               int flags = 0 );

        // Добавляет флаг MSG_NOSIGNAL, см. интернет.
        static ssize_t send( int fd, const std::string& buf, int flags = 0 );
        //===============================================================================

        //===============================================================================
        static int _getsockname( int fd, sockaddr* addr, my_socklen_t* len );

        static void get_sock_addr( int fd, my_ip_addr* addr, uint16_t* port );

//        static int _getsockname( int fd, sockaddr_in* addr );
//        static uint32_t _get_host( const sockaddr_in& sock );
//        static uint16_t _get_port( const sockaddr_in& sock );
//        static void get_bind_point( int fd, uint32_t* host, uint16_t* port );
        //===============================================================================

        //===============================================================================
        // 0 or errno
        static int _connect_or_err( int fd, const sockaddr* addr,
                                    Socket::my_socklen_t len );
        static int  _connect_a4_or_err( int fd, const in_addr&  addr, uint16_t port );
        static int  _connect_a6_or_err( int fd, const in6_addr& addr, uint16_t port );

        static void connect( int fd, uint32_t addr, uint16_t port );
        static int  connect_or_err( int fd, const my_ip_addr& addr, uint16_t port );

        static int _accept4_or_err( int fd, sockaddr* addr, my_socklen_t *addr_len,
                                    int flags );
        static int _accept4_or_err( int fd, sockaddr_in* addr, int flags );

        //  With NONBLOCK & CLOEXEC
        static int accept_or_err( int fd, uint32_t* host, uint16_t* port );
        static int accept( int fd, uint32_t* host, uint16_t* port );
        //===============================================================================

        static void _getsockopt( int fd, int level, int optname,
                                 void *optval, my_socklen_t *optlen );
        static int32_t _getsockopt_int32( int fd, int level, int optname );
        //static Type get_type( int fd );
        //===============================================================================

        //===============================================================================
        static ssize_t _recv_or_err( int fd, void *buf, size_t n, int flags );
        static ssize_t _recv( int fd, void *buf, size_t n, int flags = 0 );
        static ssize_t pending_datagram_size( int fd );

        static ssize_t _recvfrom( int fd, void *buf, size_t n,int flags,
                                  sockaddr* addr, my_socklen_t* addr_len );
        static ssize_t _recvfrom_sa4( int fd, void *buf, size_t n, int flags,
                                      sockaddr_in* addr );
        static ssize_t _recvfrom_sa6( int fd, void *buf, size_t n, int flags,
                                      sockaddr_in6* addr );

        //  src used for seems to need protocol.
        static ssize_t receive_from(int fd, void *buf, size_t n,
                                     my_ip_addr* dst, uint16_t* port );
        //===============================================================================

    }; // Socket
    //===================================================================================

    //===================================================================================
}  // namespace vposix
//=======================================================================================



#endif // VPOSIX_NETWORK_H
