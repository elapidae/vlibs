#include "vudpsocket.h"

#include "vslot.h"
#include "vudpport.h"
#include "vthread.h"
#include <atomic>

//#include "vlogger.h"

using namespace std;


//=======================================================================================
class VUdpSocket::Pimpl
{
    VUdpSocket *owner;
public:

    VThread thread;
    VUdpPort port;

    atomic_bool let_stop_listen;

    Pimpl( VUdpSocket *owner_ )
        : owner( owner_ )
        , thread("udp socket")
        , let_stop_listen( false )
        , slot_received( &owner_->received )
    {}
    ~Pimpl()
    {
        owner->close();
        thread.detach(); // very bad, need to do
    }

    VSlot<VByteArray, VHostAddress> slot_received;
    void on_received( const VByteArray &datagram, const VHostAddress &addr );

    void listen();
};
//=======================================================================================



//=======================================================================================
VUdpSocket::VUdpSocket()
    : p( new Pimpl(this) )
{}
//=======================================================================================
VUdpSocket::~VUdpSocket()
{}
//=======================================================================================
bool VUdpSocket::bind( uint16_t port )
{
    p->let_stop_listen = false;
    auto ok = p->port.bind( port );

    if (!ok)
        return false;

    p->thread.cinvoke( p.get(), &Pimpl::listen );

    return true;
}
//=======================================================================================
void VUdpSocket::close()
{
    p->let_stop_listen = true;
    p->port.close();
}
//=======================================================================================
bool VUdpSocket::write_datagram( const VByteArray &datagram, const VHostAddress &addr )
{
    return p->port.write_datagram( datagram, addr );
}
//=======================================================================================
void VUdpSocket::Pimpl::on_received( const VByteArray &datagram,
                                     const VHostAddress &addr )
{
    owner->received( datagram, addr );
}
//=======================================================================================
void VUdpSocket::Pimpl::listen()
{
    while(1)
    {
        bool ok;
        VHostAddress addr;
        auto datagram = port.read_datagram_from( &addr, &ok );

        if ( !ok )
        {
            if (let_stop_listen) return;
            throw std::runtime_error("Error during listen UDP port");
        }
        slot_received( datagram, addr );
    }
}
//=======================================================================================
