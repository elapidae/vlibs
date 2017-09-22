#ifndef VSERIALPORTOPTIONS_H
#define VSERIALPORTOPTIONS_H

#include <memory>
#include <string>
#include "vbytearray.h"
//#include "vserialport.h"
struct termios;

//=======================================================================================
// http://www.opennet.ru/docs/RUS/serial_guide/
//=======================================================================================




//=======================================================================================
class VSerialPortOptions final
{
public:
    //-----------------------------------------------------------------------------------
    VSerialPortOptions(); // default options
    VSerialPortOptions( const VSerialPortOptions& other );
    const VSerialPortOptions& operator = ( const VSerialPortOptions &other );
    ~VSerialPortOptions();

    //-----------------------------------------------------------------------------------
    enum ParityCheck  { ParityNone, ParityOdd, ParityEven          };
    enum StopBits     { OneStopBit, TwoStopBits                    };
    enum DataBits     { DataBits5, DataBits6, DataBits7, DataBits8 };

    //-----------------------------------------------------------------------------------
    static VSerialPortOptions get_options( const std::string & portname,
                                           bool *ok = nullptr );
    static VSerialPortOptions default_options();
    bool set_options( const std::string & portname ) const;

    //-----------------------------------------------------------------------------------
    void set_wait_time( unsigned char decisec );    // c_cc[VTIME] в десятых долях сек
    void set_min_packet_size( unsigned char mps );  // c_cc[VMIN]

    //-----------------------------------------------------------------------------------
    void unset_all_echos();                     // ECHO ECHOE ECHOK ECHONL ECHOCTL
                                                // ECHOPRT ECHOKE
    //-----------------------------------------------------------------------------------
    void set_speed( int spd );
    int speed() const;                          // return < 0 if in_speed != out_speed.

    //-----------------------------------------------------------------------------------
    void set_raw_input( bool ri );              // ICANON ECHO ECHOE ISIG [IO]CRNL

    //-----------------------------------------------------------------------------------
    void set_hardware_flow_control( bool fc );  // CRTSCTS
    bool hardware_flow_control() const;

    //-----------------------------------------------------------------------------------
    void set_software_flow_control( bool sc );  // IXON IXOFF IXANY

    //-----------------------------------------------------------------------------------
    void set_parity( ParityCheck pc );          // PARENB PARODD INPCK
    ParityCheck parity() const;                 // ISTRIP IGNPAR PARMRK

    void set_ignore_parity( bool ignpar );      // IGNPAR

    //-----------------------------------------------------------------------------------
    void set_stop_bits( StopBits sb );          // CSTOPB
    StopBits stop_bits() const;

    //-----------------------------------------------------------------------------------
    void set_data_bits( DataBits db );          // CS5 CS6 CS7 CS8
    DataBits data_bits() const;

    //-----------------------------------------------------------------------------------
    bool clocal() const;                        // CLOCAL   Должны быть
    bool cread()  const;                        // CREAD    разрешены.

    //-----------------------------------------------------------------------------------
    VByteArray save() const;
    static VSerialPortOptions restore( const VByteArray& saved );

    //-----------------------------------------------------------------------------------
private:
    VSerialPortOptions( const termios& trm );

    class Pimpl;
    std::unique_ptr<Pimpl> p;

    friend class VSerialPort;
    bool _set_options( int handle ) const;
    static VSerialPortOptions _get_options(int handle);
};
//=======================================================================================



#endif // VSERIALPORTOPTIONS_H
