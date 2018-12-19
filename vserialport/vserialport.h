#ifndef VSERIALPORT_H
#define VSERIALPORT_H

#include <memory>

#include "vsignal.h"
#include "vstring.h"

//=======================================================================================
class VSerialPort final
{
public:
    //===================================================================================
    class Options
    {
    public:
        enum class Parity       { No, Odd, Even          };
        enum class StopBits     { One, OneAndHalf, Two   };
        enum class FlowControl  { No, Hardware, Software };

        int         speed        = 9600;
        Parity      parity       = Parity::No;
        StopBits    stop_bits    = StopBits::One;
        FlowControl flow_control = FlowControl::No;

        Options();
    };
    //===================================================================================

    VSignal<VString> received;
    VSignal<> closed;

    VSerialPort( const Options& opts = Options() );
    ~VSerialPort();

    void set_speed        ( int spd                 );
    void set_parity       ( Options::Parity par     );
    void set_stop_bits    ( Options::StopBits sb    );
    void set_flow_control ( Options::FlowControl fc );
    void set_options      ( const Options& opts     );

    void open( const std::string& fname );
    //bool try_open( const std::string& fname, std::string *errmsg );
    void close();

    void flush();

    void write( const std::string& data );

    bool is_opened() const;

private:
    class Pimpl; std::unique_ptr<Pimpl> p;
    Options _options;
};
//=======================================================================================


#endif // VSERIALPORT_H
