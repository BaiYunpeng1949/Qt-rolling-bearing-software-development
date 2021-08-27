#ifndef SIMUDYNTHREAD_H
#define SIMUDYNTHREAD_H

#include <QObject>
#include "erroanalysis.h"
//方便与对话窗口互动
//#include"simudyn_diaprogress.h"
#include <QElapsedTimer>


class SimuDynThread : public QObject
{
    Q_OBJECT
public:
    explicit SimuDynThread(QObject *parent = nullptr);

    //建立一个接收来自主函数进行计算的数据槽函数，即线程处理主函数dyn
    void dyn(double E, double v, double rho, double alpha0, double D, double di, double fe, double fi, int Z, double Fr, double Fa, double M, double ni, double omiga, double omiga1, double omiga2, int OR,double erro,int numbers);


signals:
    //定义一个信号发送给dialogrogree进行进度显示，主窗口也会发一份
    //void sdthreadtodiagro(int curretnumbers,double erro); //这个用不上了
    //定义一个信号，把数据发给显示charts
    void sdthreadforerro(int curretnumbers,double erro,qint64 timegoesby);
    //定义一个信号把计算结果都传送回去，回到主窗口
    void sdthreadtomain(double Dthetat,double Ddeltaat,double Ddeltart,QVector<double> vecsdlamdat,QVector<double> vecsdalphaet,QVector<double> vecsdalphait,QVector<double> vecsdut,QVector<double> vecsdQet,QVector<double> vecsdQit,QVector<double> vecsdFct,QVector<double> vecsdMgt,QVector<double> vecsdwbt,QVector<double> vecsdwct,QVector<double> vecsdSRet,QVector<double> vecsdSRit ,double P0);
    //定义一个信号告诉大家都结束了
    void sdthreadisallover();
    //定义一个信号告诉大家超出最大迭代次数，不收敛
    void sdthreadnotwork();
    //中止线程信号
    void stopdynthread();

private:
    //SimuDyn_DiaProgress *simudyndia;
    ErroAnalysis erroanalysis;
    //时间替身
    qint64 m_timeelapsed;
    //设置判断线程是否被中止的标志位
    bool m_stop;
    //设置标志位判断是否超出计算范围
    bool m_eccess;
};

#endif // SIMUDYNTHREAD_H
