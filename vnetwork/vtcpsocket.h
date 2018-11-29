#ifndef VTCPSOCKET_H
#define VTCPSOCKET_H

#include "vipaddress.h"
#include <memory>
#include <atomic>
#include "vsignal.h"
#include "vstring.h"

//=======================================================================================
class VTcpSocket final
{
    static auto constexpr Buffer_Size = 4096;
public:
    //  Когда сервер принимает соединение, он генерирует сигнал peer_connected<Peer>.
    //  Этот класс можно передавать, например, между потоками, копировать, и пр.
    //  Но как только он передается в конструктор VTcpSocket, все его копии
    //  превращаются в тыквы.
    class Peer;

    VSignal<> ready_read;
    VSignal<> socket_connected;
    VSignal<> socket_disconnected;

    VTcpSocket();
    VTcpSocket( Peer* peer );
    ~VTcpSocket();

    bool is_connected() const;

    void connect_to_host( VIpAddress addr, uint16_t port );

    bool send( const std::string& data );

    VString receive_all();

private:
    class Pimpl; std::unique_ptr<Pimpl> p;
};
//=======================================================================================

//=======================================================================================
class VTcpSocket::Peer final
{
public:
    Peer( const Peer& ) = default;
    Peer& operator = ( const Peer& ) = default;

private:
    friend class VTcpServer; Peer( int fd );    //  Сервер создает.
    friend class VTcpSocket; int take_fd();        //  Сокет забирает.

    std::shared_ptr< std::atomic<int> > _ptr;
};
//=======================================================================================


#endif // VTCPSOCKET_H
