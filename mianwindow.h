#ifndef MIANWINDOW_H
#define MIANWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


protected:
    void paintEvent(QPaintEvent *event) override;

private:

    void initCanvas(QPainter &painter);
    void drawMiddleCircle(QPainter &painter,int radius);
    void drawCurrentSpeed(QPainter &painter);
    void drawScale(QPainter &painter,int radius);
    void drawScaleText(QPainter &painter,int radius);
    void drawPointLine(QPainter &painter,int lenth);
    void drawSpeedPie(QPainter &painter,int radius);
    void startSpeed();
    void drawEllipseInnerBlack(QPainter &painter,int radius);
    void drawEllipseOutterShine(QPainter &painter,int radius);


    Ui::MainWindow *ui;
    QTimer *timer;
    int currentValue;
    int mark = 0;
    double angle;
    int startAngle;
};
#endif // MIANWINDOW_H
