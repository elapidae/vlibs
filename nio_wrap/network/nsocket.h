#ifndef NSOCKET_H
#define NSOCKET_H

#include "nsocketaddress.h"
#include "nmainloop.h"
#include "nerror.h"
#include "ncancellable.h"

#include "vsignal.h"


class NSocket final : public NObject
{
public:
    //static NSocket udp4();
    //static NSocket udp6();
    //static NSocket tcp();
    //static NSocket sctp();
    enum ConnType
    {
        AsUdp4, AsUdp6,
        AsTcp4, AsTcp6,
        AsUnix
    };

    NSocket( GSocketFamily family,
             GSocketType type,
             GSocketProtocol protocol = G_SOCKET_PROTOCOL_DEFAULT,
             NError *err = nullptr );

    NSocket( ConnType ctype, NError *err = nullptr );

    ~NSocket();

    bool bind( const NSocketAddress &addr,
               bool allow_reuse = false, NError *err = nullptr );
    bool bind( const std::string &addr, uint16_t port,
               bool allow_reuse = false, NError *err = nullptr );

    bool listen( NError * err = nullptr );

    //NSocket accept( NCancellable *cancel = nullptr, NError *err = nullptr );

    bool connect( const NSocketAddress &addr,
                  NCancellable *cancel = nullptr, NError *err = nullptr );

    ssize_t receive( char *buf, size_t size,
                     NCancellable *cancel = nullptr, NError *err = nullptr );

    ssize_t receive_from( char *buf, size_t size, NSocketAddress *addr,
                          NCancellable *cancel = nullptr, NError *err = nullptr );

    std::string receive( NCancellable *cancel = nullptr, NError *err = nullptr );

    std::string receive_from( NSocketAddress *addr,
                              NCancellable *cancel = nullptr, NError *err = nullptr );

    ssize_t send( const std::string &buffer,
                  NCancellable *cancel = nullptr, NError *err = nullptr );

    ssize_t send_to(const NSocketAddress &addr, const char *msg, size_t size,
                     NCancellable *cancel = nullptr, NError *err = nullptr );

    ssize_t send_to( const NSocketAddress &addr, const std::string &msg,
                     NCancellable *cancel = nullptr, NError *err = nullptr );

    bool join_multicast_group( const NInetAddress &group, bool source_specific,
                               const char *iface, NError *err = nullptr );

    VSignal<> ready_read;
    void poll_in_context( NMainContext *ctx = nullptr,
                          NCancellable *cancel = nullptr );

    ssize_t available_bytes() const;

    // don't use it ...
    NSource create_source( GIOCondition cond, NCancellable *cancel = nullptr );
    int get_fd() const;

    NSocketAddress local_address( NError *err = nullptr ) const;

private:
    NSocket( GSocket *s );

    GSocket *_g_socket = nullptr;

    static int _on_ready_read( void *vself );
};



class NUdpSocket
{

};

#endif // NSOCKET_H
