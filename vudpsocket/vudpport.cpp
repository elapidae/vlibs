#include "vudpport.h"

#include <fcntl.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

//#include "vlogger.h"

static constexpr size_t Max_UDP_Datagram_Size = 65535; // Standart for localhost.





//=======================================================================================
VUdpPort::VUdpPort()
{}
//=======================================================================================
VUdpPort::~VUdpPort()
{}
//=======================================================================================
bool VUdpPort::bind( uint16_t port )
{
    if ( is_opened() ) return false;

    _handle = socket(AF_INET, SOCK_DGRAM, 0);

    if ( _handle <= 0 )
    {
        _last_errno = errno;
        //vwarning( vlog("Cannot open UDP socket, errno = ", _last_errno) );
        return false;
    }

    //| O_NONBLOCK
    fcntl( _handle, F_SETFL, O_ASYNC | O_RDWR | O_NOCTTY );


    const int32_t so_reuseaddr = 1;
    setsockopt( _handle, SOL_SOCKET, SO_REUSEADDR, &so_reuseaddr, sizeof(int32_t) );


    // TODO: перевести на использование через VHostAddress.
    sockaddr_in bind_addr;
    bzero( &bind_addr, sizeof bind_addr );

    bind_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind_addr.sin_port = ntohs( port );
    bind_addr.sin_family = AF_INET;

    int32_t r = -1;
    r = ::bind( _handle, (sockaddr *)&bind_addr, sizeof bind_addr );
    if ( r < 0 )
    {
        _last_errno = errno;
//        vwarning( vlog(varg::nospace, "Cannot bind to port ", port,
//                       ", errno = ", _last_errno) );

        return false;
    }

    _last_errno = 0;
    return true;
}
//=======================================================================================
void VUdpPort::close()
{
    if (_handle)
        ::close(_handle);

    _handle = 0;
}
//=======================================================================================
VByteArray VUdpPort::read_datagram( bool *ok )
{
    VHostAddress addr;
    return read_datagram_from( &addr, ok );
}
//=======================================================================================
VByteArray VUdpPort::read_datagram_from(VHostAddress *peer, bool *ok)
{
    VByteArray buf( Max_UDP_Datagram_Size );

    *ok = true;

    sockaddr_in raw_peer;
    socklen_t   raw_peer_len = sizeof raw_peer;


    auto has_read = ::recvfrom( _handle, buf.data(), buf.size(), 0,
                                (sockaddr*)&raw_peer, &raw_peer_len );
//    auto has_read = ::recvfrom( _handle, buf.data(), buf.size(), MSG_DONTWAIT,
//                                (sockaddr*)&raw_peer, &raw_peer_len );
    if (has_read < 0)
        *ok = false;

    peer->_addr = raw_peer;

    buf.resize( has_read < 0 ? 0 : has_read );
    buf.shrink_to_fit();
    return buf;
}
//=======================================================================================
bool VUdpPort::write_datagram( const VByteArray &datagram, const VHostAddress &addr )
{
    if (!is_opened()) return false;

    auto cnt = ::sendto( _handle, datagram.data(), datagram.size(), 0,
                         (const sockaddr*)&addr._addr, sizeof addr._addr );
    if (cnt < 0)
    {
        _last_errno = errno;
        //vwarning( vlog("Error write UDP datagram, errno =", _last_errno) );
    }
    return cnt == int(datagram.size());
}
//=======================================================================================

