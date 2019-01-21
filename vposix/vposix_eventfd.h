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
