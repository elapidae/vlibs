#ifndef VLOGGER_TO_UDP_H
#define VLOGGER_TO_UDP_H

#include <stdint.h>

#include "vhostaddress.h"
#include "vsignal.h"
#include "vbytearray.h"
#include "vlogger.h"


class VLogger_To_UDP final
{
public:

    VSignal<VLog> received;

    VLogger_To_UDP( uint16_t bind_port );
    ~VLogger_To_UDP();

    void set_target_address( const VHostAddress &addr );

    void register_self_in_log();

private:
    class Pimpl;
    std::unique_ptr<Pimpl> p;
    //Pimpl *p;
};

#endif // VLOGGER_TO_UDP_H
