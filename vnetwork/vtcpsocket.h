#ifndef VTCPSOCKET_H
#define VTCPSOCKET_H

#include "vipaddress.h"
#include <memory>
#include "vsignal.h"
#include "vstring.h"

class VTcpSocket final
{
    static auto constexpr Buffer_Size = 4096;

public:

    VSignal<> ready_read;
    VSignal<> socket_connected;
    VSignal<> socket_disconnected;

    VTcpSocket();
    ~VTcpSocket();

    bool is_connected() const;

    void connect_to_host( VIpAddress addr, uint16_t port );

    bool send( const std::string& data );

    VString receive_all();

private:
    class Pimpl; std::unique_ptr<Pimpl> p;
};


#endif // VTCPSOCKET_H
