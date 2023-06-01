#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include <QLCDNumber>
#include <QLabel>
#include <QTimer>
#include <QTime>

namespace Ui {
class secondwindow;
}

class secondwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit secondwindow(QWidget *parent = nullptr);
    ~secondwindow();

private slots:

    void on_horizontalSlider_valueChanged(int value);

    void on_toolButton_1_clicked();

    void on_toolButton_2_clicked();

    void on_randomButton_clicked();

    void TimerSLOT();

    void on_startButton_clicked();

    void on_endButton_clicked();

    void on_spinBox_water_valueChanged(int arg1);

    void on_spinBox_pressure_valueChanged(int arg1);

    void on_spinBox_road_valueChanged(int arg1);

    void on_spinBox_temp_valueChanged(int arg1);

    void on_timeEdit_userTimeChanged(const QTime &time);

private:
    Ui::secondwindow *ui;
    int temperature;
    int peredach;
    int sec;
    int min;
    int hour;
    QTimer *timer;
    int road;
    int pressure;
    int water;
    int kof_water;
    int bak_woda;
    int bak_pressure;
    int bak_road;
};

#endif // SECONDWINDOW_H
