#ifndef VPOSIX_EPOLL_H
#define VPOSIX_EPOLL_H

#include <stdint.h>
#include <functional>
#include <sys/epoll.h>
#include <vector>

//=======================================================================================
//  http://ru.manpages.org/epoll_ctl/2
//=======================================================================================

//=======================================================================================
namespace vposix
{
    class EPoll final
    {
    public:
        static bool has_EPOLLIN ( uint32_t events );
        static bool has_EPOLLOUT( uint32_t events );

        EPoll();
        ~EPoll();

        void add( int fd, void* arg, bool dir_in, bool dir_out, bool trigg );
        void mod( int fd, void* arg, bool dir_in, bool dir_out, bool trigg );
        void del( int fd );

        int wait_many( std::vector<epoll_event>* res, int wait_ms = -1 );
        epoll_event wait_1( int wait_ms = -1 );

    private:
        int _epoll_fd = -1;
        int _count = 0;

        static int _create();
        static int _wait( int efd, epoll_event* events, int maxevents, int wait_ms );

        static void _add( int epoll_fd, int fd, epoll_event *event );
        static void _mod( int epoll_fd, int fd, epoll_event *event );
        static void _del( int epoll_fd, int fd );

        EPoll( const EPoll& ) = delete;
        EPoll& operator = ( const EPoll& ) = delete;
    };

} // epoll namespace
//=======================================================================================


#endif // VPOSIX_EPOLL_H
