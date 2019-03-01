#include "transmitterbychannels.h"


//=======================================================================================
void TransmitterByChannels::decode( serialization::ReadBuffer *buf,
                                    const std::string &channel )
{
    p->decode( buf, channel );
}
//=======================================================================================
void TransmitterByChannels::decode( const VString &buf,
                                    const std::string &channel )
{
    p->decode( buf, channel );
}
//=======================================================================================

