#ifndef VTCPSERVER_H
#define VTCPSERVER_H

#include <stdint.h>
#include "vipaddress.h"
#include "vsignal.h"
#include <memory>


class VTcpServer final
{
    static constexpr int _queued_connections_count = 30;

public:

    VSignal<int> peer_connected;

    VTcpServer();
    ~VTcpServer();

    bool is_listening() const;
    void listen( VIpAddress addr, uint16_t port );
    void close();

    VIpAddress address()  const;
    uint16_t     port()     const;

private:
    //class Pimpl; std::unique_ptr<Pimpl> p;
    class Pimpl; Pimpl* p;
};



#endif // VTCPSERVER_H
