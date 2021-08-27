#ifndef SIMUDYN_DIAPROGRESS_H
#define SIMUDYN_DIAPROGRESS_H

#include"erroanalysis.h" //把动态画图窗口包含进来
#include <QCloseEvent> //重写窗口关闭事件
#include <QDialog>
#include <QString>

namespace Ui {
class SimuDyn_DiaProgress;
}

class SimuDyn_DiaProgress : public QDialog
{
    Q_OBJECT

public:
    explicit SimuDyn_DiaProgress(QWidget *parent = nullptr);
    ~SimuDyn_DiaProgress();
    //正常接收数据槽函数
    void dealerrodata(int numbers,int curretnumbers,double erro);
    //结束槽函数
    void dealallisover();
    //异常槽函数
    void dealnotwork();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SimuDyn_DiaProgress *ui;
    ErroAnalysis erroanalysis;    
    //设置一个标志符号，配合destroy判断函数结束时进行清楚图像用
    int m_flag;

signals:
    void diatoerro(int curretnumbers,double erro);
    void erroclearchart();

protected:
    void closeEvent(QCloseEvent *) override;
};

#endif // SIMUDYN_DIAPROGRESS_H
