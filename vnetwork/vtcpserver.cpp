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


#include "vtcpserver.h"

#include "vlog.h"

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
void VTcpServer::listen( const VIpAddress& addr, uint16_t port )
{
    p.reset();
    auto fd = Socket::tcp_socket( addr._addr() );
    p.reset( new Pimpl(fd, this) );

    Socket::set_out_of_band_data( fd );
    Socket::set_reuse_address( fd );

    Socket::bind( fd, addr._addr(), port );

    Socket::listen( fd, _queued_connections_count );

    Socket::get_sock_addr( fd, p->addr._addr_ptr(), &p->port );
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
const VIpAddress & VTcpServer::address() const
{
    assert( is_listening() );
    return p->addr;
}
//=======================================================================================
uint16_t VTcpServer::port() const
{
    assert( is_listening() );
    return p->port;
}
//=======================================================================================
