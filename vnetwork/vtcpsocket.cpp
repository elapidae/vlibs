#include "vtcpsocket.h"

#include "vposix_network.h"
#include "vposix_core.h"
#include "vlog_pretty.h"
#include "verror.h"

using namespace vposix;

class VTcpSocket::Pimpl
{
public:
    int fd = -1;
};

VTcpSocket::VTcpSocket()
    : p( new Pimpl )
{}

void VTcpSocket::connect_to_host( VIpAddress addr, uint16_t port )
{
    p->fd = Socket::socket( Socket::Domain::Inet4, Socket::Type::STREAM );
    Socket::set_out_of_band_data( p->fd );
    auto res = Socket::connect_or_err( p->fd, addr._get_host(), port );
    if ( res == -1 )
    {
        Errno e ;
        if ( e.operation_in_progress() || e.connection_already_in_progress() )
            vtrace << "Need to set in write polling." << e.str();
        else
            e.throw_verror( "VTcpSocket::connect_to_host" );
    }
}

void VTcpSocket::close()
{

}
