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


#ifndef VPOLL_H
#define VPOLL_H

#include <stdint.h>
#include <atomic>
#include "vposix_files.h"

//=======================================================================================
/*      21-11-2018  by Elapidae
 *
 *  Эта часть системы поллинга подразумевается для использования middleware.
 *  Т.е. здесь решается вопросы, связанные с управлением epoll механизма теми классами,
 *  которым необходим поллинг (сокеты, порты, таймеры и т.д.). Часть, предназначенная
 *  для конечного потребителя поллинга находится в классе VPoll.
 *
 *  UPD: Вообще никакая часть конечному пользователю не должна пригодится.
 *  Вся машинерия обязана поместиться в VApplication и VThread.
 *
 *
 *  UPD 22-11-2018
 *  Было принято решение сделать поллинг независимым компонентом, если пользователь не
 *  хочет использовать подход VApplication/VThread, то берет на себя обязанность сам
 *  контролировать создание и удаление очередей поллинга по потокам.
 *
 *  В любом случае подразумевается один поллинг на поток.
 *  NB! Поток в котором вызввается add_fd() и будет хозяином поллинга!
 *  Даже не подразумевается попыток создавать сущности в одном потоке, поллинг в другом,
 *  удаление в третьем!
 *
 *  Использование (в общем случае):
 *
 *  VPoll::add_poll();
 *
 *  int fd = create_handle_of_something_for_polling();
 *  VPoll::add_fd( fd, &any_receiver );
 *
 *  while (non_stop)
 *  {
 *      VPoll::poll_once();
 *  }
 *  // Maybe will replace to VPoll::poll( &stop_flag );
 *
 *  VPoll::del_fd( fd );
 *  VPoll::del_poll();
*/
//=======================================================================================


//=======================================================================================
class VPoll
{
public:
    //-----------------------------------------------------------------------------------
    class EventReceiver;
    //-----------------------------------------------------------------------------------
    enum class Triggered { Level, Edge      };
    enum class Direction { In, Out, InOut   };
    //-----------------------------------------------------------------------------------
    //  Флаги, пока что, не проверены, сделано как есть в системе поллинга.
    //  По мере понимания какие флаги когда прилетают, интерфейс может меняться.
    struct EventFlags final
    {
        bool take_IN();
        bool take_OUT();
        bool take_HangUp();
        bool take_RD_HangUp();
        bool take_ERR();

        bool OUT()          const;
        bool PRI()          const;

        //  Must be delete.
        uint32_t raw()      const;
        bool     empty()    const;

        void throw_not_empty() const;

    private:
        bool _take_flag( uint32_t flag );
        friend class VPoll;
        EventFlags(uint32_t evs);
        uint32_t _events;
    };
    //-----------------------------------------------------------------------------------
    static void add_fd( int fd, EventReceiver *receiver,
                        Direction d = Direction::In,
                        Triggered t = Triggered::Level );

    static void mod_fd( int fd, EventReceiver *receiver,
                        Direction d, Triggered t = Triggered::Level );

    static void del_fd( int fd );

    static constexpr auto Wait_Max_Events = 32;
    static void poll( bool *stop, int timeout_ms = -1 );

    static void add_poll();
    static void del_poll();
    //-----------------------------------------------------------------------------------

private:
    VPoll() = delete;
};
//=======================================================================================
class VPoll::EventReceiver
{
public:
    virtual ~EventReceiver();
    virtual void event_received( VPoll::EventFlags flags ) = 0;
};
//=======================================================================================
class FD_Polled final
{
public:
    explicit FD_Polled();
    explicit FD_Polled( int fd,
                        VPoll::EventReceiver *receiver,
                        const vposix::FD::close_func& cf = vposix::Files::close,
                        VPoll::Direction d = VPoll::Direction::In,
                        VPoll::Triggered t = VPoll::Triggered::Level );

    explicit FD_Polled( FD_Polled && rhs );
    FD_Polled& operator = ( FD_Polled && rhs );
    ~FD_Polled();

    bool valid() const;
    void close();

    int raw() const;

private:
    vposix::FD _fd;

    FD_Polled( const FD_Polled& rhs ) = delete;
    FD_Polled& operator = ( const FD_Polled& ) = delete;
};
//=======================================================================================



#endif // VPOLL_H
