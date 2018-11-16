#ifndef VPOSIX_EPOLL_H
#define VPOSIX_EPOLL_H

#include <stdint.h>
#include <functional>
#include <vector>
//#include <sys/epoll.h>


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
    public:
        static constexpr auto Wait_Max_Events = 100;

        static bool has_EPOLLIN ( uint32_t events );
        static bool has_EPOLLOUT( uint32_t events );

        EPoll();
        ~EPoll();

        void add( int fd, bool dir_in, bool dir_out, bool trigg );

        void raw_add( int fd, epoll_event* event );
        void raw_mod( int fd, epoll_event* event );
        void del( int fd );

        using CallBack = std::function<void(int,uint32_t)>; // (fd,events)
        void wait( CallBack cb, int maxevents = Wait_Max_Events, int wait_ms = -1 );

    private:
        int _epoll_fd = -1;
        int _count = 0;

        static int _create();
        static int _wait( int efd, epoll_event* events, int maxevents, int wait_ms );

        static void _add( int epoll_fd, int fd, epoll_event *event );
        static void _mod( int epoll_fd, int fd, epoll_event *event );
        static void _del( int epoll_fd, int fd );
    };

} // epoll namespace
//=======================================================================================


#endif // VPOSIX_EPOLL_H
