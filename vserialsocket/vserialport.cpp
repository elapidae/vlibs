#include "vserialport.h"

#include <assert.h>

#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>
#include <type_traits>
#include <termios.h>
#include <array>

//#include "vlogger.h"

using namespace std;

// При чтении из порта в readAll() применяется как размер буффера на один запрос.
//static constexpr auto one_buffer_size = 4096;
static constexpr auto one_buffer_size = 200;    // Опытным путем...



//=======================================================================================
//static speed_t to_speed_t( VSerialPort::Speed t )
//{
//    switch (t)
//    {
//    case   VSerialPort::Speed::S9600:   return   B9600;
//    case  VSerialPort::Speed::S19200:   return  B19200;
//    case VSerialPort::Speed::S115200:   return B115200;
//    case VSerialPort::Speed::S230400:   return B230400;

//    default:
//        assert( false && "Port speed is undefined! Let write need speed..." );
//        exit(10);
//    }
//}
//=======================================================================================
//static tcflag_t databits_mask(VSerialPort::DataBits db)
//{

//    switch(db)
//    {
//    case VSerialPort::DataBits::Data5: return CS5;
//    case VSerialPort::DataBits::Data6: return CS6;
//    case VSerialPort::DataBits::Data7: return CS7;
//    case VSerialPort::DataBits::Data8: return CS8;

//    default:
//        assert( false && "Data bits mask is undefined!" );
//        exit(11);
//    }
//}
//=======================================================================================
//static tcflag_t stopbits_mask(VSerialPort::StopBits s)
//{
//    switch(s)
//    {
//    case VSerialPort::StopBits::OneStop: return 0;
//    case VSerialPort::StopBits::TwoStop: return CSTOPB;

//    case VSerialPort::StopBits::OneAndHalfStop:
//        assert( false && "I don't know how to set OneAndHalfStop bits mask!" );

//    default:
//        assert( false && "Stop bits mask is undefined!" );
//        exit(12);
//    }
//}
//=======================================================================================
//static tcflag_t parity_mask(VSerialPort::ParityCheck pc)
//{
//    switch(pc)
//    {
//    case VSerialPort::ParityCheck::None: return 0;
//    case VSerialPort::ParityCheck::Odd:  return PARENB | PARODD;
//    case VSerialPort::ParityCheck::Even: return PARENB;

//    default:
//        assert( false && "ParityCheck bits mask is undefined!" );
//        exit(13);
//    }
//}
//=======================================================================================




//=======================================================================================
class VSerialPort::Pimpl
{
public:
    int handle = 0;
    VSerialPortOptions saved_options;
};
//=======================================================================================
VSerialPort::VSerialPort()
    : p( new Pimpl )
{}
//=======================================================================================
VSerialPort::~VSerialPort()
{
    close();
}
//=======================================================================================
bool VSerialPort::is_opened() const
{
    return p->handle > 0;
}
//=======================================================================================
bool VSerialPort::open( const string &fname, const VSerialPortOptions &options )
{
    return open(fname)
                ? set_options(options)
                : false;
}
//=======================================================================================
bool VSerialPort::open(const string &fname)
{
    if ( is_opened() )
        return false;

    p->handle = ::open( fname.c_str(), O_RDWR | O_NOCTTY, O_EXCL );

    if ( p->handle < 0 )
        return false;

    p->saved_options = VSerialPortOptions::_get_options( p->handle );

    return true;
}
//=======================================================================================
bool VSerialPort::set_options( const VSerialPortOptions &options )
{
    if ( !is_opened() ) return false;
    return options._set_options( p->handle );
}
//=======================================================================================
VSerialPortOptions VSerialPort::get_options() const
{
    return VSerialPortOptions::_get_options( p->handle );
}
//=======================================================================================
bool VSerialPort::set_non_block_reading( bool non_block )
{
    if ( !is_opened() ) return false;

    int flag = non_block ? FNDELAY : 0;
    return 0 == fcntl( p->handle, F_SETFL, flag );
}
//=======================================================================================
void VSerialPort::close()
{
    if ( p->handle > 0 )
    {
        p->saved_options._set_options( p->handle );
        ::close( p->handle );
    }

    p->handle = 0;
}
//=======================================================================================
int VSerialPort::read( VByteArray::value_type *buffer, int max_count )
{
    assert( buffer && max_count >= 0 );

    if ( !is_opened() )
        return -1;

    return ::read( p->handle, buffer, max_count );
}
//=======================================================================================
//  Читаем в буффер до тех пор, пока данные не кончатся.
VByteArray VSerialPort::read_all( bool *ok_ )
{
    bool lok;
    bool &ok = ok_ ? *ok_ : lok;
    ok = true;

    VByteArray res;
    array<VByteArray::value_type, one_buffer_size> buf;

    //VByteArray buf( one_buffer_size );
    while(1)
    {
        auto count = read( buf.data(), one_buffer_size );

        if ( count > 0 )
            res.append( buf.data(), buf.data() + count );

        if ( count < 0 )
            ok = false;

        if ( count < int(one_buffer_size) )
            break;
    }
    return res;
}
//=======================================================================================
bool VSerialPort::send( const VByteArray &data )
{
    //vdeb( vlog(data) );
    //vdeb( vlog(data.to_hex()) );

    if ( !is_opened() )
        return false;

    auto w = ::write( p->handle, data.data(), data.size() );
    return w == int(data.size());
}
//=======================================================================================
