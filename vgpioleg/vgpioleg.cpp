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


#include "vgpioleg.h"

#include "vfile.h"
#include "vcat.h"
#include <unistd.h> // for usleep

using namespace std;

//=======================================================================================
static const string  gpio_path         = "/sys/class/gpio/";
static const auto    export_filename   = gpio_path + "export";
static const auto    unexport_filename = gpio_path + "unexport";
//=======================================================================================


//=======================================================================================
VGpioLeg::VGpioLeg( int leg )
    : _leg( leg )
{}
//=======================================================================================
VGpioLeg &VGpioLeg::unexport_leg()
{
    try
    {
        tr1::VFile(unexport_filename).write( vcat(_leg) );
    }
    catch( const std::exception& )
    {}
    return *this;
}
//=======================================================================================
VGpioLeg &VGpioLeg::export_leg()
{
    tr1::VFile(export_filename).write( vcat(_leg) );
    return *this;
}
//=======================================================================================
VGpioLeg &VGpioLeg::set_direction( VGpioLeg::Direction dir )
{
    auto direction = dir == Direction::In ? "in" : "out";
    tr1::VFile(vcat(gpio_path, "gpio", _leg,"/direction")).write( direction );
    return *this;
}
//=======================================================================================
VGpioLeg &VGpioLeg::direction_out()
{
    return set_direction( Direction::Out );
}
//=======================================================================================
VGpioLeg &VGpioLeg::direction_in()
{
    return set_direction( Direction::In );
}
//=======================================================================================
VGpioLeg &VGpioLeg::set_value( VGpioLeg::Value val )
{
    auto value = val == Value::Low ? "0" : "1";
    tr1::VFile(vcat(gpio_path, "gpio", _leg, "/value")).write( value );
    return *this;
}
//=======================================================================================
VGpioLeg &VGpioLeg::value_hi()
{
    return set_value( Value::Hi );
}
//=======================================================================================
VGpioLeg &VGpioLeg::value_low()
{
    return set_value( Value::Low );
}
//=======================================================================================
VGpioLeg &VGpioLeg::usleep( int us )
{
    ::usleep( us );
    return *this;
}
//=======================================================================================
