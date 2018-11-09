#ifndef VPOSIX_EPOLL_H
#define VPOSIX_EPOLL_H

#include <stdint.h>
#include <functional>
#include <vector>
#include <sys/epoll.h>


//=======================================================================================
//  http://ru.manpages.org/epoll_ctl/2
//=======================================================================================

//=======================================================================================
struct epoll_event;
//=======================================================================================
namespace vposix
{
    class EPoll final
    {
        static constexpr auto Wait_Max_Events = 1024;
    public:

        struct EventFlags final
        {
            bool IN()       const;
            bool OUT()      const;
            bool RDHUP()    const;
            bool PRI()      const;
            bool ERR()      const;
            bool HUP()      const;

        private:
            friend class EPoll;
            uint32_t _events;
        };

        //using EventCallBack = std::function<void(int,EventFlags)>; // fd

        enum class Triggered { Level, Edge };
        enum class Direction { R, W, RW };

        EPoll();
        ~EPoll();

        void add( int fd, epoll_event *event );
        void del( int fd );

        std::vector<epoll_event> wait( int maxevents, int wait_ms = -1 );

    private:
        int _epoll_fd = -1;

        static int _create();
        static int _wait( int efd, epoll_event* events, int maxevents, int wait_ms );

        static void _add( int epoll_fd, int fd, epoll_event *event );
        static void _del( int epoll_fd, int fd );
    };

} // epoll namespace
//=======================================================================================


#endif // VPOSIX_EPOLL_H
