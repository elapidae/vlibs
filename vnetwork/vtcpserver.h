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


#ifndef VTCPSERVER_H
#define VTCPSERVER_H

#include <stdint.h>
#include "vipaddress.h"
#include "vtcpsocket.h"
#include "vsignal.h"
#include <memory>


//=======================================================================================
class VTcpServer final
{
    static constexpr int _queued_connections_count = 30;

public:
    VSignal<VTcpSocket::Peer> peer_connected;

    VTcpServer();
    ~VTcpServer();

    bool is_listening() const;
    void listen( const VIpAddress& addr, uint16_t port );
    void listen_any( uint16_t port );
    void close();

    const VIpAddress &address()  const;
    uint16_t   port()     const;

private:
    class Pimpl; std::unique_ptr<Pimpl> p;
};
//=======================================================================================


#endif // VTCPSERVER_H
