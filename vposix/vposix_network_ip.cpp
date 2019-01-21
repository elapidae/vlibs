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


#include "vposix_network_ip.h"

#include "verror.h"

using namespace vposix;

//=======================================================================================
void my_ip_addr::set_a4( const in_addr& a4 )
{
    ip4 = a4;
    ip_type = IpType::Ip4;
}
//=======================================================================================
void my_ip_addr::set_a6( const in6_addr& a6 )
{
    ip6 = a6;
    ip_type = IpType::Ip6;
}
//=======================================================================================
int my_ip_addr::af() const
{
    if ( ip_type == IpType::Ip4 ) return AF_INET;
    if ( ip_type == IpType::Ip6 ) return AF_INET6;

    throw verror("Bad ip type");
}
//=======================================================================================

