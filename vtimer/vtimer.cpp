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


#include "vtimer.h"

#include "vposix_timerfd.h"
#include "vposix_files.h"
#include "vpoll/vpoll.h"

#include <assert.h>

//=======================================================================================
class VTimer::Pimpl : public VPoll::EventReceiver
{
public:
    //-----------------------------------------------------------------------------------
    int fd;
    //-----------------------------------------------------------------------------------
    Pimpl( VTimer* owner )
        : owner( owner )
    {
        fd = vposix::TimerFD::create_monotonic();
        VPoll::add_fd( fd, this );
    }
    //-----------------------------------------------------------------------------------
    ~Pimpl() override
    {
        stop();
        VPoll::del_fd( fd );
    }
    //-----------------------------------------------------------------------------------
    void stop()
    {
        vposix::TimerFD::stop( fd );
    }
    //-----------------------------------------------------------------------------------
    void event_received( VPoll::EventFlags flags ) override
    {
        assert( flags.take_IN()  );
        assert( flags.raw() == 0 );
        owner->timeout_count( vposix::TimerFD::read(fd) );
        owner->timeout();
    }
    //-----------------------------------------------------------------------------------
private:
    VTimer* owner;
};
//=======================================================================================
VTimer::VTimer()
    : p( new Pimpl(this) )
{}
//=======================================================================================
VTimer::~VTimer()
{}
//=======================================================================================
void VTimer::start( const std::chrono::nanoseconds &ns )
{
    vposix::TimerFD::start_monotonic( p->fd, ns );
}
//=======================================================================================
void VTimer::singleshot( const std::chrono::nanoseconds &ns )
{
    vposix::TimerFD::singleshot_monotonic( p->fd, ns );
}
//=======================================================================================
void VTimer::stop()
{
    p->stop();
}
//=======================================================================================
