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


#ifndef VPOSIX_FILES_H
#define VPOSIX_FILES_H

#include <string>
#include <functional>


//=======================================================================================
//  UPD 26-12-2018
//  Добавлен класс FD для автозакрывания дескрипторов файлов.
//  В VPoll идет продолжение идеи, где дескриптор автоматически ставиться в поллинг.
//=======================================================================================



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

        //  Сбрасывает флаг O_NONBLOCK.
        static void close( int fd );

        //-------------------------------------------------------------------------------
        static void _ioctl( int fd, unsigned long ctl );
        static int  _ioctl_or_err( int fd, unsigned long ctl );

        // For serial port. If defined, call ioctl.
        static void set_tio_EXCL( int fd );             //  ioctl ( TIOCEXCL )
        static void set_tio_soft_not_EXCL( int fd );    //  ioctl ( TIOCNXCL )
        //-------------------------------------------------------------------------------

        static long _fcntl_get_flags( int fd );
        static void _fcntl_set_flags( int fd, long flags );

    private:
    };
    //===================================================================================

    //===================================================================================
    class FD final
    {
    public:
        using close_func = std::function<void(int)>;

        explicit FD( int fd = -1, const close_func& cf = &Files::close );
        explicit FD( FD&& rhs );
        FD& operator = ( FD&& rhs );

        ~FD();

        bool valid() const;
        void close();

        int raw() const;

    private:
        int _fd = -1;
        close_func _close;

        FD( const FD& rhs ) = delete;
        FD& operator = ( const FD& ) = delete;
    };
    //===================================================================================

} // namespace vposix
//=======================================================================================

#endif // VPOSIX_FILES_H
