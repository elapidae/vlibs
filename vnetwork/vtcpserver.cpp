#include "vtcpserver.h"

#include "vlog_pretty.h"

#include "verror.h"
#include "vposix_network.h"
#include "vposix_files.h"
#include "vposix_core.h"
#include "vpoll/vpoll.h"

#include <assert.h>

using namespace vposix;



//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
class VTcpServer::Pimpl final : public VPoll::EventReceiver
{
public:
    const int fd = -1;

    VIpAddress addr;
    uint16_t port = 0;

    Pimpl( int fd_, VTcpServer* owner_ );
    ~Pimpl() override;

    void event_received( VPoll::EventFlags flags ) override;

private:
    VTcpServer* owner;
};
#pragma GCC diagnostic pop
//=======================================================================================
VTcpServer::Pimpl::Pimpl( int fd_, VTcpServer *owner_ )
    : fd( fd_ )
    , owner( owner_ )
{
    VPoll::add_fd( fd, this );
}
//=======================================================================================
VTcpServer::Pimpl::~Pimpl()
{
    VPoll::del_fd( fd );
    Files::close( fd );
}
//=======================================================================================
void VTcpServer::Pimpl::event_received( VPoll::EventFlags flags )
{
    assert( flags.take_IN() );
    flags.throw_not_empty();

    uint32_t host;
    uint16_t port;
    auto peer_fd = Socket::accept( fd, &host, &port );

    owner->peer_connected( peer_fd );
}
//=======================================================================================


//=======================================================================================
VTcpServer::VTcpServer()
{}
//=======================================================================================
VTcpServer::~VTcpServer()
{
    close();
}
//=======================================================================================
bool VTcpServer::is_listening() const
{
    return p && p->port != 0;
}
//=======================================================================================
void VTcpServer::listen( VIpAddress addr, uint16_t port )
{
    p.reset();
    auto fd = Socket::socket( Socket::Domain::Inet4, Socket::Type::STREAM );
    p.reset( new Pimpl(fd, this) );

    Socket::set_out_of_band_data( fd );
    Socket::set_reuse_address( fd );

    Socket::bind( fd, addr._get_host(), port );

    Socket::listen( fd, _queued_connections_count );

    p->addr = addr;
    p->port = port;
}
//=======================================================================================
void VTcpServer::listen_any( uint16_t port )
{
    listen( VIpAddress::any(), port );
}
//=======================================================================================
void VTcpServer::close()
{
    p.reset();
}
//=======================================================================================
