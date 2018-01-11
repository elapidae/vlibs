#ifndef NET_CORE_H
#define NET_CORE_H

#include "stdint.h"
#include "vbytearray.h"
#include <chrono>

namespace ii
{

    using dgram_id_t = uint16_t;

    using netfragment_num_t = int32_t;

    using steady_clock_t = std::chrono::steady_clock::time_point;

    class SessionId
    {
    public:
        VByteArray save() const;
        static SessionId load( const VByteArray &sid );

        // Двигает итератор на позицию, следующую за uuid.
        static SessionId load( const VByteArray::const_iterator *begin,
                               const VByteArray::const_iterator end );

        bool operator == ( const SessionId &rhs ) const;
        bool operator != ( const SessionId &rhs ) const;

        int64_t f, s;
    };

} // ii namespace


#endif // NET_CORE_H
