#ifndef VPOSIX_FILES_H
#define VPOSIX_FILES_H

#include <string>



//=======================================================================================
namespace vposix
{
    //===================================================================================
    class Files
    {
        static constexpr bool do_trace() { return false; }
    public:
        using cstr = const std::string&;

        static int open( cstr name, int flags );
        static int open_mode( cstr name, int flags, mode_t mode );

        static ssize_t _write( int fd, const void *buf, size_t count );
        static ssize_t write( int fd, cstr buf);

        static ssize_t read( int fd, void *buf, size_t count );
        static ssize_t read_or_err( int fd, void *buf, size_t count );

        static int _remove( const char *pathname );
        static void remove( cstr pathname );

        static void close( int fd );

        static void _ioctl( int fd, unsigned long ctl );
        static void _set_TIOCEXCL( int fd ); // For serial port. If defined, call ioctl.

    private:
    };
    //===================================================================================

    //===================================================================================
    class FD final
    {
    public:
        explicit FD( int fd = -1 );
        explicit FD( FD&& rhs );
        FD& operator = ( FD&& rhs );

        ~FD();

        bool valid() const;
        void close();

        int raw() const;

    private:
        int _fd = -1;

        FD( const FD& rhs ) = delete;
        FD& operator = ( const FD& ) = delete;
    };
    //===================================================================================

} // namespace vposix
//=======================================================================================

#endif // VPOSIX_FILES_H
