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
template< typename T >
class VSemaphoreQueue
{
public:

    void push( const T& val );

    T    pop();

    int  size()  const;

    bool empty() const;

    void clear();

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
template<typename T>
void VSemaphoreQueue<T>::push( const T &val )
{
    std::unique_lock<std::mutex> lock( _mutex );
    _queue.push( val );
    _semaphore.notify();
}
//=======================================================================================
template<typename T>
T VSemaphoreQueue<T>::pop()
{
    _semaphore.wait();

    std::unique_lock<std::mutex> lock( _mutex );
    auto res( _queue.front() );
    _queue.pop();

    return res;
}
//=======================================================================================
template<typename T>
int VSemaphoreQueue<T>::size() const
{
    return _semaphore.count();
}
//=======================================================================================
template<typename T>
bool VSemaphoreQueue<T>::empty() const
{
    return size() == 0;
}
//=======================================================================================
template<typename T>
void VSemaphoreQueue<T>::clear()
{
    while (!empty()) pop();
}
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================



#endif // VSEMAPHOREQUEUE_H
