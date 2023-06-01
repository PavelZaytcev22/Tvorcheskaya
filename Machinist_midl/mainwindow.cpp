#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flag=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    if (flag==0){
        vv=new secondwindow(this);
        vv->show();
        flag=1;
    }
    else{
        flag=0;
        vv->close();
    }
}

void MainWindow::on_pushButton_exit_clicked()
{
    close();
}

