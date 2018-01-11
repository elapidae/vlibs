#include "net_core.h"


//ii::SessionId ii::SessionId::load( const VByteArray::const_iterator *begin,
//                                   const VByteArray::const_iterator end )
//{

//}

bool ii::SessionId::operator ==(const ii::SessionId &rhs) const
{
    return f == rhs.f &&
            s == rhs.s;
}

bool ii::SessionId::operator !=(const ii::SessionId &rhs) const
{
    return !( *this == rhs );
}
