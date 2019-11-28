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


#include "vtcpsocket.h"

#include "vposix_network.h"
#include "vposix_network_ip.h"

#include "vposix_core.h"
#include "vposix_files.h"

#include "vlog.h"
#include "verror.h"

#include "vpoll/vpoll.h"

#include <assert.h>

using namespace vposix;

//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
class VTcpSocket::Pimpl : public VPoll::EventReceiver
{
public:
    Pimpl( int fd_, VTcpSocket *owner_ );
    ~Pimpl() override;
    void close();

    void event_received( VPoll::EventFlags flags ) override;

    void connection_ok();

    bool is_connected = false;
    int fd = -1;

private:
    VTcpSocket *owner;
};
#pragma GCC diagnostic pop
//=======================================================================================
VTcpSocket::Pimpl::Pimpl( int fd_, VTcpSocket *owner_ )
    : fd( fd_ )
    , owner( owner_ )
{
    if ( fd < 0 )
        throw verror( "VTcpSocket fd < 0" );

    VPoll::add_fd( fd, this, VPoll::Direction::InOut );
}
//=======================================================================================
VTcpSocket::Pimpl::~Pimpl()
{
    close();
}
//=======================================================================================
//#include <sys/ioctl.h>
//#include <linux/sockios.h>
void VTcpSocket::Pimpl::close()
{
    //  Размер буффера.
    //    vdeb << Socket::_getsockopt_int32( fd, SOL_SOCKET, SO_SNDBUF );
    //  Получить сколько байт не отправлено.
    //    vdeb << vposix::Files::_ioctl_ret_int( fd, SIOCOUTQ );

    is_connected = false;
    if ( fd < 0 ) return;

    VPoll::del_fd( fd );

    vposix::Socket::shutdown_rw( fd );
    vposix::Files::close( fd );
    fd = -1;

    owner->socket_disconnected();
}
//=======================================================================================
void VTcpSocket::Pimpl::event_received( VPoll::EventFlags flags )
{
    //vdeb << "err" << (flags.take_ERR() ? "Need to see in Qt" : "");
    //vdeb << "hup" << flags.take_HangUp();

    if ( flags.take_OUT() )
        connection_ok();

    if ( flags.take_IN() )
        owner->ready_read();

    if ( flags.take_RD_HangUp() )
    {
        close();
        return;
    }

    flags.throw_not_empty();
    //vdeb.hex() << flags.raw();
}
//=======================================================================================
void VTcpSocket::Pimpl::connection_ok()
{
    VPoll::mod_fd( fd, this, VPoll::Direction::In );
    is_connected = true;
    owner->socket_connected();
}
//=======================================================================================


//=======================================================================================
VTcpSocket::VTcpSocket()
{}
//=======================================================================================
VTcpSocket::VTcpSocket( VTcpSocket::Peer* peer )
    : p( new Pimpl(peer->take_fd(),this) )
{
    std::function<int()> ff;
    //vdeb << "Connected as server socket..." << p->fd;
    p->is_connected = true;
}
//=======================================================================================
VTcpSocket::~VTcpSocket()
{}
//=======================================================================================
bool VTcpSocket::is_connected() const
{
    return p && p->is_connected;
}
//=======================================================================================
void VTcpSocket::connect_to_host( const VIpAddress& addr, uint16_t port )
{
    p.reset();
    auto fd = Socket::tcp_socket( addr._addr() );
    Socket::set_out_of_band_data( fd );
    Socket::set_linger( fd, 1, 1 ); // перед закрытием отправлять данные.
    p.reset( new Pimpl(fd, this) );

    auto res = Socket::connect_or_err( fd, addr._addr(), port );
    if ( res == -1 )
    {
        Errno e ;
        if ( e.operation_in_progress() || e.connection_already_in_progress() )
        {
            return;
            //vtrace << "Need to set in write polling." << e.str();
        }
        else
            e.throw_verror( "VTcpSocket::connect_to_host" );
    }
}
//=======================================================================================
void VTcpSocket::set_keep_alive( int idle, int intvl, int cnt )
{
    if ( !p ) throw verror << "set keep alive on empty socket.";
    Socket::set_keep_alive( p->fd, idle, intvl, cnt );
}
//=======================================================================================
//  UPD 2019-06-14 -- https://www.rsdn.org/article/unix/sockets.xml
//  Функция send может вернуть меньшее количество байт, тогда надо посылать до победного.
void VTcpSocket::send( const std::string& data )
{
    if ( !is_connected() )
        throw verror << "Socket has not connected.";

    auto ptr  = data.c_str();
    auto size = data.size();
    while (size)
    {
        auto received = Socket::send( p->fd, ptr, size );

        if (size_t(received) == size) return;

        assert( size_t(received) < size && received >= 0 );
        ptr  += received;
        size -= size_t(received);
    }
}
//=======================================================================================
VString VTcpSocket::receive_all()
{
    char buf[ Buffer_Size ];
    VString res;

    while(1)
    {
        auto has_read = Socket::_recv_or_err( p->fd, buf, Buffer_Size, 0 );

        if ( has_read == -1 )
        {
            Errno e;
            if ( e.resource_unavailable_try_again() )
                return res;
            e.throw_verror("VTcpSocket::receive_all");
        }

        res.append( buf, buf + has_read );

        if ( has_read < Buffer_Size )
            return res;
    }
}
//=======================================================================================
void VTcpSocket::disconnect_from_host()
{
    if ( !p ) return;
    p->close();
}
//=======================================================================================

//=======================================================================================
static void del_and_close_tcp( void* atom_int )
{
    auto ai_ptr = static_cast<std::atomic_int*>(atom_int);
    auto fd = ai_ptr->fetch_or( -1 );
    delete ai_ptr;

    if ( fd < 0 ) return;
    vwarning << "Server side VTcpSocket has not attached (and will close)";
    Files::close( fd );
}
//=======================================================================================
VTcpSocket::Peer::Peer( int fd )
    : _ptr( new std::atomic<int>(fd), del_and_close_tcp )
{}
//=======================================================================================
int VTcpSocket::Peer::take_fd()
{
    assert( _ptr );
    auto res = _ptr->fetch_or( -1 );
    _ptr.reset();
    return res;
}
//=======================================================================================
