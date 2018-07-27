#ifndef VZCM_SUBSCRIBER_H
#define VZCM_SUBSCRIBER_H

#include "vsignal.h"
#include "zcm/zcm-cpp.hpp"


template<typename ZCM_Type>
class VZCM_Subscriber
{
public:

    VSignal<ZCM_Type> received;

    VZCM_Subscriber( zcm::ZCM *z, const std::string &channel )
        : _zcm(z)
    {
        _handle = z->subscribe( channel, &VZCM_Subscriber<ZCM_Type>::_subsribe, this );
        assert( _handle );
    }

    virtual ~VZCM_Subscriber()
    {
        _zcm->unsubscribe( _handle );
    }


private:
    void _subsribe( const zcm::ReceiveBuffer*,
                    const std::string&,
                    const ZCM_Type *zzz )
    {
        received( *zzz );
    }

    zcm::Subscription *_handle = nullptr;
    zcm::ZCM *_zcm;
};

#endif // VZCM_SUBSCRIBER_H
