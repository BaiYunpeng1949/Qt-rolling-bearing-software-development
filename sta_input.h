#ifndef STA_INPUT_H
#define STA_INPUT_H

#include <QWidget>
#include <QTimer>
#include <QLineEdit>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QFileDialog>
#include <QTextStream>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QBrush>
#include <QTextCodec>
#include <QVariant>
#include <QAxObject>
#include <ActiveQt/QAxObject>
#include <QString>
#include <QStringList>
#include <QVariantList>
#include <stdio.h>
#define ROWNUMBERS 11

//数据库头文件
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>

//QTableWidget头文件
#include <QTableWidget>
#include <QTableWidgetItem>



namespace Ui {
class Sta_Input;
}

class Sta_Input : public QWidget
{
    Q_OBJECT

public:
    explicit Sta_Input(QWidget *parent = nullptr);
    ~Sta_Input();
    //定义一个设置阴影的函数
    void setShadowsd(QLineEdit *lineedit);



private:
    Ui::Sta_Input *ui;
    QTimer *m_statimer;
    QTimer *m_timer4index;
    //阴影效果
    QGraphicsDropShadowEffect *m_sdeffect;
    //TableView 模块设置
    QStandardItemModel *m_model_sta_1;
    //读取文件的地址
    QString m_inputopenfile_name;
    //保存文件的地址
    QString m_inputsavefile_name;
    //添加数据库
    QSqlDatabase m_db_sta_1;
    QSqlQuery m_query_sta_1;
    //QString
    QString m_linestring;
    //QStringList
    QStringList m_list_items;
    //定义几个数据，方便保存的时候调用
    QString  m_sta_Fr,m_sta_Fa,m_sta_M,m_sta_dm,m_sta_D,m_sta_alpha0,m_sta_fe,m_sta_fi,m_sta_z;

signals:
    void stainput(int z,double D,double dm,double alpha0,double fi,double fe,double Fr,double Fa,double M);

private slots:
    void on_pBstayes_clicked();
    //void on_pBstacancel_clicked();
    void on_pBstaclear_clicked();

    void on_pushButtonopenfile_clicked();
    void on_pushBottonsaveas_clicked();
    void on_pushBottonconfig_clicked();
};

#endif // STA_INPUT_H
