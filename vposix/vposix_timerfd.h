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


#ifndef VPOSIX_TIMERFD_H
#define VPOSIX_TIMERFD_H

#include <chrono>

//=======================================================================================
//  http://ru.manpages.org/timerfd_create/2
//=======================================================================================


//=======================================================================================
struct itimerspec;
//=======================================================================================
namespace vposix
{
    //===================================================================================
    class TimerFD
    {
    public:
        using nanosecs = std::chrono::nanoseconds;

        static int  create_monotonic();
        static void start_monotonic( int fd, const nanosecs& duration );
        static void singleshot_monotonic( int fd, const nanosecs& duration );

        static void stop( int fd );
        static int read( int fd );

    private:
        static void _settime( int fd,
                             // int flags, -- 0 / TFD_TIMER_ABSTIME. Use only 0.
                             const itimerspec& new_value,
                             itimerspec* old_value = nullptr );

        static void _gettime( int fd, itimerspec* cur_value );
    };
    //===================================================================================
} // namespace vposix
//=======================================================================================


#endif // VPOSIX_TIMERFD_H
