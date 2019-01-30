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


#ifndef VUDPSOCKET_H
#define VUDPSOCKET_H

#include <memory>
#include "vipaddress.h"
#include "vstring.h"
#include "vsignal.h"


//=======================================================================================
class VUdpSocket final
{
public:
    VUdpSocket();
    ~VUdpSocket();

    //  Прослушивать обязательно, иначе при наличии данных этот сигнал будет постоянно
    //  срабатывать.
    VSignal<> ready_read;

    void bind(const VIpAddress &addr, uint16_t port = 0 );
    void bind_any( uint16_t port = 0 );

    bool is_bound() const;

    void send_to(const std::string& buf, const VIpAddress &addr, uint16_t port );

    //  No more packets if result is empty.
    VString receive( VIpAddress *ip, uint16_t* port );
    VString receive();

private:
    class Pimpl; std::unique_ptr<Pimpl> p;
};
//=======================================================================================


#endif // VUDPSOCKET_H
