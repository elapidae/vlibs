#include "mainwindow.h"
#include <QApplication>

#include "vimagewidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    VImageWidget w;
    w.show();

    QImage img;
    auto ok = img.load("1.jpg", "JPEG");
    Q_ASSERT(ok);

    w.set_image(img);

    return a.exec();
}
