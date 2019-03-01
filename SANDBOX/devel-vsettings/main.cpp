#include "mainwindow.h"
#include <QApplication>

#include "vcat_containers.h"
#include "vlog.h"
#include "vsettings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    VSettings setts( R"(
    # test comment
                     kv0   = 321;\t\t
                     [   hello world! 				 ]
                     h.a1.a2.a3 = 123
                     w1.w2.w3.w4 = 09876
                     #      ololoool comment
                          [1]
                     [ olool ]
                     #   hhhhhhhh comm
                     w1.w2.w3.w4 = 09876 \
                     dddddddddddddd \
                     eeeeeee
                     )");

    vdeb << setts.cur_groups();
    for ( auto &g: setts.cur_groups() )
    {
        setts.enter_group( g );
        vdeb << setts.cur_groups();
        setts.leave_group();
    }
    vdeb << setts.view();

    return a.exec();
}
