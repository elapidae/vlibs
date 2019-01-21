/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


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
 *  При удалении объекта-подписчика он автоматически отписывается от zcm подписки.
 *
 *  Примерное использование:
        using Subscriber = VZCM_Subscriber<ZcmVeryLongStrangePassiveTypeName>;
        Subscriber subscriber( &zcm, "Channel" );
        subscriber.received.connect( [&](const Subscriber::ZType &msg)
        {
            .. using msg ..
        });
        subscriber.received_channel.connect( [&](const Subscriber::ZType &msg,
                                                 const std::string &channel)
        {
            .. using msg and channel ..
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
    : _zcm( z )
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
