#include "vudpsocket.h"

#include <assert.h>

#include "verror.h"
#include "vlog_pretty.h"
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

    VIpAddress local_host;
    uint16_t local_port;
};
#pragma GCC diagnostic pop
//=======================================================================================
void VUdpSocket::Pimpl::event_received( VPoll::EventFlags flags )
{
    assert( flags.IN() );
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
void VUdpSocket::bind( VIpAddress host, uint16_t port )
{
    auto fd = Socket::socket( Socket::Domain::Inet4, Socket::Type::DGRAM );

    Socket::set_broadcast( fd );
    Socket::set_ip_receive_packet_information( fd );
    Socket::set_ip_receive_hop_limit( fd );

    Socket::bind( fd, host._get_host(), port );

    auto type = Socket::get_type( fd );
    assert( type == Socket::Type::DGRAM );

    uint32_t local_host;
    uint16_t local_port;
    Socket::get_bind_point( fd, &local_host, &local_port );

    p.reset( new Pimpl(fd,this) );
    p->local_host._set_host( local_host );
    p->local_port = local_port;
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
void VUdpSocket::send_to( const std::string &buf, VIpAddress host, uint16_t port )
{
    if ( !is_bound() ) bind_any();

    auto sz = Socket::sendto( p->fd, buf.c_str(), buf.size(), host._get_host(), port );
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

    // std::vector<char> buf( ures_size );
    auto buf = Alloca::allocate<char>( ures_size );

    uint32_t host;
    auto recv_sz = Socket::recvfrom( p->fd, buf, ures_size, 0, &host, port );
    assert( recv_sz == res_size );
    ip->_set_host( host );
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
