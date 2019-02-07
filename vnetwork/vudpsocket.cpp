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


#include "vudpsocket.h"

#include <assert.h>

#include "verror.h"
#include "vlog.h"
#include "vposix_network.h"
#include "vposix_files.h"
#include "vposix_alloca.h"

// Strange path because dont want to include native path for vapplication.
#include "../vapplication/vpoll/vpoll.h"

using namespace vposix;

//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
class VUdpSocket::Pimpl : public VPoll::EventReceiver
{
public:
    virtual void event_received( VPoll::EventFlags flags ) override;

    Pimpl( int fd, VUdpSocket* owner );
    ~Pimpl() override;

    const int fd;
    VUdpSocket* owner;
};
#pragma GCC diagnostic pop
//=======================================================================================
void VUdpSocket::Pimpl::event_received( VPoll::EventFlags flags )
{
    assert( flags.take_IN()  );
    assert( flags.raw() == 0 );
    owner->ready_read();
}
//=======================================================================================
VUdpSocket::Pimpl::Pimpl( int fd, VUdpSocket* owner )
    : fd( fd )
    , owner( owner )
{
    VPoll::add_fd( fd, this );
}
//=======================================================================================
VUdpSocket::Pimpl::~Pimpl()
{
    VPoll::del_fd( fd );
    Files::close( fd );
}
//=======================================================================================

//=======================================================================================
VUdpSocket::VUdpSocket()
{}
//=======================================================================================
VUdpSocket::~VUdpSocket()
{}
//=======================================================================================
void VUdpSocket::bind( const VIpAddress& addr, uint16_t port )
{
    auto fd = Socket::udp_socket( addr._addr() );
    p.reset( new Pimpl(fd,this) );

    Socket::set_broadcast( fd );
    Socket::set_ip_receive_packet_information( fd );
    Socket::set_ip_receive_hop_limit( fd );

    Socket::bind( fd, addr._addr(), port );

    // Were checks, but, may be not need...
    //
    //assert( Socket::get_type(fd) == Socket::Type::DGRAM );
//    uint32_t local_host;
//    uint16_t local_port;
//    Socket::get_bind_point( fd, &local_host, &local_port );
}
//=======================================================================================
void VUdpSocket::bind_any( uint16_t port )
{
    bind( VIpAddress::any(), port );
}
//=======================================================================================
bool VUdpSocket::is_bound() const
{
    return bool(p);
}
//=======================================================================================
void VUdpSocket::send_to( const std::string& buf, const VIpAddress& addr, uint16_t port )
{
    if ( !is_bound() ) bind_any();

    auto sz = Socket::send_to( p->fd, buf, addr._addr(), port );
    if ( sz != ssize_t(buf.size()) )
        throw verror << "Cannot send UDP packet.";
}
//=======================================================================================
VString VUdpSocket::receive( VIpAddress* ip, uint16_t* port )
{
    assert( is_bound() );
    auto res_size = Socket::pending_datagram_size( p->fd );
    if ( res_size <= 0 ) return {};
    size_t ures_size = size_t( res_size );

    auto buf = Alloca::allocate<char>( ures_size );

    auto recv_sz = Socket::receive_from( p->fd, buf, ures_size, ip->_addr_ptr(), port );
    assert( recv_sz == res_size );

    return { buf, ures_size };
}
//=======================================================================================
VString VUdpSocket::receive()
{
    VIpAddress ip;
    uint16_t port;
    return receive( &ip, &port );
}
//=======================================================================================
