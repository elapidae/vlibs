#ifndef VZTOP_ZTOP_H
#define VZTOP_ZTOP_H

#include <functional>
#include "vztop_coder.h"

template <typename T>
class TD;

namespace vztop
{

    struct Some_ZMessage
    {
        static auto constexpr message_id = "Some_ZMessage ololo my ver == 0.0.0.1";

        int i;
        uint u;
        char c;

        Some_ZMessage(int i, uint u, char c) : i(i) , u(u), c(c) {}


    };



    template<typename T>
    class Subscriber
    {
    public:
        using ReceiveFunc = std::function<void(std::string,T*)>;
        Subscriber(ReceiveFunc func);
    };



    class ZTop
    {
    public:
        ZTop();

        template<typename T>
        void send( const T& msg )
        {
            using deploy = Deploy<T>;

            auto pack = deploy::pack( msg );

            using coder = Coder2<T,decltype(pack)>;
            auto buffer = coder::full_pack( pack );

            // TODO: SEND by bus.
        }

        template<typename ZMessage>
        void subscribe( const std::string &channel, Subscriber<ZMessage> subs )
        {

        }
    };

} // namespace vztop






#endif // VZTOP_ZTOP_H
