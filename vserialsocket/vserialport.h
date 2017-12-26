#ifndef VSERIALPORT_H
#define VSERIALPORT_H

#include <string>
#include <memory>

#include "vbytearray.h"
#include "vserialportoptions.h"


//=======================================================================================
/*
 *      VSerialPort -- Класс-адаптер для _синхронного_ чтения последовательных портов.
 *
 *      Для асинхронного чтения используйте класс VSerialSocket.
 *
 *      Для настройки порта используется класс VSerialPortOptions, типичный
 *      сценарий работы с портом примерно такой:
 *
 *      void foo()
 *      {
 *          auto portname = "/dev/ttyS4";
 *          VSerialPortOptions options = VSerialPortOptions::get_options( portname );
 *          options.set_speed( 115200 );
 *          options.set_parity( VSerialPortOptions::ParityNone );
 *          ... // set other options
 *
 *          VSerialPort port;
 *          if ( !port.open(portname, options) )
 *          {
 *              ... // throw error
 *          }
 *          port.set_non_block_reading( false ); // false by default.
 *
 *          VByteArray buffer( 1024 );
 *          while (1)
 *          {
 *              int count = port.read( buffer.data(), buffer.size() );
 *              ... // use data
 *          }
 *      }
 */
//=======================================================================================





//=======================================================================================
//          SERIAL PORT
//=======================================================================================
class VSerialPort
{
public:
    VSerialPort();
    virtual ~VSerialPort();

    bool is_opened() const;

    bool open( const std::string &fname, const VSerialPortOptions &options );
    bool open( const std::string &fname );

    // Вызывать только на открытом порту.
    bool set_options( const VSerialPortOptions &options );
    VSerialPortOptions get_options() const;

    // По умолчанию открывается в блокирующем режиме.
    // Вызывать только на открытом порту.
    bool set_non_block_reading( bool non_block );

    void close();

    // Возвращает количество реально прочитанных данных, -1 в случае ошибки.
    int read( VByteArray::value_type *buffer, int max_count );

    VByteArray read_all( bool *ok = nullptr );

    bool send( const VByteArray &data );


private:    
    class Pimpl;
    std::unique_ptr<Pimpl> p;
};
//=======================================================================================
//          SERIAL PORT
//=======================================================================================



#endif // VSERIALPORT_H
