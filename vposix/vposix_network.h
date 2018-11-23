#ifndef VPOSIX_NETWORK_H
#define VPOSIX_NETWORK_H

#include <string>
#include <memory>



//=======================================================================================
//  https://linux.die.net/man/2/sendmsg
//=======================================================================================


//=======================================================================================
struct sockaddr;
struct sockaddr_in;
struct msghdr;
//=======================================================================================


//=======================================================================================
namespace vposix
{
    //===================================================================================
    class Socket
    {
        static constexpr bool do_trace() { return false; }

    public:
        using my_socklen_t = unsigned int;
        using cstr = const std::string&;

        //  Wrappers for AF_* defines.
        enum class Domain
        {
            Inet4,  //  AF_INET
            Inet6   //  AF_INET6
        };

        //  Wrapper for SOCK_* defines.
        enum class Type
        {
            STREAM = 1,         //  Sequenced, reliable, connection-based byte streams.
            DGRAM = 2,          //  Connectionless, unreliable datagrams of fixed
                                //  maximum length.
        };

        //  Flags to be ORed into the type parameter of socket and socketpair and
        //  used for the flags parameter of paccept.
        enum class Cloexec  { No = 0, Yes = 02000000 };
        enum class Nonblock { No = 0, Yes = 00004000 };

        enum class Option
        {
            OutOfBandData,      //  SO_OOBINLINE
            AddressReusable     //  SO_REUSEADDR
        };

        static int socket( Domain   domain,
                           Type     type,
                           Cloexec  ce = Cloexec::Yes,
                           Nonblock nb = Nonblock::Yes
                          ); // protocol by default = 0...

        static void set_out_of_band_data( int fd );
        static void set_reuse_address( int fd );
        static void set_broadcast( int fd );
        static void set_ip_receive_packet_information( int fd );
        static void set_ip_receive_hop_limit( int fd );

        static int _socket( int domain, int type, int protocol );

        static void _setsockopt( int fd,
                                int level,
                                int optname,
                                const void *optval,
                                my_socklen_t optlen );

        static std::shared_ptr<sockaddr_in> new_sockaddr_in(uint32_t host,uint16_t port);
        static void _init_sockaddr_in( uint32_t host, uint16_t port, sockaddr_in* sock );
        static std::string _str_sockaddr_in( const sockaddr_in& addr );

        static void bind( int fd, uint32_t host, uint16_t port );
        static int _bind( int fd, const sockaddr* addr, my_socklen_t len );
        static int _bind( int fd, const sockaddr_in& addr );

        static int _getsockname( int fd, sockaddr* addr, my_socklen_t *len );
        static int _getsockname( int fd, sockaddr_in* addr );
        static uint32_t _get_host( const sockaddr_in& sock );
        static uint16_t _get_port( const sockaddr_in& sock );
        static void get_bind_point( int fd, uint32_t* host, uint16_t* port );

        static bool listen( int fd, int queued_count );

        // 0 or errno
        static int _connect_or_err( int fd, const sockaddr *addr,
                                    Socket::my_socklen_t len );
        static void connect( int fd, uint32_t addr, uint16_t port );
        static int  connect_or_err( int fd, uint32_t addr, uint16_t port );

        static int _accept4( int fd, sockaddr* addr, my_socklen_t *addr_len, int flags );
        static int _accept4( int fd, sockaddr_in* addr, int flags );

        //  With NONBLOCK & CLOEXEC
        static int accept( int fd, uint32_t* host, uint16_t* port );

        // http://www.opennet.ru/man.shtml?topic=inet_ntoa&category=3&russian=0
        static uint32_t parse_ip( cstr addr );

        // Не реализована, там трэшшшшЪ.
        static ssize_t _sendmsg( int fd, const struct msghdr *message, int flags );

        static ssize_t _sendto( int fd, const void *buf, size_t n,
                                int flags, const sockaddr* addr, my_socklen_t addr_len );
        static ssize_t _sendto( int fd, const void *buf, size_t n,
                                int flags, const sockaddr_in* addr );

        // Добавляет флаг MSG_NOSIGNAL, см. интернет.
        static ssize_t sendto( int fd,
                               const void* buf, size_t n,
                               uint32_t addr, uint16_t port,
                               int flags = 0 );

        static void _getsockopt( int fd, int level, int optname,
                                 void *optval, my_socklen_t *optlen );
        static int32_t _getsockopt_int32( int fd, int level, int optname );
        static Type get_type( int fd );

        static ssize_t _recv_or_err( int fd, void *buf, size_t n, int flags );
        static ssize_t pending_datagram_size( int fd );

        static ssize_t _recvfrom( int fd, void *buf, size_t n,int flags,
                                  sockaddr* addr, my_socklen_t *addr_len );
        static ssize_t _recvfrom( int fd, void *buf, size_t n, int flags,
                                  sockaddr_in* addr );

        static ssize_t recvfrom( int fd, void *buf, size_t n, int flags,
                                 uint32_t* host, uint16_t* port );
    }; // Socket
    //===================================================================================

    //===================================================================================
} // namespace vposix
//=======================================================================================


////  Wrapper for SOCK_* defines.
//enum class Type
//{
//    STREAM = 1,         //  Sequenced, reliable, connection-based byte streams.
//    DGRAM = 2,          //  Connectionless, unreliable datagrams of fixed
//                        //  maximum length.
//    RAW = 3,			//  Raw protocol interface.
//    RDM = 4,			//  Reliably-delivered messages.
//    SEQPACKET = 5,		//  Sequenced, reliable, connection-based, datagrams of
//                        //  fixed maximum length.
//    DCCP = 6,           //  Datagram Congestion Control Protocol.
//    PACKET = 10,		//  Linux specific way of getting packets
//                        //  at the dev level.  For writing rarp and
//                        //  other similar things on the user level.

//    //  Flags to be ORed into the type parameter of socket and socketpair and
//    //  used for the flags parameter of paccept.
//};




#endif // VPOSIX_NETWORK_H
