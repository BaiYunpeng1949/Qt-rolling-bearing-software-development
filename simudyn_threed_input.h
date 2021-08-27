#ifndef SIMUDYN_THREED_INPUT_H
#define SIMUDYN_THREED_INPUT_H

#include <QWidget>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QFileDialog>
#include <QTextCodec>
#include "math.h"
#include "setmessageboxsize.h"

namespace Ui {
class SimuDyn_ThreeD_Input;
}

class SimuDyn_ThreeD_Input : public QWidget
{
    Q_OBJECT

public:
    explicit SimuDyn_ThreeD_Input(QWidget *parent = nullptr);
    ~SimuDyn_ThreeD_Input();

    //定义一个设置阴影的函数
    void setShadows3D(QLineEdit *lineedit);
    //定义接收p0的槽函数
    void dealMainWindowToThreeDInput(double p0);
    //定义计算的函数
    void calculate(int M,int N,double XIN,double YIN,double XOUT,double YOUT);
    //定义一个保存计算压力结果的函数
    void saveasfile();

private slots:
    void on_pushButton_close_clicked();

    void on_pushButton_calculate_clicked();

    void on_pushButton_reset_clicked();

private:
    Ui::SimuDyn_ThreeD_Input *ui;
    //阴影效果
    QGraphicsDropShadowEffect *m_staeffect;
};

#endif // SIMUDYN_THREED_INPUT_H
