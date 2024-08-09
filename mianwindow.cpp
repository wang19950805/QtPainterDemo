#include "mianwindow.h"
#include "ui_mainwindow.h"

#include<QPainter>
#include<QDebug>
#include <QtMath>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startAngle = 150;
    startSpeed();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //初始化画布
    initCanvas(painter);

    //画圆
    drawMiddleCircle(painter,60);

    //画刻度
    drawScale(painter,height()/2);

    //画刻度文字
    drawScaleText(painter,height()/2);

    //画指针
    drawPointLine(painter,height()/2 - 58);

    //画扇形
    drawSpeedPie(painter,height()/2+25);

    //画内圈
    drawEllipseInnerBlack(painter,80);

    //显示数值
    drawCurrentSpeed(painter);

    //发光外圈
    drawEllipseOutterShine(painter,height()/2+25);
}



void MainWindow::initCanvas(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing,true);

    painter.setBrush(Qt::black);
    painter.drawRect(rect());

    QPoint cent(rect().width() /2 ,height() * 0.6);
    painter.translate(cent);

}

void MainWindow::startSpeed()
{
    timer = new QTimer(this);
    currentValue = 0;
    connect(timer,&QTimer::timeout,[=](){
        if(mark == 0){
            currentValue ++;
            if(currentValue >= 61){
                mark = 1;
            }
        }
        if(mark == 1){
            currentValue -- ;
            if(currentValue == 0){
                mark = 0;
            }
        }

        update();
    });
    timer->start(50);
}

void MainWindow::drawEllipseInnerBlack(QPainter &painter, int radius)
{
    QRadialGradient radialGradient(0,0,110);
    radialGradient.setColorAt(0.0,QColor(255,0,0,200));
    radialGradient.setColorAt(1.0,QColor(0,0,0,100));
    painter.setBrush(radialGradient);
    painter.drawEllipse(QPoint(0,0),110,110);

    painter.setBrush(Qt::black);
    painter.drawEllipse(QPoint(0,0),radius,radius);
}

void MainWindow::drawEllipseOutterShine(QPainter &painter, int radius)
{

    QRect rentangle(-radius ,-radius,radius*2,radius*2);
    painter.setPen(Qt::NoPen);

    QRadialGradient radialGradient(0,0,radius);
    radialGradient.setColorAt(1,QColor(255,0,0,200));
    radialGradient.setColorAt(0.97,QColor(255,0,0,120));
    radialGradient.setColorAt(0.9,QColor(0,0,0,0));
    radialGradient.setColorAt(0,QColor(0,0,0,0));
    painter.setBrush(radialGradient);

    painter.drawPie(rentangle,(360-150)*16,-angle*61*16);
}


void MainWindow::drawMiddleCircle(QPainter &painter,int radius)
{
    //画小圆
    painter.setPen(QPen(Qt::white,3));
    painter.drawEllipse(QPoint(0,0),radius,radius);

}

void MainWindow::drawCurrentSpeed(QPainter &painter)
{
    painter.setPen(Qt::white);
    QFont font("Arial",30);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QRect(-60,-60,120,70),Qt::AlignCenter,QString::number(currentValue*4));
    painter.drawText(QRect(-60,-60,120,160),Qt::AlignCenter,"Km/h");

}

void MainWindow::drawScale(QPainter &painter,int radius)
{
    angle = 240 * 1.0 / 60;
    painter.save();
    painter.setPen(QPen(Qt::white,5));
    painter.rotate(startAngle);
    for (int i = 0; i <= 60; ++i) {
        if(i >= 40){
            painter.setPen(QPen(Qt::red,5));
        }
        if(i % 5 == 0){

            painter.drawLine(radius-20,0,radius-3,0);
        }else{
            painter.drawLine(radius-8,0,radius-3,0);

        }
        painter.rotate(angle);

    }
    painter.restore();
}

void MainWindow::drawScaleText(QPainter &painter, int radius)
{
    painter.setFont(QFont("Arial",15));

    int r = radius - 49;
    for (int i = 0; i <= 60; ++i) {
        if(i%5 == 0){
            painter.save();
            int delX = qCos(qDegreesToRadians(210 - angle *i)) * r;
            int delY = qSin(qDegreesToRadians(210 - angle *i)) * r;
            painter.translate(QPoint(delX,-delY));
            //旋转坐标系
            painter.rotate(-120 + angle *i);
            painter.drawText(-25,-25,50,30,Qt::AlignCenter,QString::number(i*4));
            painter.restore();
        }

    }
}

void MainWindow::drawPointLine(QPainter &painter, int lenth)
{

    painter.save();

    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);

    static const QPointF points[4] = {
        QPointF(0,0.0),
        QPointF(200.0,-1.1),
        QPointF(200.0,1.1),
        QPointF(0,15.0)
    };

    painter.rotate(startAngle + angle * currentValue);
    painter.drawPolygon(points,4);
    painter.restore();
}

void MainWindow::drawSpeedPie(QPainter &painter, int radius)
{

    QRect rentangle(-radius ,-radius,radius*2,radius*2);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(235,152,50,150));
    painter.drawPie(rentangle,(360-startAngle)*16,-angle*currentValue*16);

}


