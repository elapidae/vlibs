#include <iostream>
#include <cstdlib>


#include "mainwindow.h"
#include <QApplication>

#include "qtserialport/src/serialport/qserialport.h"
#include "vlog_qt.h"

//#include "vcompiler.h"
//#include "vposix_core.h"

#include "vserialport.h"
#include "vapplication.h"


static auto constexpr ser_name = "/dev/ttyUSB0";
//static auto constexpr ser_name = "/dev/ttyUSB0";


int main(int argc, char *argv[])
{
    VApplication app;
    VSerialPort vport;

    vport.received.connect( []( const VString& data)
    {
        vdeb << data;
        vdeb << data.to_hex();
    });
    vport.closed.connect( [&]()
    {
        vdeb << "port closed";
        try {
            vport.open( ser_name );
        } catch ( const std::exception& e ) {
            vfatal << e.what();
        }

    });

    vport.open( ser_name );
    vport.set_speed( 115200 );
    vport.write("root fff");

    app.poll();
    return 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QSerialPort port; //( "/dev/ttyACM0" );
    vdeb << port.isOpen();
    QSerialPort port2( "/dev/ttyACM0" );
    vdeb << port2.isOpen();
    //Q_ASSERT( ok );

    return a.exec();
}
