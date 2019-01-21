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


#ifndef VTHREAD_H
#define VTHREAD_H

#include <memory>
#include <atomic>

#include "vthreadqueue.h"



//=======================================================================================
//      VTHREAD INTERFACE
//=======================================================================================
class VThreadInterface
{
public:
    explicit VThreadInterface( const std::string &label );
    virtual ~VThreadInterface();

    // Поток останавливается когда все задачи будут обработаны.
    // Если были исключения, они прилетят сюда (если по Стандарту...).
    void stop();

    // Прерывает поток сразу после выполнения текущей задачи (если она выполняется).
    // Другие задания, если они есть, будут проигнорированы потоком (но не удалены
    // из очереди, они там останутся до удаления потока).
    // Если были исключения, они прилетят сюда (если по Стандарту...).
    void break_now();

    // Было исключение, если вы в Стандарте, то делайте do_break() и перехватывайте его.
    bool has_exception() const;

    // При возбуждении исключения будет возвращать правду.
    bool has_stopped() const;

    // Количество еще не отработанных заданий.
    int queue_size() const;

    // Проталкивание заданий - функторов в очередь потока.
    template< typename Fn, typename ... Args >
    void finvoke( Fn fn, const Args& ... args );

    // Проталкивание заданий - методов классов в очередь потока.
    template<typename Cls, typename Fn, typename ... Args >
    void cinvoke( Cls *cls, Fn fn, const Args& ... args );

protected:
    // Способ вырубить поток в зависимости от реализации, используется в _run.
    virtual void _thread_get() = 0;

    // Сделан возврат указателя и прием не класса, а чёрти чего из-за особенностей
    // запуска pthread. Но он, всё равно, не умеет нормально прокидывать исключения...
    static void * _run( void * self_ );


private:
    VThreadQueue *_queue; // Для вызова из шаблонов.

    class Pimpl;
    std::unique_ptr<Pimpl> p;
};
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
template< typename Fn, typename ... Args >
void VThreadInterface::finvoke( Fn fn, const Args& ... args )
{
    _queue->fpush( fn, args... );
}
//=======================================================================================
template<typename Cls, typename Fn, typename ... Args >
void VThreadInterface::cinvoke( Cls *cls, Fn fn, const Args& ... args )
{
    _queue->cpush( cls, fn, args... );
}
//=======================================================================================
//      VTHREAD INTERFACE
//=======================================================================================



#ifndef VTHREAD_USE_PTHREAD
//=======================================================================================
//      VTHREAD 11
//=======================================================================================
class _VThread11 final : public VThreadInterface
{
public:
//    enum _Detached { Detached };
//    _VThread11( _Detached, const std::string &label = std::string() );

    _VThread11( const std::string &label = std::string() );
    ~_VThread11() override;


private:
    virtual void _thread_get() override;

    class Pimpl;
    std::unique_ptr<Pimpl> p;
};
using VThread = _VThread11;
//=======================================================================================
//      VTHREAD 11
//=======================================================================================
#else
//=======================================================================================
//      VTHREAD ON PTHREAD
//=======================================================================================
class _VThreadP final : public VThreadInterface
{
public:
    _VThreadP( const std::string &label = std::string() );
    ~_VThreadP();

    void detach();

private:
    virtual void _thread_get() override;

    unsigned long int _pthread_handle;
};
using VThread = _VThreadP;
//=======================================================================================
//      VTHREAD ON PTHREAD
//=======================================================================================
#endif // VTHREAD_USE_PTHREAD



//=======================================================================================
class TimeAccum
{
public:
    TimeAccum();

    void start();
    void accumulate();

    // nanosec.
    int64_t elapsed() const;

private:
    std::atomic<int64_t> _elapsed;
    using _time_t = decltype(std::chrono::high_resolution_clock::now());
    _time_t _time;
};
//=======================================================================================




#endif // VTHREAD_H
