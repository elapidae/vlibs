#ifndef VPOLL_FDS_H
#define VPOLL_FDS_H

#include <stdint.h>


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
*/
//=======================================================================================


//=======================================================================================
class VEventReceiver;
//=======================================================================================
class VPoll_FDs
{
public:
    //-----------------------------------------------------------------------------------
    enum class Triggered { Level, Edge      };
    enum class Direction { In, Out, InOut   };
    //-----------------------------------------------------------------------------------
    //  Флаги, пока что, не проверены, сделано как есть в системе поллинга.
    //  По мере понимания какие флаги когда прилетают, интерфейс может меняться.
    struct EventFlags final
    {
        bool IN()       const;
        bool OUT()      const;
        bool RDHUP()    const;
        bool PRI()      const;
        bool ERR()      const;
        bool HUP()      const;

        //  Must be delete.
        uint32_t raw() const { return _events; }

    private:
        friend class VPoll_FDs;
        EventFlags(uint32_t evs);
        uint32_t _events;
    };
    //-----------------------------------------------------------------------------------
    static void add_fd( int fd, VEventReceiver *receiver,
                        Direction d = Direction::In,
                        Triggered t = Triggered::Level );

    static void mod_fd( int fd, VEventReceiver *receiver,
                        Direction d,
                        Triggered t = Triggered::Level );

    static void del_fd( int fd );

    //  Поллит по одной штуке, если окажется, что надо больше -- работать здесь.
    // static constexpr auto Wait_Max_Events = 100;
    static void poll_once( int timeout_ms = -1 );
    static void poll( volatile bool *stop, int timeout_ms = -1 );

    static void add_poll();
    static void del_poll();
    //-----------------------------------------------------------------------------------

private:
    VPoll_FDs() = delete;
};
//=======================================================================================
class VEventReceiver
{
public:
    virtual ~VEventReceiver() = default;

    virtual void event_received( VPoll_FDs::EventFlags flags ) = 0;
    //virtual void about_to_close() = 0;
};
//=======================================================================================



#endif // VPOLL_FDS_H
