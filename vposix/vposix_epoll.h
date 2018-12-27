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
        static constexpr bool do_trace() { return false; }

        static uint32_t flag_IN();
        static uint32_t flag_OUT();
        static uint32_t flag_PRI();
        static uint32_t flag_RDNORM();
        static uint32_t flag_RDBAND();
        static uint32_t flag_WRNORM();
        static uint32_t flag_WRBAND();
        static uint32_t flag_MSG();
        static uint32_t flag_ERR();
        static uint32_t flag_HangUp();
        static uint32_t flag_RD_HangUp();
        //static uint32_t flag_();

        EPoll();
        ~EPoll();

        void add( int fd, void* arg, bool dir_in, bool dir_out, bool trigg );
        void mod( int fd, void* arg, bool dir_in, bool dir_out, bool trigg );
        void del( int fd );

        //  http://ru.manpages.org/epoll_wait/2
        //
        //  Заметим, что интервал timeout будет округлён в соответствии с точностью
        //  системных часов, а задержки ядерного планирования приведут к тому, что
        //  интервал блокировки может быть немного больше. Если присвоить timeout
        //  значение -1, то epoll_wait() блокируется навсегда; если значение timeout
        //  равно 0, то epoll_wait() сразу завершает работу, даже если никаких
        //  событий не произошло.
        uint wait( std::vector<epoll_event>* res, int wait_ms = -1 );

    private:
        int _epoll_fd = -1;
        int _count = 0;

        static int  _create();
        static uint _wait( int efd, epoll_event* events, int maxevents, int wait_ms );

        static void _add( int epoll_fd, int fd, epoll_event *event );
        static void _mod( int epoll_fd, int fd, epoll_event *event );
        static void _del( int epoll_fd, int fd );

        EPoll( const EPoll& ) = delete;
        EPoll& operator = ( const EPoll& ) = delete;
    };

} // epoll namespace
//=======================================================================================


#endif // VPOSIX_EPOLL_H
