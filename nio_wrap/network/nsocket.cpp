#include "nsocket.h"

#include "impl/ncastinghelper.h"

#include <assert.h>

#include "threadsafe_unordered_map.h"

using namespace std;


static ThreadSafe_Unordered_Map<GSocket*, NSocket*> all_sockets;



//=======================================================================================
//NSocket NSocket::udp4()
//{
//    _n_error_proxy err_proxy(nullptr);
//    return g_socket_new( G_SOCKET_FAMILY_IPV4,
//                         G_SOCKET_TYPE_DATAGRAM,
//                         G_SOCKET_PROTOCOL_UDP,
//                         err_proxy );
//}
//=======================================================================================
//NSocket NSocket::udp6()
//{
//    _NErrorProxy err_proxy(nullptr);
//    return g_socket_new( G_SOCKET_FAMILY_IPV6,
//                         G_SOCKET_TYPE_DATAGRAM,
//                         G_SOCKET_PROTOCOL_UDP,
//                         err_proxy );
//}
//=======================================================================================
static GSocketFamily as_gfamily( NSocket::ConnType ctype )
{
    if ( ctype == NSocket::AsUdp4 || ctype == NSocket::AsTcp4 )
        return G_SOCKET_FAMILY_IPV4;

    if ( ctype == NSocket::AsUdp6 || ctype == NSocket::AsTcp6 )
        return G_SOCKET_FAMILY_IPV6;

    if ( ctype == NSocket::AsUnix )
        return G_SOCKET_FAMILY_UNIX;

    throw logic_error("Unknown socket family type.");
    //G_SOCKET_FAMILY_INVALID,
    //G_SOCKET_FAMILY_UNIX
}
//=======================================================================================
static GSocketType as_gtype( NSocket::ConnType ctype )
{
    if ( ctype == NSocket::AsUdp4 || ctype == NSocket::AsUdp6 )
        return G_SOCKET_TYPE_DATAGRAM;

    if ( ctype == NSocket::AsTcp4 || ctype == NSocket::AsTcp6 )
        return G_SOCKET_TYPE_STREAM;

    throw logic_error("Unknown socket type.");
    //G_SOCKET_TYPE_INVALID,
    //G_SOCKET_TYPE_SEQPACKET
}
//=======================================================================================
static GSocketProtocol as_gprotocol( NSocket::ConnType ctype )
{
    if ( ctype == NSocket::AsUdp4 || ctype == NSocket::AsUdp6 )
        return G_SOCKET_PROTOCOL_UDP;

    if ( ctype == NSocket::AsTcp4 || ctype == NSocket::AsTcp6 )
        return G_SOCKET_PROTOCOL_TCP;

    throw logic_error("Unknown socket protocol.");
    //G_SOCKET_PROTOCOL_UNKNOWN = -1,
    //G_SOCKET_PROTOCOL_DEFAULT = 0,
    //G_SOCKET_PROTOCOL_SCTP    = 132
}
//=======================================================================================

//=======================================================================================
int NSocket::_on_ready_read( void *vself )
{
    auto *gsocket = static_cast<GSocket*>( vself );
    auto *nsocket = all_sockets.at( gsocket );

    //nsocket->ready_read();

    return G_SOURCE_CONTINUE;
}
//=======================================================================================

//=======================================================================================
NSocket::NSocket( GSocket *s )
    : NObject( gcast_to_gobject(s) )
    , _g_socket( s )
{
    all_sockets.emplace( _g_socket, this );
}
//=======================================================================================
//NSocket NSocket::udp4()
//{
//    return std::move( NSocket(AsUdp4) );
//}
//=======================================================================================
NSocket::NSocket( GSocketFamily family,
                  GSocketType type,
                  GSocketProtocol protocol,
                  NError *err )
    : NSocket( g_socket_new(family, type, protocol, _n_error_proxy(err)) )
{}
//=======================================================================================
NSocket::NSocket( NSocket::ConnType ctype, NError *err )
    : NSocket( as_gfamily(ctype), as_gtype(ctype), as_gprotocol(ctype), err )
{}
//=======================================================================================
NSocket::~NSocket()
{
    all_sockets.erase( _g_socket );
}
//=======================================================================================

//=======================================================================================
bool NSocket::bind( const NSocketAddress &addr, bool allow_reuse, NError *err )
{
    gboolean areuse = allow_reuse ? TRUE : FALSE;
    _n_error_proxy err_proxy( err );
    return g_socket_bind ( _g_socket, addr._g_socket_address, areuse, err_proxy );
}
//=======================================================================================
bool NSocket::bind(const string &addr, uint16_t port, bool allow_reuse, NError *err)
{
    return bind( NInetSocketAddress(addr, port), allow_reuse, err );
}
//=======================================================================================
bool NSocket::listen( NError *err )
{
    _n_error_proxy err_proxy( err );
    return g_socket_listen ( _g_socket, err_proxy );
}
//=======================================================================================
//NSocket NSocket::accept(NCancellable *cancel, NError *err)
//{
//    GCancellable *gcancel = cancel ? cancel->_g_cancellable() : nullptr;
//    _NErrorProxy err_proxy( err );
//    return g_socket_accept( _g_socket, gcancel, err_proxy );
//}
//=======================================================================================
bool NSocket::connect(const NSocketAddress &addr, NCancellable *cancel, NError *err)
{
    GCancellable *gcancel = cancel ? cancel->_g_cancellable : nullptr;
    _n_error_proxy err_proxy( err );
    return g_socket_connect( _g_socket, addr._g_socket_address, gcancel, err_proxy );
}
//=======================================================================================
ssize_t NSocket::receive( char *buf, size_t size, NCancellable *cancel, NError *err )
{
    GCancellable *gcancel = cancel ? cancel->_g_cancellable : nullptr;
    _n_error_proxy err_proxy( err );
    return g_socket_receive( _g_socket, buf, size, gcancel, err_proxy );
}
//=======================================================================================
string NSocket::receive( NCancellable *cancel, NError *err )
{
    auto bytes = available_bytes();
    if (bytes <= 0) return string();
    std::string res( bytes, '\0' );
    auto size = receive( const_cast<char*>(res.c_str()), bytes, cancel, err );
    assert( size == bytes );
    return res;
}
//=======================================================================================
string NSocket::receive_from( NSocketAddress *addr, NCancellable *cancel, NError *err )
{
    char buf[ 65536 ];
    auto size = receive_from( buf, 65536, addr, cancel, err );

    return size <= 0 ? "" : string( buf, buf + size );
}
//=======================================================================================
ssize_t NSocket::receive_from( char *buf, size_t size, NSocketAddress *addr,
                               NCancellable *cancel, NError *err )
{
    GCancellable *gcancel = cancel ? cancel->_g_cancellable : nullptr;
    _n_error_proxy err_proxy( err );
    GSocketAddress *gaddr = nullptr;
    auto res = g_socket_receive_from( _g_socket, &gaddr, buf, size, gcancel, err_proxy );
    *addr = gaddr;
    return res;
}
//=======================================================================================
ssize_t NSocket::send(const std::string &buffer, NCancellable *cancel, NError *err)
{
    GCancellable *gcancel = cancel ? cancel->_g_cancellable : nullptr;
    _n_error_proxy err_proxy( err );
    return g_socket_send( _g_socket, buffer.c_str(), buffer.size(), gcancel, err_proxy );
}
//=======================================================================================
ssize_t NSocket::send_to( const NSocketAddress &addr,
                          const char *msg, size_t size,
                          NCancellable *cancel, NError *err )
{
    GCancellable *gcancel = cancel ? cancel->_g_cancellable : nullptr;
    _n_error_proxy err_proxy( err );

    return g_socket_send_to( _g_socket, addr._g_socket_address,
                             msg, size,
                             gcancel, err_proxy );
}
//=======================================================================================
ssize_t NSocket::send_to( const NSocketAddress &addr, const string &msg,
                          NCancellable *cancel, NError *err )
{
    return send_to( addr, msg.c_str(), msg.size(), cancel, err );
}
//=======================================================================================
NSource NSocket::create_source( GIOCondition cond, NCancellable *cancel )
{
    GCancellable *gcancel = cancel ? cancel->_g_cancellable : nullptr;
    return g_socket_create_source( _g_socket, cond, gcancel );
}
//=======================================================================================
bool NSocket::join_multicast_group( const NInetAddress &group, bool source_specific,
                                    const char *iface, NError *err )
{
    _n_error_proxy err_proxy( err );
    return g_socket_join_multicast_group( _g_socket, group._g_inet_address,
                                          source_specific, iface, err_proxy );
}
//=======================================================================================
void NSocket::poll_in_context( NMainContext *ctx, NCancellable *cancel )
{
    auto source = create_source( G_IO_IN, cancel );
    source.set_callback( _on_ready_read, nullptr );

    if (ctx) ctx->attach( source );
    else     NMainContext::default_ctx().attach( source );
}
//=======================================================================================
ssize_t NSocket::available_bytes() const
{
    return g_socket_get_available_bytes( _g_socket );
}
//=======================================================================================
int NSocket::get_fd() const
{
    return g_socket_get_fd( _g_socket );
}
//=======================================================================================
NSocketAddress NSocket::local_address( NError *err ) const
{
    _n_error_proxy err_proxy( err );
    return g_socket_get_local_address( _g_socket, err_proxy );
}
//=======================================================================================








//https://eax.me/network-application-mistakes/
//Типичные ошибки в сетевых приложениях на C/C++

//11 октября 2017

//Очень многие программисты при написании сетевых приложений на C/C++ по неопытности допускают одни и те же ошибки. Даже несмотря на то, что эти ошибки, казалось бы, довольно известны. Поэтому сегодня мне хотелось бы в очередной раз поднять этот несколько баянистый топик, в надежде, что заметка поможет уменьшить hit ratio соответствующих граблей.

//Итак, первая проблема заключается в обработке сигнала SIGPIPE. Этот сигнал приходит приложению, например, в случае, когда оно пытается сделать send в сокет, уже закрытый на стороне клиента. По умолчанию этот сигнал убивает приложение, что часто не является тем, чего хочет программист (если он пишет свое приложение на трэдах, а не процессах). Решить проблему можно так:
///*
// * If client will close a connection send() will just return -1
// * instead of killing a process with SIGPIPE.
// */
//void HttpServer::_ignoreSigpipe() {
//    sigset_t msk;
//    sigemptyset(&msk);
//    sigaddset(&msk, SIGPIPE);
//    if(pthread_sigmask(SIG_BLOCK, &msk, nullptr) != 0)
//        throw std::runtime_error("pthread_sigmask() call failed");
//}

//Две другие проблемы связаны с обработкой возвращаемых значений от recv и send (или read и write, смотря что вы используете).

//Во-первых, эти вызовы могут возвращать ошибку и устанавливать errno в значение EINTR в случае, если вызов был прерван пришедшим программе сигналом до того, как были посланы или приняты какие-либо данные. Это совершенно штатная ситуация, и в этом случае обычно нужно просто повторить вызов.

//Во-вторых, ни один из вызовов не гарантирует, что пошлет или примет ровно столько байт, сколько вы указали третьим аргументом. То есть, за один вызов может быть принято или послано как ровно столько байт, сколько вы хотели, так и меньше. Часто эта особенность приводит к неприятной ситуации, когда код отлично работает у программиста на ноутбуке, но неожиданно ломается на сервере.

//Правильный код будет выглядеть как-то так:
//void Socket::read(char* buff, size_t buffsize) {
//    while(buffsize > 0) {
//        ssize_t res = ::read(_fd, buff, buffsize);
//        if(res == 0) {
//            throw std::runtime_error("client closed connection");
//        } else if(res < 0) {
//            if(errno == EINTR)
//                continue;
//            throw std::runtime_error("read() failed");
//        }
//        buff += res;
//        buffsize -= res;
//    }
//}

//void Socket::write(const char* buff, size_t buffsize) {
//    while(buffsize > 0) {
//        ssize_t res = ::write(_fd, buff, buffsize);
//        if(res <= 0) {
//            if(errno == EINTR)
//                continue;
//            throw std::runtime_error("write() failed");
//        }

//        buff += res;
//        buffsize -= res;
//    }
//}

//Это, собственно, и есть те ошибки, о которых я хотел рассказать. Само собой разумеется, существуют и куда более глубоководные грабли. Например, при реализации собственных протоколов обычно не лишено смысла предусмотреть посылку пингов клиенту. Нужно это для своевременного закрытия повисших соединений, которые образуются как из-за «умного» прокси между клиентом и сервером, кэширующего соединения (часто встречается в случае HTTP), так и тупо из-за бага в клиентском коде. Еще неплохой идеей будет предусмотреть собственные контрольные суммы. Было больше одной истории с багами в маршрутизаторах — например, в редких случаях они портили принятые данные, а затем вычисляли контрольные суммы в IP-пакетах от испорченных данных (см также тынц и тынц). Однако это все уже темы для других постов.

//А какие типичные ошибки вы бы добавили к приведенному списку?
