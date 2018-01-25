#ifndef OUTCOMINGMESSAGE_H
#define OUTCOMINGMESSAGE_H

#include <vector>
#include "vbytearray.h"
#include "json11.h"
#include "message.h"

//=======================================================================================
namespace ii
{
    //===================================================================================
    class OutcomingMessage : Message
    {
    public:
        static uint default_max_bin_size;    // = 1000.

        using Dump = std::vector<VByteArray>;

        OutcomingMessage( const std::string &target,
                          const VByteArray &data = VByteArray() );

        void insert( const std::string &label, const json11::Json &val );

        Dump dump(uint max_bin_size);    // Can be call one time.
        Dump dump();

    private:
        static VByteArray _make_packet( const json11::Json::object &o,
                                        const VByteArray &data );
        static VByteArray _make_packet( json11::Json::object *o,
                                        VByteArray::const_iterator begin,
                                        VByteArray::const_iterator end );
        Dump _dump_one();
        Dump _dump_multi(int piece_size);

        json11::Json::object _obj;
        VByteArray           _data;
        int32_t              _msg_id;
    };
    //===================================================================================

} // namespace ii
//=======================================================================================


#endif // OUTCOMINGMESSAGE_H
