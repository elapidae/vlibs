#ifndef VPARSER_INTERFACE_H
#define VPARSER_INTERFACE_H

#include "vbytearray.h"
//#include "vsignal.h"

//=======================================================================================
// Никаких сигнальных систем об ошибках, а также никакого вывода результатов в интерфейсе
// не предусмотрено. Они касаются реализаций.
// Также не предусматривается никаких внутренних состояний объекта парсера:
// подразумевается, что как только сообщение оказалось в буфере, оно вырезается целиком.
class VParser_Interface
{
public:
    virtual ~VParser_Interface();

    //  Парсер отвечает подходит ли ему сообщение.
    virtual bool is_mine( const VByteArray &buf ) const = 0;

    //  Парсер отвечает подходит ли ему начало сообщения.
    virtual bool maybe_mine( const VByteArray &buf ) const = 0;

    //  Если сообщение целиком в начале буфера, оно вырезается, метод возвращает true,
    //  если с буфером никаких манипуляций не производилось, метод возвращает false.
    virtual bool cut( VByteArray *buf ) const = 0;

    class Rotator;
};
//=======================================================================================


//=======================================================================================
class VParser_Interface::Rotator
{
public:
    //VSignal<char> undefined_symbol;

    void parse( const VByteArray &data );

    void append( VParser_Interface *parser );

private:
    bool _parse_one();
    VByteArray _buffer;
    std::vector<VParser_Interface*> _parsers;
};
//=======================================================================================



#endif // VPARSER_INTERFACE_H
