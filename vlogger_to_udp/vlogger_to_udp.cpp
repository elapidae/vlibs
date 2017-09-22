#include "vlogger_to_udp.h"

#include "vudpsocket.h"



//=======================================================================================
class VLogger_To_UDP::Pimpl
{
public:
    VUdpSocket udp;
    VHostAddress target_addr;
    VLog::OutControl::Deleter my_deleter;

    void send(const VLog &log)
    {
        udp.write_datagram( log.to_json(), target_addr );
    }

};
//=======================================================================================
VLogger_To_UDP::VLogger_To_UDP( uint16_t bind_port )
    : p( new Pimpl )
{
    if ( !p->udp.bind(bind_port) )
        throw VLogException( vlog("Cannot bind UDP logger to port", bind_port) );

    p->udp.received.connect( [this](const VByteArray &data, const VHostAddress &addr)
    {
        bool ok;
        auto log = VLog::from_json(data.str(), &ok);

        if (ok)
            received(log);
        else
        {
            vwarning( vlog("Cannot convert datagram to log, addr =", addr.str()) );
        }
    });
}
//=======================================================================================
VLogger_To_UDP::~VLogger_To_UDP()
{}
//=======================================================================================
void VLogger_To_UDP::set_target_address( const VHostAddress &addr )
{
    p->target_addr = addr;
}
//=======================================================================================
void VLogger_To_UDP::register_self_in_log()
{
    p->my_deleter = VLog::OutControl::add_logger
                                        ( [this](const VLog &log){ p->send(log); } );
}
//=======================================================================================
