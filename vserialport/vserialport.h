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
