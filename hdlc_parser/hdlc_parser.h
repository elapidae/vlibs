#ifndef HDLC_PARSER_H
#define HDLC_PARSER_H

#include "vstring.h"
#include "vsignal.h"

//=======================================================================================
//  Standard parser for HDLC protocol.
//  https://ru.wikipedia.org/wiki/HDLC
//=======================================================================================



//=======================================================================================
class HDLC_Parser
{
public:

    VSignal<VString> received;

    void append( const std::string& app_data );

    static void test();

private:
    VString _buffer;
    bool _packet_began = false; // Обозначает что нашли в последовательности первый 7E.
    bool _escaped = false;
};
//=======================================================================================


#endif // HDLC_PARSER_H
