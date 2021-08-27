#ifndef DYN_INPUT_H
#define DYN_INPUT_H

#include <QWidget>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>
#include <QTimer>
#include <QString>
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
#define ROWNUMBERS_DYN 35

//QTableWidget头文件
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QComboBox>

namespace Ui {
class Dyn_Input;
}

class Dyn_Input : public QWidget
{
    Q_OBJECT

public:
    explicit Dyn_Input(QWidget *parent = nullptr);
    ~Dyn_Input();

    //定义一个设置阴影的函数
    void setShadowdyn(QLineEdit *lineedit);

private slots:
    void on_pushButton_apply_clicked();

    void on_pushButton_reset_clicked();

    void on_comboBox_dyn_activated(const QString &arg1);

    void on_pushButtondynopenfile_clicked();

    void on_pushButtondynsaveas_clicked();

    void on_pushButtondynconfig_clicked();

private:
    Ui::Dyn_Input *ui;
    //阴影效果
    QGraphicsDropShadowEffect *m_sdeffect;
    QString m_inputopenfile_name3;
    QString m_inputsavefile_name3;
    QString m_linestring3;
    QStringList m_list_items3;
    QString m_dyn_Fr,m_dyn_Fa,m_dyn_My,m_dyn_Mz,m_dyn_ni,m_dyn_dm,m_dyn_D,m_dyn_rho,m_dyn_rhoc,m_dyn_T,m_dyn_Cp,m_dyn_Cg;
    QString m_dyn_OR,m_dyn_T0,m_dyn_alpha,m_dyn_beta,m_dyn_z,m_dyn_alpha0,m_dyn_fi,m_dyn_fe,m_dyn_v,m_dyn_E,m_dyn_vc,m_dyn_Ec;
    QString m_dyn_K,m_dyn_n0,m_dyn_h0,m_dyn_kt,m_dyn_Ferr,m_dyn_Uerr;


signals:
    void dyninput(int z_dyn,
                  double D_dyn,double dm_dyn,double alpha0_dyn,double fi_dyn,double fe_dyn,double Cp_dyn,double Cg_dyn,
                  double E_dyn,double v_dyn,double rho_dyn,double Ec_dyn,double vc_dyn,double rhoc_dyn,
                  double ni_dyn,double Fa_dyn,double Fr_dyn,double My_dyn,double Mz_dy,double OR_dyn,
                  double T0_dyn,double n0_dyn,double alpha_dyn,double beta_dyn,double K_dyn,
                  double h0_dyn,double kt_dyn,double Ferr_dyn,double uerr_dyn,double T_dyn);

};

#endif // DYN_INPUT_H
