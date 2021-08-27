#ifndef SIMUDYN_CHARTS_H
#define SIMUDYN_CHARTS_H

#include <QWidget>
#include <QPen>

//把画图需要的QtCharts组件加进来
#include<QtCharts>
#include<QtCharts/QSplineSeries>
#include<QLineSeries>
#include<QPieSeries>
#include<QValueAxis>
#include<QAbstractAxis>
QT_CHARTS_USE_NAMESPACE



namespace Ui {
class SimuDyn_Charts;
}

class SimuDyn_Charts : public QWidget
{
    Q_OBJECT

public:
    explicit SimuDyn_Charts(QWidget *parent = nullptr);
    ~SimuDyn_Charts();

    //定义一个槽函数，接收来自主窗口的数据进行画图
    void sddealcharts(int z, QVector<double> vecsdlamdat, QVector<double> vecsdalphaet, QVector<double> vecsdalphait, QVector<double> vecsdut, QVector<double> vecsdQet, QVector<double> vecsdQit, QVector<double> vecsdFct, QVector<double> vecsdMgt, QVector<double> vecsdwbt, QVector<double> vecsdwct, QVector<double> vecsdSRet, QVector<double> vecsdSRit);
    //定义一个计算图像上下限的函数
    double calculatemin(double min,double max);
    double calculatemax(double min,double max);
    //定义一个判断精确度的函数
    QString accuracy(double min,double max);
    //定义一个zoom函数
    void zoombeforescoll_simu_charts(QChart *m_charts);

protected:
    //鼠标轮滚动事件
    void wheelEvent(QWheelEvent *event) override;
    //鼠标位置事件
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    //void on_pushButton_8_clicked();

    void on_pushButton_u_clicked();

    void on_pushButton_alphai_clicked();

    void on_pushButton_alphae_clicked();

    void on_pushButton_lamda_clicked();

    void on_pushButton_qi_clicked();

    void on_pushButton_qe_clicked();

    void on_pushButton_Fc_clicked();

    void on_pushButton_M_clicked();

    void on_pushButton_wb_clicked();

    void on_pushButton_wc_clicked();

    void on_pushButton_SRi_clicked();

    void on_pushButton_SRe_clicked();

private:
    Ui::SimuDyn_Charts *ui;

    //Charts
    QChart *m_sdchartlamda ;
    QChart *m_sdchartalphae ;
    QChart *m_sdchartalphai ;
    QChart *m_sdchartqe ;
    QChart *m_sdchartqi ;
    QChart *m_sdchartwc ;
    QChart *m_sdchartwb ;
    QChart *m_sdchartSre ;
    QChart *m_sdchartSri ;
    QChart *m_sdchartFc ;
    QChart *m_sdchartMg ;
    QChart *m_sdchartu ;
    //鼠标位置变量
    QPoint m_lastpos;




signals:
    //设置一个信号来决定传回的是那种情况的图片
    //void charttomainpic(int situation);
};

#endif // SIMUDYN_CHARTS_H
