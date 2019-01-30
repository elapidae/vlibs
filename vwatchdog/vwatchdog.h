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


#ifndef VWATCHDOG_H
#define VWATCHDOG_H

#include <assert.h>
#include "vtimer.h"
#include "vcallback.h"


//=======================================================================================
/*
 *  2018-12-21      by Elapidae
 *
 *  VWatchDog -- Сторожевой таймер, использует VTimer.
 *
 *  Конструируется из любого std::chrono::duration и числа повторений.
 *  Это сделано для того, чтобы не перезапускать таймер при сбросе, с одной стороны, и
 *  не нарваться на timeout на временной границе сброса и таймаута, с другой.
 *
 *  Т.е. от этого класса не требуется соблюдения точного измерения отсчетов времени.
 *
 *  times_count = 5;
 *  VWatchDog wd( seconds(1), times_count );
 *  Сигнал после вызова relax() может поступить в диапазоне времени от 4 до 5 секунд.
 *
 *  При опаздывании вызова relax(), будет вызван expired.
 *  wd.expired = [&](){ restart_all_on_watchdog(); };
 *  ...
 *  for (;;)
 *  {
 *      very_long_operation();
 *      wd.relax();
 *  }
*/
//=======================================================================================



//=======================================================================================
//      VWatchDog
//=======================================================================================
class VWatchDog
{
public:

    VCallBack<> expired;

    template<typename Duration>
    VWatchDog( const Duration& d, int times_count );

    void relax();

private:
    VTimer _timer;
    void   _on_timeout( int cnt );

    const int _times_count;
    int _cur_times_count;
};
//=======================================================================================
//      VWatchDog
//=======================================================================================



//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================
template<typename Duration>
VWatchDog::VWatchDog( const Duration& d, int times_count )
    : _times_count( times_count )
    , _cur_times_count( times_count )
{
    assert( times_count > 0 );

    _timer.timeout_count.link( this, &VWatchDog::_on_timeout );
    _timer.start( d );
}
//=======================================================================================
//      IMPLEMENTATION
//=======================================================================================


#endif // VWATCHDOG_H
