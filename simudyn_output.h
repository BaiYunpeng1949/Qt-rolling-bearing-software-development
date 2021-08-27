#ifndef SIMUDYN_OUTPUT_H
#define SIMUDYN_OUTPUT_H

#include <QWidget>
#include <QProcess>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QTextCodec>

namespace Ui {
class SimuDyn_Output;
}

class SimuDyn_Output : public QWidget
{
    Q_OBJECT

public:
    explicit SimuDyn_Output(QWidget *parent = nullptr);
    ~SimuDyn_Output();

    //接收来自主窗口的槽函数
    void sddealoutput(double E, double v, double rho, double alpha0, double D, double di, double fe, double fi, double Fr, double Fa, double M, double ni, double omiga, double omiga1, double omiga2, int OR, double erro, int numbers,int z,double Dthetat, double Ddeltaat, double Ddeltart, QVector<double> vecsdlamdat, QVector<double> vecsdalphaet, QVector<double> vecsdalphait, QVector<double> vecsdut, QVector<double> vecsdQet, QVector<double> vecsdQit, QVector<double> vecsdFct, QVector<double> vecsdMgt, QVector<double> vecsdwbt, QVector<double> vecsdwct, QVector<double> vecsdSRet, QVector<double> vecsdSRit);

private slots:
    void on_pushButtonsdoutput_clicked();

    //void on_pushButton_clicked();

private:
    Ui::SimuDyn_Output *ui;
};

#endif // SIMUDYN_OUTPUT_H
