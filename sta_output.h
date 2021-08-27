#ifndef STA_OUTPUT_H
#define STA_OUTPUT_H

#include <QWidget>

//写文件，保存文件之用
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QProcess>
#include <QSettings>
#include <QTextCodec>

#include <QString>
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <math.h>



namespace Ui {
class Sta_Output;
}

class Sta_Output : public QWidget
{
    Q_OBJECT

public:
    explicit Sta_Output(QWidget *parent = nullptr);
    ~Sta_Output();
    //建立一个接受来自主窗口信号的槽函数
    void stadealoutput(double D,double dm,double alpha0,double fi,double fe,double Fr,double Fa,double M,double staoutputdeltaa,double staoutputdeltat,double staoutputtheta,int z,QVector<double> vecsalpha,QVector<double> vecsq);

private slots:
    void on_pushButtonstaoutput_clicked();

    //void on_pushButton_clicked();

private:
    Ui::Sta_Output *ui;
};

#endif // STA_OUTPUT_H
