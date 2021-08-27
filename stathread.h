#ifndef STATHREAD_H
#define STATHREAD_H

#include <QObject>
#include"sta_diaprogress.h"

class StaThread : public QObject
{
    Q_OBJECT
public:
    explicit StaThread(QObject *parent = nullptr);

    //sta线程处理函数_计算函数sta，其实是作为槽函数了
    //补充参数:double alpha0,dm,D,fi,fe,Fr,Fa,M; int z;
    void sta(int z,double D,double dm,double alpha0,double fi,double fe,double Fr,double Fa,double M);

private:
    Sta_DiaProgress stadiaprogress;

signals:
    //定义一个信号，用来返回所有计算完的值,返回给数据显示部分
    void stasendback(double deltar,double deltaa,double theta,QVector<double> vecsalpha,QVector<double> vecsq);
    //定义一个信号，负责通知主窗口sta计算完毕
    void staprogress();
};

#endif // STATHREAD_H
