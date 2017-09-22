#ifndef VSEMAPHOREQUEUE_H
#define VSEMAPHOREQUEUE_H

#include <mutex>
#include <queue>
#include "vsemaphore/vsemaphore.h"

//=======================================================================================
/*
 *      VSemaphoreQueue -- потокобезопасная очередь
 *
 *      NB! Небезопасна с точки зрения транзакционности при исключениях, т.к. решает
 *      задачи, несовместимые с таким поведением.
*/
//=======================================================================================



//=======================================================================================
//      SEMAPHORE QUEUE
//=======================================================================================
template< class T >
class VSemaphoreQueue
{
public:

    void push( const T& val );

    T    pop();

    int  size()  const;

    bool empty() const;

private:
    std::queue<T>   _queue;
    std::mutex      _mutex;
    VSemaphore      _semaphore;
};
//=======================================================================================
//      SEMAPHORE QUEUE
//=======================================================================================



//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
template<class T>
void VSemaphoreQueue<T>::push( const T &val )
{
    std::unique_lock<std::mutex> lock( _mutex );
    _queue.push( val );
    _semaphore.notify();
}
//=======================================================================================
template<class T>
T VSemaphoreQueue<T>::pop()
{
    _semaphore.wait();

    std::unique_lock<std::mutex> lock( _mutex );
    auto res( _queue.front() );
    _queue.pop();

    return res;
}
//=======================================================================================
template<class T>
int VSemaphoreQueue<T>::size() const
{
    return _semaphore.count();
}
//=======================================================================================
template<class T>
bool VSemaphoreQueue<T>::empty() const
{
    return size() == 0;
}
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================



#endif // VSEMAPHOREQUEUE_H
