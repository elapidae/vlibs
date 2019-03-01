#include "mainwindow.h"
#include <QApplication>

#include "qcustomplot.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include "hdlc_parser.h"
#include "vlog_qt.h"
#include <QDebug>


//=======================================================================================
//termios VSerialPortOptions::_get_options( int handle )
//{
//    struct termios trm_com;
//    auto res = tcgetattr( handle, &trm_com );

//    if ( res != 0 )
//        throw std::runtime_error( "Error during get attr for port" );

//    return trm_com;
//}
////=======================================================================================
//bool VSerialPortOptions::_set_options( int handle ) const
//{
//    int setted = tcsetattr( handle, TCSAFLUSH, &p->trm );
//    return setted == 0;
//}
//=======================================================================================




//=======================================================================================
struct KinematicData
{
    uint32_t u_ts;

    double acc_x;
    double acc_y;
    double acc_z;

    double magn_x;
    double magn_y;
    double magn_z;

    bool has_gyro = false;
    double gyro_x = NAN;
    double gyro_y = NAN;
    double gyro_z = NAN;
};
//=======================================================================================
static KinematicData parse( const VString& str, bool *ok )
{
    *ok = false;
    KinematicData res {};

    if ( str.size() != 26 && str.size() != 32)
    {
        vwarning << "Omitted by len" << str.size() << ": " << str.to_hex('_');
        return res;
    }
    auto view = str.forward_view();

    auto msg_id = view.take_u16_LE();
    if ( msg_id != 0x40 )
    {
        return res;
    }

    auto type = view.take_u16_LE();
    if ( type != 0x0117 &&
         type != 0x011d )
    {
        return res;
    }


    res.u_ts = view.take_u32_LE();

    res.acc_x = view.take_i16_LE() * 0.000244;
    res.acc_y = view.take_i16_LE() * 0.000244;
    res.acc_z = view.take_i16_LE() * 0.000244;

    res.magn_x = view.take_i16_LE();
    res.magn_y = view.take_i16_LE();
    res.magn_z = view.take_i16_LE();


    res.has_gyro = false;

    if (type == 0x011d)
    {
        res.has_gyro = true;
        res.gyro_x = view.take_i16_LE() * 0.0078125;
        res.gyro_y = view.take_i16_LE() * 0.0078125;
        res.gyro_z = view.take_i16_LE() * 0.0078125;
    }
    *ok = true;
    return res;
}
//=======================================================================================


//=======================================================================================
//=======================================================================================


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCustomPlot w;
    w.show();
    w.resize(800, 800);

    QSerialPortInfo port_info;
    auto ports = QSerialPortInfo::availablePorts();
    for (auto p: ports)
    {
        vdeb << p.portName() << p.manufacturer() << p.vendorIdentifier();
        if (p.manufacturer() == "MBED" && p.vendorIdentifier() == 3368)
        {
            port_info = p;
            break;
        }
    }

    QSerialPort port( port_info );
    bool ok = port.open( QIODevice::ReadWrite );
    Q_ASSERT(ok);
    port.setBaudRate( 230400 );
    auto msg = QByteArray::fromHex("7E 21 00 00 02 01 01 7E");
    port.write( msg );

    auto graph = w.addGraph();
    double x = 0;

    HDLC_Parser parser;
    parser.received.connect( [&](const VString& str)
    {
        vdeb << str.to_hex();
        auto accd = parse( str, &ok );
        if ( !ok ) return;
        graph->addData( x +=1, accd.magn_x );
        graph->data()->remove( x - 100 );
        w.rescaleAxes();
        w.replot();
        //Parse message & put into graph
    });


    QObject::connect( &port, &QSerialPort::readyRead, [&]()
    {
        auto data = port.readAll();
        //vdeb << data.toHex('_');
        parser.append( data.toStdString() );
    });

    return a.exec();
}
