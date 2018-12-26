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
