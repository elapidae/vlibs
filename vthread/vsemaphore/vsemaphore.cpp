#include "vsemaphore.h"

#include <mutex>
#include <condition_variable>
#include <atomic>

using namespace std;


//=======================================================================================
class VSemaphore::Pimpl
{
public:
    std::mutex          mutex;
    condition_variable  cv;
    atomic_int          count;
};
//=======================================================================================
VSemaphore::VSemaphore( int count )
    : p( make_shared<Pimpl>() )
{
    if ( count < 0 )
        count = 0;

    p->count = count;
}
//=======================================================================================
void VSemaphore::notify()
{
    unique_lock<std::mutex> lock( p->mutex );
    ++p->count;
    p->cv.notify_one();
}
//=======================================================================================
//  Цикл необходим из-за срывов ожидания (см. Мейерса, Современный С++ (11 стандарт)).
void VSemaphore::wait()
{
    unique_lock<std::mutex> lock( p->mutex );
    while( p->count == 0 )
    {
        p->cv.wait( lock );
    }
    --p->count;
}
//=======================================================================================
int VSemaphore::count() const
{
    return p->count;
}
//=======================================================================================
