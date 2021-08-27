#ifndef RBEVALUATION_H
#define RBEVALUATION_H

#include <QMainWindow>

//包含所需要的库
#include <QThread>
#include <QVector>
#include <QPushButton>
#include <QSpacerItem>

//把各个子窗口都包含进来
#include "sta_input.h"
#include "simudyn_input.h"
#include "sta_charts.h"
#include "simudyn_charts.h"
#include "sta_output.h"
#include "simudyn_output.h"
#include "indiaopengl.h"
#include "cloudtest.h"
#include "setmessageboxsize.h" //使用自定义messagebox
#include "dyn_input.h"
#include "welcome_byp.h"
#include "simudyn_threed_input.h"

//把线程文件包含进来
#include "stathread.h"
#include "simudynthread.h"


//把画图需要的QtCharts组件加进来
#include <QPen>
#include <QBrush>
#include <QtCharts>
#include <QtCharts/QSplineSeries>
#include <QLineSeries>
#include <QPieSeries>
#include <QValueAxis>
#include <QAbstractAxis>
QT_CHARTS_USE_NAMESPACE

//打开文档需要的头文件
#include <QProcess>
#include <QFileDialog>
#include <QString>
#include <QAxWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class RBEvaluation; }
QT_END_NAMESPACE

class RBEvaluation : public QMainWindow
{
    Q_OBJECT

public:
    RBEvaluation(QWidget *parent = nullptr);
    ~RBEvaluation();

    ////Sta部分
    //定义一个槽函数接收处理sta读取完成后的数据
    void stadealinput(int sz,double sD,double sdm,double salpha0,double sfi,double sfe,double sFr,double sFa,double sM);
    //定义一个接收信号的槽函数，一会儿发送走进行结果显示
    void stadealresult(double deltar,double deltaa,double theta,QVector<double> vecsalpha,QVector<double> vecsq);

    ////SD部分
    //定义一个槽函数接收处理读取完成后的数据
    void sddealinput(double E, double v, double rho, double alpha0, double D, double di, double fe, double fi, int Z, double Fr, double Fa, double M, double ni, double omiga, double omiga1, double omiga2, int OR,double erro,int numbers);
    //定义一个接收信号的槽函数，一会儿发送走进行结果显示
    void sddealresult(double Dthetat,double Ddeltaat,double Ddeltart,QVector<double> vecsdlamdat,QVector<double> vecsdalphaet,QVector<double> vecsdalphait,QVector<double> vecsdut,QVector<double> vecsdQet,QVector<double> vecsdQit,QVector<double> vecsdFct,QVector<double> vecsdMgt,QVector<double> vecsdwbt,QVector<double> vecsdwct,QVector<double> vecsdSRet,QVector<double> vecsdSRit ,double P0);
    //定义一个槽函数负责实时接收thread的erro数据进行主窗口画图
    //void sddealerro(int curretnumbers,double erro);

    ////Dyn部分
    //定义一个槽函数接收处理读取完成后的数据
    void dyndealinput(int zdyn,
                      double Ddyn,double dmdyn,double alpha0dyn,double fidyn,double fedyn,double Cpdyn,double Cgdyn,
                      double Edyn,double vdyn,double rhodyn,double Ecdyn,double vcdyn,double rhocdyn,
                      double nidyn,double Fadyn,double Frdyn,double Mydyn,double Mzdy,double ORdyn,
                      double T0dyn,double n0dyn,double alphadyn,double betadyn,double Kdyn,
                      double h0dyn,double ktdyn,double Ferrdyn,double uerrdyn,double Tdyn);


    ////公共部分
    //定义一个槽函数，接收欢迎界面的信号
    void dealWelcometoMain(int mode_rb);
    //定义一个槽函数，在关闭窗口的时候 也终止线程
    void dealdestroyed();
    //建立一个槽函数负责画表头
    void creattablewidgetheaders(QString title,double data,QString unit);
    //建立一个关闭tab的槽函数
    void TabClose(int index);





private slots:
    void on_actionstainput_triggered();

    void on_actionsdinput_triggered();

    void on_actionstachart_triggered();

    void on_actionsdchart_triggered();

    void on_actionstaoutput_triggered();

    void on_actionsdoutput_triggered();

    void on_actionstarun_triggered();

    void on_actionsdrun_triggered();

    void on_action3D_triggered();

    void on_actionstadata_1_triggered();

    void on_actioncharts_triggered();

    void on_actioncloud_2_triggered();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_pushButtoneditable_clicked();

    void on_actionabout_triggered();

    void on_actiondyninput_triggered();

    void on_actionThreeD_triggered();

private:
    Ui::RBEvaluation *ui;
    //把各个子窗口都规定为成员变量，方便进行显示消失的操作，用show和hide函数，connect函数连接吧
    Sta_Input stainput;
    SimuDyn_Input simudyninput;
    Dyn_Input dyninput;
    Sta_Charts *stacharts;
    SimuDyn_Charts *simudyncharts;
    Sta_Output *staoutput;
    SimuDyn_Output *simudynoutput;
    IndiaOpenGL *indiaopengl;
    CloudTest *cloudtest;
    SimuDyn_ThreeD_Input *SD_3D_Input;

    //定义sta线程
    StaThread *m_stathread;
    //定义sta子线程
    QThread *threadsta;

    //定义SD线程
    SimuDynThread *m_simudynthread;
    //定义sta子线程
    QThread *threadsd;

    //线程中断标志为
    bool m_sdthreadstop;

    //主窗口TabWidget项目
    //子窗口显示过标志
    bool flag_staoutput;
    bool flag_stacharts;
    bool flag_simudynoutput;
    bool flag_simudyncharts;
    bool flag_openGL_3D = false;
    bool flag_openGL_Cloud = false;

    //标签页定义
    int m_tabWidgetworkingarea_index_staoutput; //定义标签页
    int m_tabWidgetworkingarea_index_stacharts; //定义标签页
    int m_tabWidgetworkingarea_index_simudyncharts; //定义标签页
    int m_tabWidgetworkingarea_index_simudynoutput; //定义标签页
    int m_tabWidgetworkingarea_index_openGL_3D; //定义标签页
    int m_tabWidgetworkingarea_index_openGL_Cloud; //定义标签页

    //tab子项目
    QWidget *m_tabstaoutputdyn;
    QWidget *m_tabstachartsdyn;
    QWidget *m_tabsimudynoutptudyn;
    QWidget *m_tabsimudynchartsdyn;
    QWidget *m_tabopenGL_3D;
    QWidget *m_tabopenGL_Cloud;

    //主窗口判定是静力学计算还是拟动力学计算
    int m_sta_simudyn_status;

    //ToolBar相关设置
    QToolButton *m_opennew_sta;
    QToolButton *m_opennew_simudyn;
    QToolButton *m_opennew_dyn;
    QToolButton *m_run;
    QWidget *m_toolbar_hboxlayout;
    QHBoxLayout *m_hboxlayout;  //与弹簧混搭着用
    QSpacerItem *m_toolbar_h_spacer;
    QToolButton *m_rollingbearing_mode;
    QToolButton *m_taperedrollerbearing_mode;
    QToolButton *m_cylindricalrollerbearing_mode;

    //模式选择
    int m_mode;

    //三维视图模式选择
    int m_threeD_mode;
    QString m_input3D_name;
    QString m_inputCloud_name;

signals:
    ////Sta部分
    //定义一个信号，告诉sta线程该启动了,传递的变量需要与sta函数自己保持一致
    void startthreadsta(int z,double D,double dm,double alpha0,double fi,double fe,double Fr,double Fa,double M);
    //定义一个信号，负责传送需要显示的sta数据
    void statooutput(double D,double dm,double alpha0,double fi,double fe,double Fr,double Fa,double M,double staoutputdeltaa,double staoutputdeltat,double staoutputtheta,int z,QVector<double> vecsalpha,QVector<double> vecsq);
    //定义一个信号，负责传送需要绘图的sta数据
    void statocharts(int z,QVector<double> vecsalpha,QVector<double> vecsq);

    ////SimuDyn部分
    //定义一个信号，告诉sd线程该启动了,传递的变量需要与sd函数自己保持一致
    void startthreadsd(double E, double v, double rho, double alpha0, double D, double di, double fe, double fi, int Z, double Fr, double Fa, double M, double ni, double omiga, double omiga1, double omiga2, int OR,double erro,int numbers);
    //定义一个信号把参数传送到output
    void sdtooutput(double E, double v, double rho, double alpha0, double D, double di, double fe, double fi, double Fr, double Fa, double M, double ni, double omiga, double omiga1, double omiga2, int OR, double erro, int numbers,int z,double Dthetat, double Ddeltaat, double Ddeltart, QVector<double> vecsdlamdat, QVector<double> vecsdalphaet, QVector<double> vecsdalphait, QVector<double> vecsdut, QVector<double> vecsdQet, QVector<double> vecsdQit, QVector<double> vecsdFct, QVector<double> vecsdMgt, QVector<double> vecsdwbt, QVector<double> vecsdwct, QVector<double> vecsdSRet, QVector<double> vecsdSRit);
    //定义一个信号把参数传递到charts
    void sdtocharts(int z, QVector<double> vecsdlamdat, QVector<double> vecsdalphaet, QVector<double> vecsdalphait, QVector<double> vecsdut, QVector<double> vecsdQet, QVector<double> vecsdQit, QVector<double> vecsdFct, QVector<double> vecsdMgt, QVector<double> vecsdwbt, QVector<double> vecsdwct, QVector<double> vecsdSRet, QVector<double> vecsdSRit);

    ////三维部分
    void MainWindowToThreeD(int m_threeD_mode);
    //定义一个传递P0的信号
    void MainWindowToThreeDInput(double p0);
    //3D发送文件名
    void FilenameToThreeD(QString filename);
    //Cloud发送文件名
    void FilenameToCloud(QString filename);
};
#endif // RBEVALUATION_H
