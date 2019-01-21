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


#ifndef VGPIOLEG_H
#define VGPIOLEG_H

#include <stdexcept>


//=======================================================================================
/**
 *      class VGpioLeg -- вспомогательный класс для управления состояниями GPIO ног.
 *
 *      Класс тривиальный, не хранит никаких внутренних состояний и выполняет
 *      операции непосредственно над файлами в системной папке /sys/class/gpio/.
 *
 *      Подходит только для Linux, предполатается, что пользователь знаком с методами
 *      управления GPIO ногами в этой системе.
 *
 *      Пример правильного использования:
 *      int leg = 4;
 *      VGpioLeg(leg).unexport()
 *                   .export()
 *                   .direction_out()
 *                   .hi()
 *                   .usleep( some_us )
 *                   .low();
 *
 *      Можно объявить объект и работать с ним:
 *      VGpioLeg gpio(leg);
 *      gpio.unexport()
 *          .export()
 *          .direction_out()
 *          .hi()
 *          .usleep( some_us )
 *          .low();
 *
 *      NB!
 *      Если произошли ошибки, бросает исключение
 *      VGpioLeg::Exception (наследник std::runtime_error).
 *
 *      NB!!!
 *      Метод unexport_leg() исключения не бросает (точнее глушит его).
 *
 *      UPD 2018-12-20: Поудалял лишнего, вообщем, будьте проще...
 */
//=======================================================================================


//=======================================================================================
class VGpioLeg
{
public:

    enum class Direction    { In, Out };
    enum class Value        { Low, Hi };

    explicit VGpioLeg( int leg );

    // unexport_leg() при ошибке глушит исключение.
    VGpioLeg& unexport_leg();
    VGpioLeg& export_leg();

    VGpioLeg& set_direction( Direction dir );
    VGpioLeg& direction_out();
    VGpioLeg& direction_in();

    VGpioLeg& set_value( Value val );
    VGpioLeg& value_hi();
    VGpioLeg& value_low();

    VGpioLeg& usleep( int us );

private:
    int _leg;
};
//=======================================================================================


#endif // VGPIOLEG_H
