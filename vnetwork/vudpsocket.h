#ifndef VUDPSOCKET_H
#define VUDPSOCKET_H

#include <memory>
#include "vipaddress.h"
#include "vstring.h"
#include "vsignal.h"


//=======================================================================================
class VUdpSocket final
{
public:
    VUdpSocket();
    ~VUdpSocket();

    //  Прослушивать обязательно, иначе при наличии данных этот сигнал будет постоянно
    //  срабатывать.
    VSignal<> ready_read;

    void bind(const VIpAddress &addr, uint16_t port = 0 );
    void bind_any( uint16_t port = 0 );

    bool is_bound() const;

    void send_to(const std::string& buf, const VIpAddress &addr, uint16_t port );

    //  No more packets if result is empty.
    VString receive( VIpAddress *ip, uint16_t* port );
    VString receive();

private:
    class Pimpl; std::unique_ptr<Pimpl> p;
};
//=======================================================================================


#endif // VUDPSOCKET_H
