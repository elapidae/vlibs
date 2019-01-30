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


#include "vserialport.h"

#include "verror.h"
#include "vpoll/vpoll.h"
#include "vposix_serial.h"
#include <assert.h>

#include "vlog_pretty.h"

//=======================================================================================
static auto constexpr Read_Buffer_Size = 1024;
//=======================================================================================


//=======================================================================================
static vposix::Serial::Parity
to_posix_parity( VSerialPort::Options::Parity p );

static vposix::Serial::StopBits
to_posix_stopbits( VSerialPort::Options::StopBits sb );

static vposix::Serial::FlowControl
to_posix_flowcontrol( VSerialPort::Options::FlowControl fc );
//=======================================================================================


//=======================================================================================
//      VSerialPort::Pimpl
//=======================================================================================
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
class VSerialPort::Pimpl : public VPoll::EventReceiver
{
public:
    Pimpl( VSerialPort *own );

    void set_options( const Options& opts );

    void open( const std::string& fname, const Options& opts );
    void close();

    bool is_opened() const;

    void event_received( VPoll::EventFlags flags ) override;

    void write( const std::string& buf );

    void flush();

private:
    VString read_all();
    void process_error( VPoll::EventFlags *flags );

    VSerialPort *owner = nullptr;
    FD_Polled fd;
    vposix::Serial::termios_ptr last_termios;
};
#pragma GCC diagnostic pop
//=======================================================================================
VSerialPort::Pimpl::Pimpl( VSerialPort* own )
    : owner( own )
{}
//=======================================================================================
void VSerialPort::Pimpl::set_options( const Options& opts )
{
    if ( !is_opened() ) return;

    auto p  = to_posix_parity       ( opts.parity       );
    auto sb = to_posix_stopbits     ( opts.stop_bits    );
    auto fc = to_posix_flowcontrol  ( opts.flow_control );

    vposix::Serial::set_complex_options( fd.raw(), p, sb, fc, opts.speed );
}
//=======================================================================================
template<class T>class TD;
void VSerialPort::Pimpl::open( const std::string& fname, const Options& opts )
{
    close();

    int new_fd = vposix::Serial::open( fname );
    vposix::Files::set_tio_EXCL( new_fd );
    auto last_opts = vposix::Serial::tio_save( new_fd );

    auto fclose = [last_opts]( int fd )
    {
        vposix::Serial::tio_soft_set( fd, *last_opts );
        vposix::Files::set_tio_soft_not_EXCL( fd );
        vposix::Files::close( fd );
    };

    fd = FD_Polled( new_fd, this, fclose );
    set_options( opts );
}
//=======================================================================================
void VSerialPort::Pimpl::close()
{
    if ( !is_opened() ) return;

    fd.close();
    owner->closed();
}
//=======================================================================================
bool VSerialPort::Pimpl::is_opened() const
{
    return fd.valid();
}
//=======================================================================================
void VSerialPort::Pimpl::event_received( VPoll::EventFlags flags )
{
    if ( flags.take_ERR() )
    {
        process_error( &flags );
        return;
    }

    if ( flags.take_IN() )
    {
        owner->received( read_all() );
    }
    assert( flags.empty() );
}
//=======================================================================================
void VSerialPort::Pimpl::process_error( VPoll::EventFlags *flags )
{
    if ( !flags->take_HangUp() )
    {
        throw verror.hex()( "Unexpected serial error: ", flags->raw() );
    }
    close();
}
//=======================================================================================
void VSerialPort::Pimpl::write( const std::string &buf )
{
    if ( !is_opened() )
        throw verror( "Write to closed serial port." );

    auto res = vposix::Files::write( fd.raw(), buf );
    assert( res == ssize_t(buf.size()) );
}
//=======================================================================================
void VSerialPort::Pimpl::flush()
{
    if ( !fd.valid() ) return;
    vposix::Serial::flush_io( fd.raw() );
}
//=======================================================================================
VString VSerialPort::Pimpl::read_all()
{
    char buf[ Read_Buffer_Size ];

    VString res;

    while(1)
    {
        auto has_read = vposix::Files::read( fd.raw(), buf, sizeof(buf) );
        res.append( buf, buf + has_read );

        if ( has_read < Read_Buffer_Size )
            break;
    }
    return res;
}
//=======================================================================================
//      VSerialPort::Pimpl
//=======================================================================================


//=======================================================================================
//      VSerialPort
//=======================================================================================
VSerialPort::VSerialPort( const VSerialPort::Options &opts )
    : p( new Pimpl(this) )
    , _options( opts )
{}
//=======================================================================================
VSerialPort::~VSerialPort()
{}
//=======================================================================================
void VSerialPort::set_speed( int spd )
{
    vposix::Serial::_check_speed( spd );
    _options.speed = spd;
    p->set_options( _options );
}
//=======================================================================================
void VSerialPort::set_parity( VSerialPort::Options::Parity par )
{
    _options.parity = par;
    p->set_options( _options );
}
//=======================================================================================
void VSerialPort::set_stop_bits( VSerialPort::Options::StopBits sb )
{
    _options.stop_bits = sb;
    p->set_options( _options );
}
//=======================================================================================
void VSerialPort::set_flow_control( VSerialPort::Options::FlowControl fc )
{
    _options.flow_control = fc;
    p->set_options( _options );
}
//=======================================================================================
void VSerialPort::set_options( const VSerialPort::Options& opts )
{
    vposix::Serial::_check_speed( opts.speed );
    _options = opts;
    p->set_options( _options );
}
//=======================================================================================
void VSerialPort::open( const std::string& fname )
{
    p->open( fname, _options );
    p->flush();
}
//=======================================================================================
void VSerialPort::close()
{
    p->close();
}
//=======================================================================================
void VSerialPort::flush()
{
    p->flush();
}
//=======================================================================================
void VSerialPort::write( const std::string &data )
{
    p->write( data );
}
//=======================================================================================
bool VSerialPort::is_opened() const
{
    return p->is_opened();
}
//=======================================================================================
//      VSerialPort
//=======================================================================================


//=======================================================================================
//      VSerialPort::Options
//=======================================================================================
VSerialPort::Options::Options()
{} // all by default
//=======================================================================================
//      VSerialPort::Options -> vposix::Serial enums
//  Применяется, потому что все эти перечисления не перекрыть какими-то понятными
//  передачами. Приходится экранировать экранированное.
//=======================================================================================
static vposix::Serial::Parity to_posix_parity( VSerialPort::Options::Parity p )
{
    switch ( p )
    {
    case VSerialPort::Options::Parity::No:
        return vposix::Serial::Parity::No;

    case VSerialPort::Options::Parity::Odd:
        return vposix::Serial::Parity::Odd;

    case VSerialPort::Options::Parity::Even:
        return vposix::Serial::Parity::Even;
    }
    throw verror("Bad parity casting");
}
//=======================================================================================
static vposix::Serial::StopBits to_posix_stopbits( VSerialPort::Options::StopBits sb )
{
    switch ( sb )
    {
    case VSerialPort::Options::StopBits::One:
        return vposix::Serial::StopBits::One;

    case VSerialPort::Options::StopBits::Two:
        return vposix::Serial::StopBits::Two;

    case VSerialPort::Options::StopBits::OneAndHalf:
        return vposix::Serial::StopBits::OneAndHalf;
    }
    throw verror("Bad stop bits casting");
}
//=======================================================================================
static vposix::Serial::FlowControl
to_posix_flowcontrol( VSerialPort::Options::FlowControl fc )
{
    switch ( fc )
    {
    case VSerialPort::Options::FlowControl::No:
        return vposix::Serial::FlowControl::No;

    case VSerialPort::Options::FlowControl::Hardware:
        return vposix::Serial::FlowControl::Hardware;

    case VSerialPort::Options::FlowControl::Software:
        return vposix::Serial::FlowControl::Software;
    }
    throw verror("Bad flow control casting");
}
//=======================================================================================
//      VSerialPort::Options -> vposix::Serial enums
//=======================================================================================
//      VSerialPort::Options
//=======================================================================================

