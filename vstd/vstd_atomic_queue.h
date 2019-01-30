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


#ifndef VSTD_ATOMIC_QUEUE_H
#define VSTD_ATOMIC_QUEUE_H


#include <queue>
#include <stdexcept>
#include <mutex>


//=======================================================================================
namespace vstd
{
    //===================================================================================
    template<typename T>
    class atomic_queue
    {
    public:

        template< typename ... Args >
        void emplace( Args&&... args );

        bool   empty()  const;
        size_t size()   const;

        const T& front() const;
        T& front();

        void pop();
        void clear();

        //  Advanced interface
        template< typename ... Args >
        void enqueue( Args&&... args );

        T dequeue();

    private:
        std::queue<T> _queue;
        mutable std::mutex _mutex;
    }; // atomic_queue
    //===================================================================================


    //===================================================================================
    //      IMPLEMEMNTATION
    //===================================================================================
    template<typename T>
    template< typename ... Args >
    void atomic_queue<T>::emplace( Args&& ... args )
    {
        std::unique_lock<std::mutex> lock( _mutex );
        _queue.emplace( std::forward<Args>(args)... );
    }
    //===================================================================================
    template<typename T>
    bool atomic_queue<T>::empty() const
    {
        std::unique_lock<std::mutex> lock( _mutex );
        return _queue.empty();
    }
    //===================================================================================
    template<typename T>
    size_t atomic_queue<T>::size() const
    {
        std::unique_lock<std::mutex> lock( _mutex );
        return _queue.size();
    }
    //===================================================================================
    template<typename T>
    const T& atomic_queue<T>::front() const
    {
        std::unique_lock<std::mutex> lock( _mutex );
        return _queue.front();
    }
    //===================================================================================
    template<typename T>
    T& atomic_queue<T>::front()
    {
        std::unique_lock<std::mutex> lock( _mutex );
        return _queue.front();
    }
    //===================================================================================
    template<typename T>
    void atomic_queue<T>::pop()
    {
        std::unique_lock<std::mutex> lock( _mutex );
        _queue.pop();
    }
    //===================================================================================
    template<typename T>
    void atomic_queue<T>::clear()
    {
        std::unique_lock<std::mutex> lock( _mutex );
        while ( !empty() )
            _queue.pop();
    }
    //===================================================================================
    template<typename T>
    template<typename ... Args>
    void atomic_queue<T>::enqueue( Args&&... args )
    {
        emplace( std::forward<Args>(args)... );
    }
    //===================================================================================
    template<typename T>
    T atomic_queue<T>::dequeue()
    {
        std::unique_lock<std::mutex> lock( _mutex );
        if ( _queue.empty() )
            throw std::out_of_range( "atomic queue empty in dequeue()." );

        T res = _queue.front();
        _queue.pop();
        return res;
    }
    //===================================================================================
} // namespace vstd
//=======================================================================================

#endif // VSTD_ATOMIC_QUEUE_H
