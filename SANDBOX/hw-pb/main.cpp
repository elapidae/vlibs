#include <QApplication>
#include <QCheckBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCheckBox cb("Hello wordl!");
    cb.show();
    return a.exec();
}
