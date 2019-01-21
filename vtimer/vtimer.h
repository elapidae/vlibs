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


#ifndef VTIMER_H
#define VTIMER_H


#include "vcallback.h"
#include <chrono>
#include <memory>

//=======================================================================================
class VTimer final
{
public:
    VCallBack<int> timeout_count;     // argument -- count of elapsed episodes.
    VCallBack<>    timeout;           // simple, without elapsed episodes.

    explicit VTimer();
    ~VTimer();

    void start( const std::chrono::nanoseconds& ns );
    void singleshot( const std::chrono::nanoseconds& ns );

    template<typename Duration>
    void start( const Duration& duration );

    template<typename Duration>
    void singleshot( const Duration& duration );

    void stop();

private:    
    class Pimpl; std::unique_ptr<Pimpl> p;
};
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
template<typename Duration>
void VTimer::start( const Duration& duration )
{
    start( std::chrono::duration_cast<std::chrono::nanoseconds>(duration) );
}
//=======================================================================================
template<typename Duration>
void VTimer::singleshot( const Duration& duration )
{
    singleshot( std::chrono::duration_cast<std::chrono::nanoseconds>(duration) );
}
//=======================================================================================

#endif // VTIMER_H
