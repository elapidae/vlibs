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


#ifndef VTIMEMETER_H
#define VTIMEMETER_H

#include <chrono>

//=======================================================================================
/// General template class. Use specifications instead
template<typename Clk>
class _vtime_meter
{
public:

    using time_point = typename Clk::time_point;
    using duration   = typename Clk::duration;

    class Duration : public duration
    {
    public:
        Duration( const duration& rhs );

        std::chrono::seconds       sec() const;
        std::chrono::milliseconds  ms()  const;
        std::chrono::microseconds  us()  const;
        std::chrono::nanoseconds   ns()  const;
    };

    _vtime_meter();

    enum _stopped { Stopped };
    _vtime_meter( _stopped );

    Duration elapsed() const;
    Duration restart();

    Duration pause();
    Duration unpause();

private:
    duration   _elapsed {};
    time_point _catched {};
    bool _paused = false;
};
//=======================================================================================
template<typename Clk>
_vtime_meter<Clk>::_vtime_meter()
    : _elapsed( 0 )
    , _catched( Clk::now() )
    , _paused( false )
{}
//=======================================================================================
template<typename Clk>
_vtime_meter<Clk>::_vtime_meter( _stopped )
    : _elapsed( 0 )
    , _paused( true )
{}
//=======================================================================================
template<typename Clk>
typename _vtime_meter<Clk>::Duration
_vtime_meter<Clk>::elapsed() const
{
    if ( _paused )
        return Duration(_elapsed);

    return _elapsed + (Clk::now() - _catched);
}
//=======================================================================================
template<typename Clk>
typename _vtime_meter<Clk>::Duration
_vtime_meter<Clk>::restart()
{
    auto res = elapsed();
    _paused  = false;
    _elapsed = duration{};
    _catched = Clk::now();
    return res;
}
//=======================================================================================
template<typename Clk>
typename _vtime_meter<Clk>::Duration
_vtime_meter<Clk>::pause()
{
    auto res = elapsed();
    _paused  = true;
    _elapsed = res;
    return res;
}
//=======================================================================================
template<typename Clk>
typename _vtime_meter<Clk>::Duration
_vtime_meter<Clk>::unpause()
{
    auto res = elapsed();
    _paused  = false;
    _elapsed = res;
    _catched = Clk::now();
    return res;
}
//=======================================================================================
//=======================================================================================
template<typename Clk>
_vtime_meter<Clk>::Duration::Duration( const duration& rhs )
    : duration( rhs )
{}
//=======================================================================================
template<typename Clk>
std::chrono::seconds _vtime_meter<Clk>::Duration::sec() const
{ return std::chrono::duration_cast<std::chrono::seconds>(*this); }
//=======================================================================================
template<typename Clk>
std::chrono::milliseconds _vtime_meter<Clk>::Duration::ms() const
{ return std::chrono::duration_cast<std::chrono::milliseconds>(*this); }
//=======================================================================================
template<typename Clk>
std::chrono::microseconds _vtime_meter<Clk>::Duration::us() const
{ return std::chrono::duration_cast<std::chrono::microseconds>(*this); }
//=======================================================================================
template<typename Clk>
std::chrono::nanoseconds _vtime_meter<Clk>::Duration::ns() const
{ return std::chrono::duration_cast<std::chrono::nanoseconds>(*this); }
//=======================================================================================


//=======================================================================================
using vtime_meter_system          = _vtime_meter<std::chrono::system_clock>;
using vtime_meter_steady          = _vtime_meter<std::chrono::steady_clock>;
using vtime_meter_high_resolution = _vtime_meter<std::chrono::high_resolution_clock>;
//=======================================================================================
using VTimeMeter = vtime_meter_steady;
//=======================================================================================




#endif // VTIMEMETER_H
