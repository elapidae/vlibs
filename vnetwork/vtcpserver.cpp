#include "vtcpserver.h"

//#include <sys/socket.h>

#include "verror.h"
#include "vposix_network.h"
#include "vposix_files.h"

using namespace vposix;



//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
class VTcpServer::Pimpl
{
public:
    int fd = -1;

    VIpAddress addr;
    uint16_t port = 0;

    bool listening = false;
};
#pragma GCC diagnostic pop
//=======================================================================================
VTcpServer::VTcpServer()
    : p( new Pimpl )
{}
//=======================================================================================
VTcpServer::~VTcpServer()
{
    close();
}
//=======================================================================================
bool VTcpServer::is_listening() const
{
    return p->listening;
}
//=======================================================================================
void VTcpServer::listen( VIpAddress addr, uint16_t port )
{
    if ( p->listening ) verror << "Listening";

    p->fd = Socket::socket( Socket::Domain::Inet4, Socket::Type::STREAM );
    Socket::set_out_of_band_data( p->fd );
    Socket::set_reuse_address( p->fd );

    Socket::bind( p->fd, addr._get_host(), port );

    Socket::listen( p->fd, _queued_connections_count );

    p->addr = addr;
    p->port = port;
    p->listening = true;
}
//=======================================================================================
void VTcpServer::close()
{
    if ( !is_listening() ) return;

    Files::close( p->fd );
    p->fd = -1;
    p->listening = false;
}
//=======================================================================================
