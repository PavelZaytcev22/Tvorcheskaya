#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QLabel>
#include <QTimer>
#include <QMessageBox>


secondwindow::secondwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::secondwindow)
{
    ui->setupUi(this);
    temperature=0;
    peredach=0;
    //Временные переменные и таймер
    sec=0;
    min=0;
    hour=0;
    road=0;
    water=0;
    bak_woda=0;
    bak_road=0;
    kof_water=0;
    pressure=0;
    bak_pressure=0;
    //Подключение таймера
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT( TimerSLOT()));
    //ПЕРЕМЕЩЕНИЕ МАРКЕРА
    ui->marker->setGeometry(0,20,25,30);
    //настройка цветов progressbar-ов
    ui->progressBar->setOrientation(Qt::Vertical);
    ui->progressBar->setStyleSheet("*{background-color: blue; border: 1px solid black; }");
    ui->progressBar->setStyleSheet("*{color: rgb(255, 255, 0); background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(100,0,0,255), stop: 1 rgba(200,0,0,255)); border: 2px solid grey; border-radius: 5px;}");
    ui->progressBar->setStyleSheet("*::chunk {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(0,200,255,255), stop: 1 rgba(0,0,255,255));}");
    ui->progressBar_2->setOrientation(Qt::Vertical);
    ui->progressBar_2->setStyleSheet("*{background-color: red; border: 1px solid black; }");
    ui->progressBar_2->setStyleSheet("*{color: rgb(255, 0, 0); background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(194, 14, 14, 1), stop: 1 rgba(194, 14, 14, 1)); border: 2px solid grey; border-radius: 5px;}");
    ui->progressBar_2->setStyleSheet("*::chunk {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(194, 14, 14, 1), stop: 1 rgba(0,0,150,150));}");
    ui->progressBar_3->setStyleSheet("*{background-color: black; border: 1px solid black; }");
    ui->progressBar_3->setStyleSheet("*{color: rgb(148, 135, 135); background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(79, 79, 79, 1), stop: 1 rgba(79, 79, 79, 1)); border: 2px solid grey; border-radius: 5px;}");
    ui->progressBar_3->setStyleSheet("*::chunk {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(79, 79, 79, 1), stop: 1 rgba(0,0,0,0));}");
    ui->progressBar_3->setTextVisible(false);
    ui->endButton->setEnabled(0);
}

secondwindow::~secondwindow()
{
    delete ui;
}

void secondwindow::on_horizontalSlider_valueChanged(int value)
{
    temperature=value;
    ui->tempview->display(value);
}


//повышение передач
void secondwindow::on_toolButton_1_clicked()
{
    if (peredach<4){
        peredach+=1;
        ui->label_peredach->setText('('+QString::number(peredach)+')');
    }
}

//понижение передач
void secondwindow::on_toolButton_2_clicked()
{
    if(peredach>0){
        peredach-=1;
        ui->label_peredach->setText('('+QString::number(peredach)+')');
    }
}

void secondwindow::on_randomButton_clicked()
{
    sec=rand() % 60;
    min=rand() % 60;
    hour=rand() % 23;
    ui->timeEdit->setTime(QTime(hour,min,sec,0));
    ui->spinBox_road->setValue(rand()%100000);
    ui->spinBox_water->setValue(rand()%1000);
    ui->spinBox_pressure->setValue(rand()%1450);
}


void secondwindow::TimerSLOT(){
        sec++;
        if(sec>=60){
            min++;
            sec-=60;
        }
        if (min>=60){
            hour++;
            min-=60;
        }
        if(hour==24&&min==60&& sec==60){
            sec=0;
            min=0;
            hour=0;
        }

  //Отображение времени
ui->timeEdit->setTime(QTime(hour,min,sec,0));

//Заполнение бака c водой
if (peredach==0){
    if(bak_woda<water){
        if (water<600){
            bak_woda+=10;
        }
        else {
           bak_woda+=25;
        }
    }
    else{
        bak_woda=water;
    }
    ui->progressBar->setValue((bak_woda*1000)/water);
}
//Заполнение котла с паром
kof_water=temperature/100;
if (bak_woda>0){
    if(bak_pressure<pressure){
      bak_pressure+=kof_water;
      bak_woda-=kof_water;
    }
    else{
        bak_pressure=pressure;
    }
}

if (bak_pressure==pressure){
    bak_pressure-=10;
    QMessageBox::warning(this, "Осторожно","Давление слишком большое");
    temperature=0;
    ui->tempview->display(temperature);
}
//Отображение давления
ui->progressBar_2->setValue((bak_pressure*1000)/pressure);
ui->progressBar->setValue((bak_woda*1000)/water);

//Работа с передачами и паром
switch (peredach) {
case 1:
    if (bak_pressure>=2)
    {
       bak_pressure-=2; bak_road+=5;
    }
    break;
case 2:
    if (bak_pressure>=6){
        bak_pressure-=6; bak_road+=15;
    }
    break;
case 3: if(bak_pressure>=10){
    bak_pressure-=10; bak_road+=20;
    }
     break;
case 4:
    if(bak_pressure>=14) {
     bak_pressure-=14; bak_road+=30;
    }
    break;
}
ui->progressBar->setValue((bak_woda*1000)/water);
ui->progressBar_3->setValue((bak_road*100000)/road);
ui->marker->setGeometry(((bak_road*1000)/road),20,25,30);
ui->label_road->setText(QString::number(bak_road)+' '+':');
 if (bak_road>=road){
    QMessageBox::information(this,"Конец","Вы доехали в В от точки А");
    timer->stop();
    close();
 }
}


void secondwindow::on_startButton_clicked()
{
    if (road<=0&&water<=0&&pressure<=0){
QMessageBox::warning(this, "Ошибка","Некоторые поля остались не заполненными");
    }
    else{
        timer->start(1000);
        ui->randomButton->setEnabled(0);
        ui->spinBox_road->setEnabled(0);
        ui->spinBox_water->setEnabled(0);
        ui->spinBox_pressure ->setEnabled(0);
        ui->startButton->setEnabled(0);
        ui->endButton->setEnabled(1);
    }
}


void secondwindow::on_endButton_clicked()
{
    timer->stop();
    ui->endButton->setEnabled(0);
    ui->startButton->setEnabled(1);
}


void secondwindow::on_spinBox_water_valueChanged(int arg1)
{
    water=arg1;
}

void secondwindow::on_spinBox_pressure_valueChanged(int arg1)
{
    pressure=arg1;
}


void secondwindow::on_spinBox_road_valueChanged(int arg1)
{
    road=arg1;
}


void secondwindow::on_spinBox_temp_valueChanged(int arg1)
{
    temperature= arg1;
    ui->tempview->display(temperature);
}


void secondwindow::on_timeEdit_userTimeChanged(const QTime &time)
{
    hour=time.hour();
    min=time.minute();
    sec=time.second();
}

