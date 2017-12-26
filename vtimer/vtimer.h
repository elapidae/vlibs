#ifndef VTIMER_H
#define VTIMER_H


#include "vsignal.h"
#include "vslot.h"
#include "vthread.h"

#include <chrono>

class VTimer final
{
public:
    explicit VTimer( int ms = 0 );
    ~VTimer();

    VSignal<> timeout;

    void start( int ms );
    void stop();

    bool stopped() const;

private:    
    VThread _thread;
    VSlot<> _timeout;
    bool _need_stop;
    bool _stopped;
};



//class VTimeCounter
//{
//public:

//    using duration = decltype( std::chrono::steady_clock::now() -
//                               std::chrono::steady_clock::now() );

//    void start();

//    duration elapsed() const;

//    duration restart();

//    int elapsed_ms() const;

//    int restart_ms();


//private:
//    decltype(std::chrono::steady_clock::now()) _point;
//};

#endif // VTIMER_H
