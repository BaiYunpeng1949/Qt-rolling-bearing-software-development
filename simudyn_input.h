#ifndef SIMUDYN_INPUT_H
#define SIMUDYN_INPUT_H

#include <QWidget>
#include <QTimer>
#include <QString>
#include <QGraphicsDropShadowEffect> //设置阴影实验
#include <QLineEdit>
#include <QDebug>

#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QBrush>
#include <QTextCodec>
#include <QVariant>
#include <QAxObject>
#include <ActiveQt/QAxObject>
#include <QStringList>
#include <QVariantList>
#include <stdio.h>
#define ROWNUMBERS_SIMUDYN 29

//QTableWidget头文件
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QComboBox>

namespace Ui {
class SimuDyn_Input;
}

class SimuDyn_Input : public QWidget
{
    Q_OBJECT

public:
    explicit SimuDyn_Input(QWidget *parent = nullptr);
    ~SimuDyn_Input();

    //定义一个设置阴影的函数
    void setShadowsta(QLineEdit *lineedit);

private:
    Ui::SimuDyn_Input *ui;
    QTimer *m_sdtimer;
    //阴影效果
    QGraphicsDropShadowEffect *m_staeffect;
    //全局OR使用
    int OR = 0;
    QString m_inputopenfile_name2;
    QString m_inputsavefile_name2;
    QString m_linestring2;
    QStringList m_list_items2;
    QString m_sd_Fr,m_sd_Fa,m_sd_M,m_sd_ni,m_sd_dm,m_sd_D,m_sd_rho,m_sd_omiga,m_sd_omiga1,m_sd_omiga2;
    QString m_sd_OR,m_sd_erro,m_sd_erronumber,m_sd_z,m_sd_alpha0,m_sd_fi,m_sd_fe,m_sd_v,m_sd_E;

signals:
    void sdinput(double E, double v, double rho, double alpha0, double D, double di, double fe, double fi, int Z, double Fr, double Fa, double M, double ni, double omiga, double omiga1, double omiga2, int OR,double erro,int numbers);
private slots:
    void on_pBsdyes_clicked();
    void on_pBsdclear_clicked();
    //void on_pBsdcancel_clicked();
    void on_comboBox_activated(QString index);
    void on_pushButtonsdopenfile_clicked();
    void on_pushButtonsdsaveas_clicked();
    void on_pushButtonsdconfig_clicked();
};

#endif // SIMUDYN_INPUT_H
