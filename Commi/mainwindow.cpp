#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QLabel>
#define N 10
double grad=360;
int r,ris=0,prirost,xcenter,ycenter,mins=10000,leng,s;
struct Node{
    int x,y;
};
bool *was;
int *way, *minway;
Node *node;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    solution="";
    //Ограничение доступа к кнопкам
     ui->buildButton->setEnabled(0);
      ui->roadButton->setEnabled(0);
      //Задание маски блоков ввода
      ui->vvodvertex->setInputMask("9");
      ui->p12->setInputMask("99");
      ui->p13->setInputMask("99");
      ui->p14->setInputMask("99");
      ui->p15->setInputMask("99");
      ui->p16->setInputMask("99");
      ui->p17->setInputMask("99");
      ui->p18->setInputMask("99");
      ui->p19->setInputMask("99");
      ui->p23->setInputMask("99");
      ui->p24->setInputMask("99");
      ui->p25->setInputMask("99");
      ui->p26->setInputMask("99");
      ui->p27->setInputMask("99");
      ui->p28->setInputMask("99");
      ui->p29->setInputMask("99");
      ui->p34->setInputMask("99");
      ui->p35->setInputMask("99");
      ui->p36->setInputMask("99");
      ui->p37->setInputMask("99");
      ui->p37->setInputMask("99");
      ui->p38->setInputMask("99");
      ui->p39->setInputMask("99");
      ui->p45->setInputMask("99");
      ui->p46->setInputMask("99");
      ui->p47->setInputMask("99");
      ui->p48->setInputMask("99");
      ui->p49->setInputMask("99");
      ui->p56->setInputMask("99");
      ui->p57->setInputMask("99");
      ui->p58->setInputMask("99");
      ui->p59->setInputMask("99");
      ui->p67->setInputMask("99");
      ui->p68->setInputMask("99");
      ui->p69->setInputMask("99");
      ui->p78->setInputMask("99");
      ui->p79->setInputMask("99");
      ui->p89->setInputMask("99");
      Hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Функция скрытия матрицы смежности с основного виджета
void MainWindow::Hide(){
  QString pol;//Строковая переменная нужная для считывание значений с нужных виджетов
  for (int i=1;i<10;i++){
         pol="gor" + QString::number(i);
         this->findChild<QWidget*>(pol)->hide();
     }
  for (int i=1; i<10; i++){
      pol="vert"+QString::number(i);
      this->findChild<QWidget*>(pol)->hide();
      pol="dig"+QString::number(i);
      this->findChild<QWidget*>(pol)->hide();
      for(int e=i+1;e<10;e++ ){
          pol="p"+QString::number(i)+QString::number(e);
          this->findChild<QWidget*>(pol)->hide();
      }
      for(int e=1;e<i;e++){
          pol="n"+QString::number(i)+QString::number(e);
          this->findChild<QWidget*>(pol)->hide();
      }
  }
}

//Функция вывода матрицы смежности на основной виджет
void MainWindow::Show(){
    QString pol; //Строковая переменная нужная для считывание значений с нужных виджетов
    for (int i=1;i<r+1;i++){
           pol="gor" + QString::number(i);
           this->findChild<QWidget*>(pol)->show();
       }
    for (int i=1; i<r+1; i++){
        pol="vert"+QString::number(i);
        this->findChild<QWidget*>(pol)->show();
        pol="dig"+QString::number(i);
        this->findChild<QWidget*>(pol)->show();
        for(int e=i+1;e<r+1;e++ ){
            pol="p"+QString::number(i)+QString::number(e);
            this->findChild<QWidget*>(pol)->show();
        }
        for(int e=1;e<i;e++){
            pol="n"+QString::number(i)+QString::number(e);
            this->findChild<QWidget*>(pol)->show();
        }
    }
}

//Функция отрисовки событий
void MainWindow::paintEvent(QPaintEvent *)
{
    if (ris){
    int otstup;
    grad/=r;
    prirost=grad;
    grad=0;
   //Объявление холста с карандашом
    QPainter paint;
    QPen pen;
    QBrush brush;
    QString stroka;
    QFont font;
    pen.setColor(Qt::black);
    pen.setWidth(4);
    pen.setStyle(Qt::SolidLine);
    font.setPointSize(20);
    paint.begin(this);
    paint.setPen(pen);
    paint.setFont(font);
    for (int i=0;i<r;i++){
        otstup=-10;
        //Отрисока кругов(вершин графа)
        if (grad>180) otstup=100;
        stroka=QString::number(i+1);
        node[i].x=xcenter+(150*cos(grad/57));
        node[i].y=ycenter+(150*-sin(grad/57));
        paint.drawEllipse(node[i].x,node[i].y,50,50);
        paint.drawText(node[i].x+25,node[i].y+otstup,stroka);
        grad+=prirost;
    }
    if (ris>1){
        //Отрисока линий(ребер графа)
        for (int i=0;i<r;i++){
            for (int e=i+1;e<r;e++){
                if (matrix[i][e]){
                    pen.setStyle(Qt::SolidLine);
                    pen.setWidth(3);
                    paint.setPen(pen);
                    paint.drawLine(node[i].x+25,node[i].y+25,node[e].x+25,node[e].y+25);
                }
            }
        }
    }
    paint.end();
    }
}

//Слот вывода матрицы на основной виджет
void MainWindow::on_maketableButton_clicked()
{
    if (ui->vvodvertex->text().toInt()<3||ui->vvodvertex->text().toInt()>9){
        ui->vvodvertex->setText("");
        Hide();
        ris=0;
        this->repaint();
        QMessageBox::warning(this,"Ошибка","Количество вершин должно быть не менее 3 и не более 9! ");
    }
    else{
        Hide();
        ui->buildButton->show();
        r=ui->vvodvertex->text().toInt();
        Show();
        node = new Node[r];
        xcenter=650;
        ycenter=300;
        ris=1;
        this->repaint();
        ui->buildButton->setEnabled(1);
    }
}

//Слот считывания матрицы с основного виджета
void MainWindow::on_buildButton_clicked()
{
    QString searcher,buffer;
    for (int i=1;i<r;i++){
        for (int e=i+1;e<r+1;e++){
            searcher="p"+QString::number(i) + QString::number(e);
            buffer=this->findChild <QLineEdit*> (searcher)->text();
            if (!buffer.length()) buffer='0';
            searcher="n"+QString::number(e) + QString::number(i);
            this->findChild<QLabel*>(searcher)->setText(buffer);
        }
    }
    for (int i=0;i<r-1;i++){
        for (int e=i+1;e<r;e++){
            searcher="n"+QString::number(e+1) + QString::number(i+1);
            buffer=this->findChild<QLabel*>(searcher)->text();
            if (!buffer.length()) buffer='0';
           matrix[i][e]=buffer.toInt();
           matrix[e][i]=matrix[i][e];
        }
    }
    ui->roadButton->setEnabled(1);
    ris=2;
    this->repaint();
}

//Слот вычисления кратчайшего пути
void MainWindow::on_roadButton_clicked(){
    QString searcher,buffer;
        leng=0;
        s=0;
        mins=10000;
        was = new bool [r];
        way = new int [r];
        minway = new int [r];
        for (int i=0;i<r;i++) Perebor(0,i);
        buffer="Кратчайший путь: " + QString::number(minway[0]+1);
        for (int i=1;i<r;i++) buffer += "->" + QString::number(minway[i]+1);
        if (mins==10000){
            QMessageBox::warning(this,"Предупреждение","Не существует маршрута, позволяющего посетить все города, или невозможно посетить их без повторного посещения пройденных дорог и городов. ");
        }
        else{
        buffer+= "\n Длина пути: " +QString::number(mins);
        QMessageBox::information(this,"Результат",buffer);
        }
        delete[] was;
        delete[] way;
        ui->roadButton->setEnabled(0);
}

//Вычисление маршрута перебором
void MainWindow::Perebor(int l, int i){
    leng+=l;
    was[i]=1;
    bool b=0;
    way[s]=i;
    s++;
    for (int e=0;e<r;e++){
        if (!was[e]){
            if (matrix[i][e]) Perebor(matrix[i][e],e);
            b=1;
        }
    }
    if(!b){
        if (leng<mins){
            mins=leng;
            for (int z=0;z<r;z++) minway[z]=way[z];
        }
    }
    leng-=l;
    s--;
    was[i]=0;
}







