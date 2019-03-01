#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QFileInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString ini_path, QWidget *parent = nullptr);
    ~MainWindow();

    static bool omit_it   ( const QFileInfo& fi );
    static bool is_source ( const QFileInfo& fi );
    static bool is_build   ( const QFileInfo& fi );

    void scan_dir( const QString& dname );

private slots:
    void on_open_folder_btn_clicked();

private:
    Ui::MainWindow *ui;
    QSettings settings;
};

#endif // MAINWINDOW_H
