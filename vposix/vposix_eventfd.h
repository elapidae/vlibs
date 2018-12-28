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
        static constexpr bool do_trace() { return false; }

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

        int fd() const;

    private:
        int _fd = -1;
        Semaphore(const Semaphore&) = delete;
    };

} // vposix namespace
//=======================================================================================



#endif // VPOSIX_EVENTFD_H
