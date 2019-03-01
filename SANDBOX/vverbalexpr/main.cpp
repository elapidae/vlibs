#include "mainwindow.h"
#include <QApplication>

#include "vlog_qt.h"
#include "vverbalexpr.h"
#include "vgit.h"

int main(int argc, char *argv[])
{
    vdeb << VGit::as_message(); return 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    auto downs = VVerbalExpr::latin_downs();

    std::string str = "abcdefghigjklmnopqrstuvwxyzA";
    auto b = str.cbegin();
    auto e = str.cend();

    while (1)
    {
        auto bb = downs.step(b, e);
        if (b == bb) break;
        b = bb;
    }
    vdeb << *b;

    return a.exec();
}
