#include "mainwindow.h"
#include <QApplication>

#include "pathscanner.h"
#include <QDebug>

#include "reportform.h"
#include "sourceanalizer.h"
#include "vlog.h"

#include "colons.h"

int main(int argc, char *argv[])
{
//    colons();
//    return 0;

    QApplication a(argc, argv);
    MainWindow w( QString(argv[0]) + ".ini" );
    w.show();


    //w.scan_dir( "/home/el/trash/obu" );
    //w.scan_dir( "/home/el/trash/fl" );
    w.scan_dir( "/home/el/trash/zcm2ros" );

//    auto root = "../ProjectDriver";
//    auto entries  = PathScanner::scan( root );
//    auto sentries = PathScanner::clear_first_path( root, entries );

    return a.exec();
}
