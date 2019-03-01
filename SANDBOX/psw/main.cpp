#include "mainwindow.h"
#include <QApplication>

#include <QCryptographicHash>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    auto res = QCryptographicHash::hash( "123456", QCryptographicHash::Sha1 );
    qDebug() << res.toHex().toUpper();

    return 0;
}
