#ifndef VPOLL_H
#define VPOLL_H

#include <stdint.h>
#include <atomic>


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
        bool IN()       const;
        bool IN_only()  const;

        bool OUT()      const;
        bool RDHUP()    const;
        bool PRI()      const;
        bool ERR()      const;
        bool HUP()      const;

        //  Must be delete.
        uint32_t raw() const { return _events; }

    private:
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

    //  Поллит по одной штуке, если окажется, что надо больше -- работать здесь.
    static constexpr auto Wait_Max_Events = 10;
    //static void poll_once( int timeout_ms = -1 );
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
    virtual ~EventReceiver() = default;

    virtual void event_received( VPoll::EventFlags flags ) = 0;
    //virtual void about_to_close() = 0;
};
//=======================================================================================



#endif // VPOLL_H
