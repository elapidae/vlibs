#ifndef VPOSIX_EVENTFD_H
#define VPOSIX_EVENTFD_H


//=======================================================================================
// http://ru.manpages.org/eventfd/2
//=======================================================================================


//=======================================================================================
namespace vposix
{
    class EventFD
    {
    public:
        //  Неблокируемые.
        static int  _semaphore_create();
        static bool _semaphore_read  ( int fd );
        static void _semaphore_write ( int fd );
    };

    class Semaphore final
    {
    public:
        Semaphore();
        ~Semaphore();

        void inc();
        bool dec();

    private:
        int _fd;
        Semaphore(const Semaphore&) = delete;
    };

} // vposix namespace
//=======================================================================================



#endif // VPOSIX_EVENTFD_H
