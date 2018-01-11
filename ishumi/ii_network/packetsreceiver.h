#ifndef PACKETSRECEIVER_H
#define PACKETSRECEIVER_H

#include "vsignal.h"
#include "vbytearray.h"
#include "json11.h"

// Alpha ver. Подразумевается, что объект будет проводить первичный анализ входного
// пакетного трафика.
// Если трафик на новое соединение, то в начале идет json-объект.
// Если соединение признанное -- передается сначала uuid, только потом json-объект.


class PacketsReceiver
{
public:

    VSignal<json11::Json::object, VByteArray> received;

    void parse( const VByteArray &packet );
};



#endif // PACKETSRECEIVER_H
