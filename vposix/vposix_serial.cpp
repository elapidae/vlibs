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


#include "vposix_serial.h"

#include "verror.h"

#include "vposix_core.h"
#include "vposix_files.h"

#include <assert.h>
#include <termios.h>
#include <string.h>     // Here: bzero
#include <fcntl.h>      // Here: O_NOCTTY | O_NONBLOCK | O_EXCL;




using namespace vposix;


//=======================================================================================
int Serial::open( const std::string &fname )
{
    int flags = O_NOCTTY | O_NONBLOCK | O_EXCL | O_CLOEXEC;

    flags |= O_RDWR;    // Every time we can read and write.

    return Files::open( fname, flags );
}
//=======================================================================================
void Serial::flush_io(int fd)
{
    auto res = Core::linux_call( ::tcflush, "tcflush", fd, TCIOFLUSH );
    assert( res == 0 );
}
//=======================================================================================


//=======================================================================================
//      TERMIOS
//=======================================================================================
static speed_t tio_normal_speed_to_speedcode( int speed )
{
    switch( speed )
    {
    case      0: return      B0;
    case     50: return     B50;
    case     75: return     B75;
    case    110: return    B110;
    case    134: return    B134;
    case    150: return    B150;
    case    200: return    B200;
    case    300: return    B300;
    case    600: return    B600;
    case   1200: return   B1200;
    case   1800: return   B1800;
    case   2400: return   B2400;
    case   4800: return   B4800;
    case   9600: return   B9600;
    case  19200: return  B19200;
    case  38400: return  B38400;
    case  57600: return  B57600;
    case 115200: return B115200;
    case 230400: return B230400;
    case 460800: return B460800;
    }
    throw verror( "Bad serial speed: ", speed );
}
//=======================================================================================
//#define NCCS 32
//struct termios
//  {
//    tcflag_t c_iflag;		/* input mode flags */
//    tcflag_t c_oflag;		/* output mode flags */
//    tcflag_t c_cflag;		/* control mode flags */
//    tcflag_t c_lflag;		/* local mode flags */
//    cc_t c_line;			/* line discipline */
//    cc_t c_cc[NCCS];		/* control characters */
//    speed_t c_ispeed;		/* input speed */
//    speed_t c_ospeed;		/* output speed */
//#define _HAVE_STRUCT_TERMIOS_C_ISPEED 1
//#define _HAVE_STRUCT_TERMIOS_C_OSPEED 1
//  };
//
bool tio_equals( const termios& t1, const termios& t2 )
{
    if ( t1.c_iflag != t2.c_iflag ) return false;
    if ( t1.c_oflag != t2.c_oflag ) return false;
    if ( t1.c_cflag != t2.c_cflag ) return false;
    if ( t1.c_lflag != t2.c_lflag ) return false;
    if ( t1.c_line  != t2.c_line  ) return false;

    for ( int i = 0; i < NCCS; ++i )
        if ( t1.c_cc[i] != t2.c_cc[i] ) return false;

    if ( t1.c_ispeed != t2.c_ispeed ) return false;
    if ( t1.c_ospeed != t2.c_ospeed ) return false;

    return true;
}
//=======================================================================================
void Serial::_tio_init( termios *tio )
{
    ::bzero( tio, sizeof(*tio) );
}
//=======================================================================================
void Serial::tio_get( int fd, termios *tio )
{
    _tio_init( tio );
    auto res = Core::linux_call( ::tcgetattr, "::tcgetattr", fd, tio );
    assert( res == 0 );
}
//=======================================================================================
void Serial::tio_set( int fd, const termios& tio )
{
    auto res = Core::linux_call( ::tcsetattr, "::tcsetattr", fd, TCSANOW, &tio );
    assert( res == 0 );

    termios new_tio;
    tio_get( fd, &new_tio );
    assert( tio_equals(tio, new_tio) );
}
//=======================================================================================
void Serial::tio_soft_set( int fd, const termios &tio )
{
    Core::linux_call_or_err( ::tcsetattr, fd, TCSANOW, &tio );
}
//=======================================================================================
std::shared_ptr<termios> Serial::tio_save( int fd )
{
    auto res = std::make_shared<termios>();
    tio_get( fd, res.get() );
    return res;
}
//=======================================================================================
void Serial::_tio_cfmakeraw( termios *tio )
{
    ::cfmakeraw( tio );
}
//=======================================================================================
void Serial::tio_set_common_props( termios *tio )
{
    _tio_cfmakeraw( tio );

    tio->c_cflag |= CLOCAL;
    tio->c_cc[VTIME] = 0;
    tio->c_cc[VMIN] = 0;
    tio->c_cflag |= CREAD;
}
//=======================================================================================
void Serial::tio_set_databits8( termios *tio )
{
    tio->c_cflag &= decltype(tio->c_cflag)(~CSIZE);
    tio->c_cflag |= CS8;
}
//=======================================================================================
void Serial::tio_set_parity( Parity p, termios *tio )
{
    tio->c_iflag &= decltype(tio->c_iflag)(~(PARMRK | INPCK));
    tio->c_iflag |= IGNPAR;

    switch (p)
    {
    case Parity::No:
        tio->c_cflag &= decltype(tio->c_cflag)(~PARENB);
        return;

    case Parity::Even:
        tio->c_cflag &= decltype(tio->c_cflag)(~PARODD);
        tio->c_cflag |= PARENB;
        return;

    case Parity::Odd:
        tio->c_cflag |= PARENB | PARODD;
        return;
    }
    throw verror("Bad parity");

//#ifdef CMSPAR
//    // Here Installation parity only for GNU/Linux where the macro CMSPAR.
//    case QSerialPort::SpaceParity:
//        tio->c_cflag &= ~PARODD;
//        tio->c_cflag |= PARENB | CMSPAR;
//        break;
//    case QSerialPort::MarkParity:
//        tio->c_cflag |= PARENB | CMSPAR | PARODD;
//        break;
    //#endif
}
//=======================================================================================
void Serial::tio_set_stopbits( StopBits sb, termios *tio )
{
    switch ( sb )
    {
    case StopBits::One:
        tio->c_cflag &= decltype(tio->c_cflag)(~CSTOPB);
        return;
    case StopBits::Two:
        tio->c_cflag |= CSTOPB;
        return;
    case StopBits::OneAndHalf:
        tio->c_cflag &= decltype(tio->c_cflag)(~CSTOPB);
        return;
    }
    throw verror("Bad stop bits");
}
//=======================================================================================
void Serial::tio_set_flowcontrol(Serial::FlowControl fc, termios *tio)
{
    switch ( fc )
    {
    case FlowControl::No:
        tio->c_cflag &= ~CRTSCTS;
        tio->c_iflag &= decltype(tio->c_iflag)(~(IXON | IXOFF | IXANY));
        return;
    case FlowControl::Hardware:
        tio->c_cflag |= CRTSCTS;
        tio->c_iflag &= decltype(tio->c_iflag)(~(IXON | IXOFF | IXANY));
        return;
    case FlowControl::Software:
        tio->c_cflag &= ~CRTSCTS;
        tio->c_iflag |= IXON | IXOFF | IXANY;
        return;
    }
    throw verror("Bad flow control");
}
//=======================================================================================
void Serial::_tio_cfsetspeed( int spd, termios *tio )
{
    auto spd_code = tio_normal_speed_to_speedcode( spd );
    auto res = Core::linux_call( ::cfsetspeed, "::cfsetspeed", tio, spd_code );
    assert( res == 0 );
}
//=======================================================================================
void Serial::_check_speed( int spd )
{
    volatile auto res = tio_normal_speed_to_speedcode( spd );
    (void) res;
}
//=======================================================================================
void Serial::set_complex_options( int fd,
                                  Serial::Parity p,
                                  Serial::StopBits sb,
                                  Serial::FlowControl fc,
                                  int spd )
{
    termios tio;
    tio_get( fd, &tio );

    tio_set_common_props( &tio );
    tio_set_databits8   ( &tio );

    tio_set_parity      ( p,    &tio );
    tio_set_stopbits    ( sb,   &tio );
    tio_set_flowcontrol ( fc,   &tio );
    _tio_cfsetspeed     ( spd,  &tio );

    tio_set( fd, tio );
}
//=======================================================================================
//      TERMIOS
//=======================================================================================


//=======================================================================================
//static int tio_speedcode_normal_speed( speed_t speed_code )
//{
//    switch( speed_code )
//    {
//    case      B0: return      0;
//    case     B50: return     50;
//    case     B75: return     75;
//    case    B110: return    110;
//    case    B134: return    134;
//    case    B150: return    150;
//    case    B200: return    200;
//    case    B300: return    300;
//    case    B600: return    600;
//    case   B1200: return   1200;
//    case   B1800: return   1800;
//    case   B2400: return   2400;
//    case   B4800: return   4800;
//    case   B9600: return   9600;
//    case  B19200: return  19200;
//    case  B38400: return  38400;
//    case  B57600: return  57600;
//    case B115200: return 115200;
//    case B230400: return 230400;
//    case B460800: return 460800;
//    }
//    throw verror( "Bad speed code: ", speed_code );
//}
//=======================================================================================
