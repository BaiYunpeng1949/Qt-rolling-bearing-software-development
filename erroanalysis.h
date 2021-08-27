#ifndef ERROANALYSIS_H
#define ERROANALYSIS_H

#include <QWidget>
#include <QCloseEvent> //重写窗口关闭事件
#include <QMessageBox>
#include <QStatusBar> //状态栏
#include <QLabel>
#include <QElapsedTimer>
#include <QTimer>
#include <QTime>

#include "setmessageboxsize.h"

//把画图需要的QtCharts组件加进来
#include<QPen>
#include<QBrush>
#include<QtCharts>
#include<QtCharts/QSplineSeries>
#include<QLineSeries>
#include<QPieSeries>
#include<QValueAxis>
#include<QAbstractAxis>
QT_CHARTS_USE_NAMESPACE


namespace Ui {
class ErroAnalysis;
}

class ErroAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit ErroAnalysis(QWidget *parent = nullptr);
    ~ErroAnalysis();

    //接收数据的槽函数
    void dealthreadtoerro(int currentnumbers,double erro,qint64 timegoesby);
    //接收处理清楚图像的信号
    void dealerroclearchart();
    //定义槽函数完工提示
    void threadisover();
    //定义槽函数报错
    void threadinterruptted();

private:
    Ui::ErroAnalysis *ui;

    //定义一个曲线成员变量方便后面刷新调用
    QSplineSeries *m_erroline;
    QValueAxis *m_erroaxisx;
    QValueAxis *m_erroaxisy;
    QChart *m_errochart;

    //定义成员变量曲线数组
    QVector<QPointF> m_pts;
    //定义一个判断标志位，判断线程是否结束
    int m_flag;
    //计时器
    QElapsedTimer *m_timer;
    //玩具
    int m_count;
    //时间
    double m_time;

protected:
    void closeEvent(QCloseEvent *) override;

private slots:
    void on_pushButtonclose_clicked();
    void on_pushButtonstop_clicked();

signals:
    void stopthread();
};

#endif // ERROANALYSIS_H
