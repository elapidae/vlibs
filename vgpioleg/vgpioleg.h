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
 *      TODO: Метод unexport_leg() исключения не бросает (точнее глушит его).
 *      Это сделано, чтобы, если нога уже была экпортирована, код работал без внешнего
 *      перехвата исключений. Необходимо поставить проверку включенной ноги, если нога
 *      не экпортирована, ничего не делать.
 *      Для решения этой задачи необходимо написать класс VFileInfo.
 */
//=======================================================================================


//=======================================================================================
class VGpioLeg
{
public:

    class Exception : public std::runtime_error
    { public: Exception(const std::string &err); };

    enum class Direction    { In, Out };
    enum class Value        { Low, Hi };


    explicit VGpioLeg( int leg );

    // unexport_leg() глушит исключение GpioException.
    VGpioLeg& unexport_leg();
    VGpioLeg& export_leg();

    VGpioLeg& set_direction( Direction dir );
    VGpioLeg& direction_out();
    VGpioLeg& direction_in();

    VGpioLeg& set_value( Value val );
    VGpioLeg& hi();
    VGpioLeg& low();

    VGpioLeg& usleep( int us );

private:
    int _leg;
};
//=======================================================================================


#endif // VGPIOLEG_H
