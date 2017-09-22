#include "vserialsocket.h"

#include <atomic>

#include "vthread.h"
#include "vserialport.h"

#include "vslot.h"
#include "unistd.h"

#include "vlogger.h"

using namespace std;





//=======================================================================================
class VSerialSocket::Pimpl
{
    VSerialSocket *owner;

public:
    Pimpl( VSerialSocket *owner_ )
        : owner( owner_ )
        , slot_received( &owner_->received )
        , thread("serial socket")
    {}

    VSlot<VByteArray> slot_received;

    VThread     thread;
    VSerialPort port;

    atomic_bool let_stop;

    void listen();
};
//=======================================================================================
unsigned char VSerialSocket::read_delay_decisec = 10;
//=======================================================================================
VSerialSocket::VSerialSocket()
    : p( new Pimpl(this) )
{}
//=======================================================================================
VSerialSocket::~VSerialSocket()
{
    //vdeb(vlog("~VSerialSocket()"));
    p->let_stop = true;
}
//=======================================================================================
bool VSerialSocket::open( const string &fname, VSerialPortOptions options )
{
    bool ok = open( fname );

    return ok ? set_options(options) : ok;
}
//=======================================================================================
bool VSerialSocket::open( const string &fname )
{
    p->let_stop = false;

    bool ok = p->port.open( fname );    
    if (!ok) return false;
    p->port.set_non_block_reading( false );

    p->thread.cinvoke( p.get(), &Pimpl::listen );

    return ok;
}
//=======================================================================================
bool VSerialSocket::is_opened() const
{
    return p->port.is_opened();
}
//=======================================================================================
bool VSerialSocket::set_options( VSerialPortOptions options )
{
    _correct_options( &options );
    return p->port.set_options( options );
}
//=======================================================================================
VSerialPortOptions VSerialSocket::get_options() const
{
    return p->port.get_options();
}
//=======================================================================================
void VSerialSocket::close()
{
    p->let_stop = true;
    p.get()->port.close();
}
//=======================================================================================
bool VSerialSocket::send( const VByteArray &data )
{
    return p->port.send( data );
}
//=======================================================================================
void VSerialSocket::_correct_options( VSerialPortOptions *opt )
{
    opt->set_min_packet_size( 1 );
    opt->set_wait_time( read_delay_decisec );
}
//=======================================================================================
void VSerialSocket::Pimpl::listen()
{
    bool ok = true;
    while ( !let_stop && ok )
    {
        VByteArray data = port.read_all( &ok );

        if ( ok && data.empty() )
        {
            //owner->no_data.call();
            continue;
        }

        //vdeb(vlog(data));

        if ( ok )
        {
            slot_received( data );  // Здесь происходит спуск в поток,
                                    // в котором был создан сокет.
        }

        if ( !ok && !let_stop )
        {
            throw runtime_error( "Error during listen serial port" );
        }
        //usleep( 25000 );
    } // reading the port
}
//=======================================================================================
