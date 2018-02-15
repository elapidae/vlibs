#include "mainwindow.h"
#include <QApplication>

#include "vstring.h"
#include "vlogger.h"

#include <map>


using namespace  std;

int main(int argc, char *argv[])
{
    std::string sss("HW");

    VString ss(move(sss));

    vdeb(vlog(varg::nospace, ss.to_Hex(), "|", ss.front_BE<int16_t>()));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::string s;
    s.append( std::string("ololo") );

    return a.exec();
}
