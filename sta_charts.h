#ifndef STA_CHARTS_H
#define STA_CHARTS_H

#include <QWidget>
#include <QFileDialog>
#include <QList>
#include <QWheelEvent>
#include <QMouseEvent>

//把画图需要的QtCharts组件加进来
#include <QPen>
#include<QFont>
#include<QtCharts>
#include<QtCharts/QSplineSeries>
#include<QLineSeries>
#include<QPieSeries>
#include<QValueAxis>
#include<QAbstractAxis>
QT_CHARTS_USE_NAMESPACE


namespace Ui {
class Sta_Charts;
}

class Sta_Charts : public QWidget
{
    Q_OBJECT

public:
    explicit Sta_Charts(QWidget *parent = nullptr);
    ~Sta_Charts();

    //定义一个槽函数，传递参数来生成charts
    void stadealcharts(int z,QVector<double> vecsalpha,QVector<double> vecsq);

    //定义一个计算图像上下限的函数
    double calculatemin(double min,double max);
    double calculatemax(double min,double max);
    //定义一个判断精确度的函数
    QString accuracy(double min,double max);
    //定义一个zoom初始化的函数
    void zoombeforescroll_sta_charts(QChart *m_charts);

protected:
    //鼠标轮滚动事件
    void wheelEvent(QWheelEvent *event) override;
    //鼠标位置事件
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;


private slots:
    void on_pushButtonstaalpha_clicked();

    void on_pushButtonstaq_clicked();

    //void on_pushButton_clicked();

    void on_pushButtonreset_clicked();

    void on_pushButton_clicked();

private:
    Ui::Sta_Charts *ui;

    //图像变量
    QChart *m_stachart1;
    QChart *m_stachart2;

    //鼠标位置变量
    QPoint m_lastpos;

signals:
    //定义一个信号，发送通知哪个图片被保存了
    //void stacahrttomainpic(int situation);

};

#endif // STA_CHARTS_H
