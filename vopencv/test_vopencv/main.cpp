#include "mainwindow.h"
#include <QApplication>

#include "vcv_image.h"
#include "vlog_pretty.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    auto def_proj = vcv::Image::Projection::default_project_1(-10, 10, 3, 103);
    def_proj.v_deb();

    return a.exec();
}
