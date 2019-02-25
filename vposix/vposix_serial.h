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


#ifndef VPOSIX_SERIAL_H
#define VPOSIX_SERIAL_H

#include <string>
#include <memory>

//=======================================================================================
//  http://www.opennet.ru/man.shtml?topic=tcgetattr&category=3&russian=0
// **************************************************************************************
// Обратите внимание, что tcsetattr() сообщает об успешном завершении, если хотя бы одно
//  из запрошенных изменений может быть успешно выполнено. Поэтому, при необходимости
//  одновременного изменения нескольких параметров, может понадобится после этой функции
//  вызвать tcgetattr() для того, чтобы убедиться, что все изменения были выполнены
//  успешно.
// **************************************************************************************
//=======================================================================================


//=======================================================================================
struct termios;
//=======================================================================================


//=======================================================================================
namespace vposix
{
    //===================================================================================
    class Serial
    {
    public:

        static int open( const std::string& fname );
        static int try_open( const std::string& fname, std::string* err );

        static void _tio_init( termios *tio );
        static void tio_get( int fd, termios *tio );            //  init it himself.
        static void tio_set( int fd, const termios &tio );      //  set, then check.
        static void tio_soft_set( int fd, const termios &tio ); //  try to set.

        using termios_ptr = std::shared_ptr<termios>;
        static termios_ptr tio_save( int fd );

        //  Tune step by step.
        static void _tio_cfmakeraw( termios *tio );

        //  makeraw and set: CLOCAL, c_cc[VTIME] = 0; c_cc[VMIN] = 0; c_cflag |= CREAD;
        static void tio_set_common_props( termios *tio );

        //  Надоело делать никому не нужные перечисления. Установка только на 8 дата-бит.
        static void tio_set_databits8( termios *tio );

        enum class Parity { No, Odd, Even };
        static void tio_set_parity( Parity p, termios *tio );

        enum class StopBits { One, OneAndHalf, Two };
        static void tio_set_stopbits( StopBits sb, termios *tio );

        enum class FlowControl { No, Hardware, Software };
        static void tio_set_flowcontrol( FlowControl fc, termios *tio );

        static void _tio_cfsetspeed( int spd , termios *tio );

        //  Попробует перевести в перечислимую скорость,
        //  если не получится -- даст исключение.
        static void _check_speed( int spd );

        //  get options, then set:
        //  common_props, databits8, parity, flow, stopbits.
        static void set_complex_options( int fd,
                                         Parity p,
                                         StopBits sb,
                                         FlowControl fc,
                                         int spd );

        static void flush_io( int fd );

    }; // Serial class
    //===================================================================================
} // namespace vposix
//=======================================================================================


#endif // VPOSIX_SERIAL_H
