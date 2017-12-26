#include "vserialportoptions.h"

#include <termios.h>
#include <fcntl.h>
#include <assert.h>
#include <stdexcept>
#include <strings.h>
#include <unistd.h>

#include "vlogger.h"


using namespace std;


//=======================================================================================
//  Считано с перезагруженной системы.
static const auto def_options =
VByteArray::from_hex( "0005000005000000bd0c00003b8a000000031c7f150400010011131a0"
                      "0120f1716000000000000000000000000000000000d0000000d000000" );
//=======================================================================================
static termios _restore( VByteArray saved );
//=======================================================================================


//=======================================================================================
static int to_normal_speed( speed_t speed_code )
{
    switch( speed_code )
    {
    case      B0: return      0;
    case     B50: return     50;
    case     B75: return     75;
    case    B110: return    110;
    case    B134: return    134;
    case    B150: return    150;
    case    B200: return    200;
    case    B300: return    300;
    case    B600: return    600;
    case   B1200: return   1200;
    case   B1800: return   1800;
    case   B2400: return   2400;
    case   B4800: return   4800;
    case   B9600: return   9600;
    case  B19200: return  19200;
    case  B38400: return  38400;
    case  B57600: return  57600;
    case B115200: return 115200;
    case B230400: return 230400;
    case B460800: return 460800;
    }
    return -1;
}
//=======================================================================================
static speed_t normal_speed_to_code( int speed )
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
    return -1;
}
//=======================================================================================


//=======================================================================================
class VSerialPortOptions::Pimpl
{
public:
    Pimpl()
    {
        static const auto def_trm = _restore( def_options );
        trm = def_trm;
    }
    termios trm;
};
//=======================================================================================
VSerialPortOptions::VSerialPortOptions()
    : p( new Pimpl )
{}
//=======================================================================================
VSerialPortOptions::VSerialPortOptions( const VSerialPortOptions &other )
    : p( new Pimpl(*other.p) )
{}
//=======================================================================================
VSerialPortOptions::VSerialPortOptions( const termios &trm )
    : VSerialPortOptions()
{
    p->trm = trm;
}
//=======================================================================================
const VSerialPortOptions &VSerialPortOptions::operator =(const VSerialPortOptions &other)
{
    *p = *other.p;
    return *this;
}
//=======================================================================================
VSerialPortOptions::~VSerialPortOptions()
{}
//=======================================================================================
bool VSerialPortOptions::set_options( const string &portname ) const
{
    auto handle = ::open( portname.c_str(), O_RDWR );

    if (handle < 0)
        return false;

    auto res = _set_options( handle );
    ::close( handle );
    return res;
}
//=======================================================================================
VSerialPortOptions VSerialPortOptions::default_options()
{
    return _restore(def_options);
}
//=======================================================================================
// static
VSerialPortOptions VSerialPortOptions::get_options( const string &portname, bool *ok_ )
{
    bool lok;
    bool &ok = ok_ ? *ok_ : lok;
    ok = false;

    auto handle = ::open( portname.c_str(), O_RDONLY );
    if (handle < 0)
    {
        vdeb( vlog(errno));
        return {};
    }

    ok = true;
    auto res = _get_options( handle );
    ::close( handle );
    return res;
}
//=======================================================================================
// static
VSerialPortOptions VSerialPortOptions::_get_options( int handle )
{
    struct termios trm_com;
    auto res = tcgetattr( handle, &trm_com );

    if ( res != 0 )
        throw std::runtime_error( "Error during get attr for port" );

    return trm_com;
}
//=======================================================================================
bool VSerialPortOptions::_set_options( int handle ) const
{
    int setted = tcsetattr( handle, TCSAFLUSH, &p->trm );
    return setted == 0;
}
//=======================================================================================
void VSerialPortOptions::set_wait_time(unsigned char decisec)
{
    p->trm.c_cc[VTIME] = decisec;
}
//=======================================================================================
void VSerialPortOptions::set_min_packet_size(unsigned char mps)
{
    p->trm.c_cc[VMIN] = mps;
}
//=======================================================================================
void VSerialPortOptions::unset_all_echos()
{
    p->trm.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ECHOCTL | ECHOPRT | ECHOKE);
}
//=======================================================================================
int VSerialPortOptions::speed() const
{
    auto ospd = cfgetospeed( &p->trm );
    auto ispd = cfgetispeed( &p->trm );

    if ( ospd != ispd ) return -1;
    return to_normal_speed( ospd );
}
//=======================================================================================
void VSerialPortOptions::set_speed( int spd )
{
    cfsetspeed( &p->trm, normal_speed_to_code(spd) );
}
//=======================================================================================
void VSerialPortOptions::set_raw_input( bool ri )
{
    if (ri) p->trm.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    else    p->trm.c_lflag |=  (ICANON | ECHO | ECHOE | ISIG);

    if (ri) p->trm.c_oflag &= ~OPOST;
    else    p->trm.c_oflag |=  OPOST;

    if (ri) p->trm.c_oflag &= ~OCRNL;
    if (ri) p->trm.c_iflag &= ~ICRNL;
}
//=======================================================================================
void VSerialPortOptions::set_hardware_flow_control(bool fc)
{
    if (fc) p->trm.c_cflag |=  CRTSCTS;
    else    p->trm.c_cflag &= ~CRTSCTS;
}
//=======================================================================================
bool VSerialPortOptions::hardware_flow_control() const
{
    return p->trm.c_cflag & CRTSCTS;
}
//=======================================================================================
void VSerialPortOptions::set_software_flow_control(bool sc)
{
    if (sc) p->trm.c_iflag |=  (IXON | IXOFF | IXANY);
    else    p->trm.c_iflag &= ~(IXON | IXOFF | IXANY);
}
//=======================================================================================
void VSerialPortOptions::set_parity( ParityCheck pc )
{
    p->trm.c_cflag &= ~(PARENB | PARODD);
    p->trm.c_iflag &= ~(INPCK  | ISTRIP);
    p->trm.c_iflag &= ~(IGNPAR | PARMRK);

    if ( pc == ParityEven ) p->trm.c_cflag |= PARENB;
    if ( pc == ParityOdd  ) p->trm.c_cflag |= (PARENB | PARODD);

    // В мане написано, что ставить надо, а на практике с этим не работает...
    //if ( pc != ParityNone ) p->trm.c_iflag |= (INPCK | ISTRIP);
}
//=======================================================================================
VSerialPortOptions::ParityCheck VSerialPortOptions::parity() const
{
    bool enb = p->trm.c_cflag & PARENB;
    bool odd = p->trm.c_cflag & PARODD;

    if ( enb && odd ) return ParityOdd;
    if ( enb ) return ParityEven;

    return ParityNone;
}
//=======================================================================================
void VSerialPortOptions::set_ignore_parity(bool ignpar)
{
    if (ignpar) p->trm.c_iflag |=  IGNPAR;
    else        p->trm.c_iflag &= ~IGNPAR;
}
//=======================================================================================
void VSerialPortOptions::set_stop_bits( VSerialPortOptions::StopBits sb )
{
    if ( sb == TwoStopBits ) p->trm.c_cflag |=  CSTOPB;
    else                     p->trm.c_cflag &= ~CSTOPB;
}
//=======================================================================================
VSerialPortOptions::StopBits VSerialPortOptions::stop_bits() const
{
    return p->trm.c_cflag & CSTOPB
                    ? TwoStopBits
                    : OneStopBit;
}
//=======================================================================================
void VSerialPortOptions::set_data_bits( VSerialPortOptions::DataBits db )
{
    p->trm.c_cflag &= ~CSIZE;
    switch(db)
    {
    case DataBits5: p->trm.c_cflag |= CS5; break;
    case DataBits6: p->trm.c_cflag |= CS6; break;
    case DataBits7: p->trm.c_cflag |= CS7; break;
    case DataBits8: p->trm.c_cflag |= CS8; break;
    default: assert(false);
    }
}
//=======================================================================================
VSerialPortOptions::DataBits VSerialPortOptions::data_bits() const
{
    auto mask = p->trm.c_cflag & CS8;
    if (mask == CS8) return DataBits8;
    if (mask == CS7) return DataBits7;
    if (mask == CS6) return DataBits6;
    return DataBits5;
}
//=======================================================================================
bool VSerialPortOptions::clocal() const
{
    return p->trm.c_cflag & CLOCAL;
}
//=======================================================================================
bool VSerialPortOptions::cread() const
{
    return p->trm.c_cflag & CREAD;
}
//=======================================================================================


//=======================================================================================
//  NB! Если структура изменится, будет больно.
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
//---------------------------------------------------------------------------------------
static termios _restore( VByteArray saved )
{
    termios trm;

    if (saved.empty())
        saved = def_options;

    trm.c_iflag = saved.pop_front_little<decltype(trm.c_iflag)>();
    trm.c_oflag = saved.pop_front_little<decltype(trm.c_oflag)>();
    trm.c_cflag = saved.pop_front_little<decltype(trm.c_cflag)>();
    trm.c_lflag = saved.pop_front_little<decltype(trm.c_lflag)>();

    trm.c_line = saved.pop_front_little<decltype(trm.c_line)>();

    for (int i = 0; i < NCCS; ++i)
        trm.c_cc[i] = saved.pop_front_little< cc_t >();

    trm.c_ispeed = saved.pop_front_little<decltype(trm.c_ispeed)>();
    trm.c_ospeed = saved.pop_front_little<decltype(trm.c_ospeed)>();

    return trm;
}
//=======================================================================================
VByteArray VSerialPortOptions::save() const
{
    VByteArray res;

    auto & trm = p->trm;
    res.push_back_little(trm.c_iflag);
    res.push_back_little(trm.c_oflag);
    res.push_back_little(trm.c_cflag);
    res.push_back_little(trm.c_lflag);

    res.push_back_little(trm.c_line);

    for (int i = 0; i < NCCS; ++i)
        res.push_back_little(trm.c_cc[i]);

    res.push_back_little(trm.c_ispeed);
    res.push_back_little(trm.c_ospeed);

    return res;
}
//=======================================================================================
// static
VSerialPortOptions VSerialPortOptions::restore( const VByteArray &saved )
{
    return _restore( saved );
}
//=======================================================================================
