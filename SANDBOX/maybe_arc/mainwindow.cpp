#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    t1 = ui->tableView;
    t2 = ui->tableView_2;
    t3 = ui->tableView_3;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::simple_func()
{
    std::cout << "HW!" << std::endl;
}
