#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTableView *t1, *t2, *t3;

public slots:
    void simple_func();

signals:
    void sig();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
