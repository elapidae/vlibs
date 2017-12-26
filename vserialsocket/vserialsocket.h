#ifndef VSERIALSOCKET_H
#define VSERIALSOCKET_H

#include <memory>

#include "vsignal.h"
#include "vbytearray.h"
#include "vserialport.h"

//=======================================================================================
//      В экспериментальной стадии. Обкатывается его возможности, удобство,
//  принципиальная устойчивость.
//=======================================================================================



class VSerialSocket
{
public:
    // Переменная используется для установки времени ожидания данных с порта, измеряется
    // в десятых долях секунды, по умолчанию = 10. Если за указанный период данных
    // не придет, будет подан сигнал no_data.
    static unsigned char read_delay_decisec;

    enum class Error
    {
        Send_Failure,
        Unknown
    };

    //VSignal<>           no_data; // Подается, если в течение секунды не было данных.
    VSignal<VByteArray> received;


    VSerialSocket();
    virtual ~VSerialSocket();

    // NB! в настройках меняет время ожидания!
    bool open( const std::string &fname, VSerialPortOptions options );
    bool open( const std::string &fname );
    bool is_opened() const;

    bool set_options( VSerialPortOptions options );
    VSerialPortOptions get_options() const;

    void close();

    bool send( const VByteArray &data );

private:
    void _correct_options( VSerialPortOptions *opt );

    class Pimpl;
    //Pimpl *p;
    std::unique_ptr<Pimpl> p;    
};

#endif // VSERIALSOCKET_H
