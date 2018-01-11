#ifndef MESSAGE_H
#define MESSAGE_H

#include "json11.h"
#include "vbytearray.h"
#include "vsignal.h"


//=======================================================================================
namespace ii
{
    //===================================================================================
    class Message
    {
    protected:
        static const std::string msg_id_label;
        static const std::string target_label;
        static const std::string bin_size_label;
        static const std::string fragment_num_label;
        static const std::string fragment_count_label;
    };
    //===================================================================================
} // namespace ii
//=======================================================================================


#endif // MESSAGE_H
