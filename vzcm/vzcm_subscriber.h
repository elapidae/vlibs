#ifndef VZCM_SUBSCRIBER_H
#define VZCM_SUBSCRIBER_H

#include "vsignal.h"
#include "zcm/zcm-cpp.hpp"

//=======================================================================================
/*  01-08-2018          by Elapidae
 *
 *  VZCM_Subscriber -- подписчик на ZCM сообщения. Во-первых, берет на себя подписку,
 *  во-вторых, не заставляет создавать класс-приемник.
 *
 *  Примерное использование:
        using Subscriber = VZCM_Subscriber<ZcmVeryLongStrangePassiveTypeName>;
        Subscriber subs( &zcm, "Channel" );
        subs.received.connect( [&](const Subscriber::ZType &msg)
        {
            .. using msg ..
        });
*/
//=======================================================================================


//=======================================================================================
//      VZCM_Subscriber<ZCM_Type>
//=======================================================================================
template<typename ZCM_Type>
class VZCM_Subscriber
{
public:
    //-----------------------------------------------------------------------------------

    using ZType = ZCM_Type;

    using Receiver          = std::function<void(const ZCM_Type&)>;
    using ReceiverChannel   = std::function<void(const ZCM_Type&, const std::string&)>;

    //-----------------------------------------------------------------------------------

    VSignal<ZCM_Type> received;
    VSignal<ZCM_Type,std::string> received_channel;

    //-----------------------------------------------------------------------------------

    VZCM_Subscriber( zcm::ZCM *z, const std::string &channel );

    virtual ~VZCM_Subscriber();


    //- private -------------------------------------------------------------------------
private:
    void _subsribe( const zcm::ReceiveBuffer*,
                    const std::string &channel,
                    const ZCM_Type *zzz );

    zcm::Subscription *_handle = nullptr;
    zcm::ZCM *_zcm;
};
//=======================================================================================
//      VZCM_Subscriber<ZCM_Type>
//=======================================================================================



//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
template<typename ZCM_Type>
VZCM_Subscriber<ZCM_Type>::VZCM_Subscriber( zcm::ZCM *z, const std::string &channel )
    : _zcm(z)
{
    _handle = z->subscribe( channel, &VZCM_Subscriber<ZCM_Type>::_subsribe, this );
    assert( _handle );
}
//=======================================================================================
template<typename ZCM_Type>
VZCM_Subscriber<ZCM_Type>::~VZCM_Subscriber()
{
    _zcm->unsubscribe( _handle );
}
//=======================================================================================
template<typename ZCM_Type>
void VZCM_Subscriber<ZCM_Type>::_subsribe( const zcm::ReceiveBuffer*,
                const std::string &channel,
                const ZCM_Type *zzz )
{
    received( *zzz );
    received_channel( *zzz, channel );
}
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================



#endif // VZCM_SUBSCRIBER_H
