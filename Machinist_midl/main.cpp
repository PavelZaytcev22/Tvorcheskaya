#include "mainwindow.h"
#include "secondwindow.h"
#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QTimer::singleShot(500000000, &w, SLOT(close()));
    return a.exec();
}
