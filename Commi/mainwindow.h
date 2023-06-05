#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QVector>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Hide();
    void Show();
    void Perebor(int,int);

private slots:

    void on_maketableButton_clicked();

    void on_buildButton_clicked();

    void on_roadButton_clicked();

private:
    Ui::MainWindow *ui;
    int matrix[10][10];//Матрица смежности
    QString solution;
    QPainter paint;
    virtual void paintEvent(QPaintEvent *)  ;
};
#endif // MAINWINDOW_H
