#include "rbevaluation.h"
#include "ui_rbevaluation.h"

//查bug用
#include<QDebug>


using namespace std;
////Sta部分
//定义几个全局变量，方便参数传值
int z;
double D,dm,alpha0,fi,fe,Fr,Fa,M;
//定义结果变量
double stadeltar,stadeltaa,statheta;
QVector<double> vecsalphatocharts(100);
QVector<double> vecsqtocharts(100);
////SimuDyn部分
int zsd,numberssd,ORsd;
double Dsd,dmsd,alpha0sd,fisd,fesd,Frsd,Fasd,Msd,vsd,Esd,osd,o1sd,o2sd,nisd,rhosd,errosd;
double sd_p0;

////Dyn部分
int z_dyn;
double D_dyn,dm_dyn,alpha0_dyn,fi_dyn,fe_dyn,Cp_dyn,Cg_dyn;
double E_dyn,v_dyn,rho_dyn,Ec_dyn,vc_dyn,rhoc_dyn;
double ni_dyn,Fa_dyn,Fr_dyn,My_dyn,Mz_dyn,OR_dyn;
double T0_dyn,n0_dyn,alpha_dyn,beta_dyn,K_dyn;
double h0_dyn,kt_dyn,Ferr_dyn,uerr_dyn,T_dyn;


RBEvaluation::RBEvaluation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RBEvaluation)
    , m_sta_simudyn_status(0)   //初始化
    , m_mode(0) //模式选择默认为0
{
    ui->setupUi(this);

    ////初始最大化显示
    setWindowState(Qt::WindowMaximized);
    //设置为不可缩小，否则图片可能会显示错误
    //setFixedSize(this->width(),this->height());
    //setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    //这个是把缩小按钮标志为假

    ////工具栏设置
    //toolbar宽度设置
    ui->toolBar->setMinimumHeight(50);
    //分配空间
    m_opennew_sta = new QToolButton(this);
    m_opennew_simudyn = new QToolButton(this);
    m_opennew_dyn = new QToolButton(this);
    m_run = new QToolButton(this);
    m_toolbar_hboxlayout = new QWidget(this);
    m_hboxlayout = new QHBoxLayout(m_toolbar_hboxlayout);   //hbox写在里面
    m_toolbar_h_spacer = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding);
    m_rollingbearing_mode = new QToolButton(this);
    m_taperedrollerbearing_mode = new QToolButton(this);
    m_cylindricalrollerbearing_mode = new QToolButton(this);
    //ICON设置
    m_opennew_sta->setFixedSize(50,50);
    //m_opennew_sta->setIconSize(QSize(100,100));
    m_opennew_sta->setIcon(QIcon("sta.png"));   //
    m_opennew_simudyn->setFixedSize(50,50);
    m_opennew_simudyn->setIcon(QIcon("simudyn.png"));
    m_opennew_dyn->setFixedSize(50,50);         //
    m_opennew_dyn->setIcon(QIcon("dyn.png"));
    m_run->setFixedSize(50,50);                 //
    m_run->setIcon(QIcon("run.png"));
    m_rollingbearing_mode->setFixedSize(50,50); //
    m_rollingbearing_mode->setIcon(QIcon("rb.png"));
    m_taperedrollerbearing_mode->setFixedSize(50,50); //
    m_taperedrollerbearing_mode->setIcon(QIcon("tb.png"));
    m_cylindricalrollerbearing_mode->setFixedSize(50,50); //
    m_cylindricalrollerbearing_mode->setIcon(QIcon("cb.png"));
    //加入显示
    //从左往右加
    ui->toolBar->addWidget(m_opennew_sta);
    ui->toolBar->addWidget(m_opennew_simudyn);
    ui->toolBar->addWidget(m_opennew_dyn);
    ui->toolBar->addSeparator();    //加分割杠
    ui->toolBar->addWidget(m_run);
    ui->toolBar->addSeparator();
    //从右往左加,只需中间添加一个弹簧
    m_hboxlayout->addItem(m_toolbar_h_spacer);
    ui->toolBar->addWidget(m_toolbar_hboxlayout);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(m_rollingbearing_mode);
    ui->toolBar->addWidget(m_taperedrollerbearing_mode);
    ui->toolBar->addWidget(m_cylindricalrollerbearing_mode);
    //设置tooltip
    m_opennew_sta->setToolTip("新建静力学计算");
    m_opennew_simudyn->setToolTip("新建拟动力学计算");
    m_opennew_dyn->setToolTip("新建动力学计算");
    m_run->setToolTip("运行");
    m_rollingbearing_mode->setToolTip("滚动球轴承分析");
    m_taperedrollerbearing_mode->setToolTip("圆锥滚子轴承分析");
    m_cylindricalrollerbearing_mode->setToolTip("圆柱滚子轴承分析");
    //设置点击功能
    connect(m_opennew_sta,&QPushButton::clicked,this,&RBEvaluation::on_actionstainput_triggered); //显示静力学input
    connect(m_opennew_simudyn,&QPushButton::clicked,this,&RBEvaluation::on_actionsdinput_triggered);    //显示拟动力学input
    connect(m_opennew_dyn,&QPushButton::clicked,this,&RBEvaluation::on_actiondyninput_triggered);
    connect(m_run,&QPushButton::clicked,
            [=]()
            {
            switch (m_sta_simudyn_status)
            {
            case 1: on_actionstarun_triggered();break;
            case 2: on_actionsdrun_triggered();break;
            case 3:break;
            default:break;
            }
            }
            );
    connect(m_rollingbearing_mode,&QPushButton::clicked,
            [=]()
            {
                m_mode = 1; //mode标志位置一表示滚动球轴承在使用
                //pixmap设置，并且自适应图片
                QPixmap *pixmap = new QPixmap("rbpixmap.png");
                pixmap->scaled(ui->labelpixmap->size(), Qt::KeepAspectRatio);
                ui->labelpixmap->setScaledContents(true);
                ui->labelpixmap->setPixmap(*pixmap);
            }
            );
    connect(m_taperedrollerbearing_mode,&QPushButton::clicked,
            [=]()
            {
                m_mode = 2;//mode标志位置2表示圆锥滚子轴承在使用
                //pixmap设置，并且自适应图片
                QPixmap *pixmap = new QPixmap("tbpixmap.png");
                pixmap->scaled(ui->labelpixmap->size(), Qt::KeepAspectRatio);
                ui->labelpixmap->setScaledContents(true);
                ui->labelpixmap->setPixmap(*pixmap);
            }
            );
    connect(m_cylindricalrollerbearing_mode,&QPushButton::clicked,
            [=]()
            {
                m_mode = 3;//mode标志位置3表示圆柱滚子轴承在使用
                //pixmap设置，并且自适应图片
                QPixmap *pixmap = new QPixmap("cbpixmap.png");
                pixmap->scaled(ui->labelpixmap->size(), Qt::KeepAspectRatio);
                ui->labelpixmap->setScaledContents(true);
                ui->labelpixmap->setPixmap(*pixmap);
            }
            );


    //分配子窗口空间
    staoutput = new Sta_Output();
    stacharts = new Sta_Charts();
    simudyncharts = new SimuDyn_Charts();
    simudynoutput = new SimuDyn_Output();
    cloudtest = new CloudTest();
    indiaopengl = new IndiaOpenGL();
    SD_3D_Input = new SimuDyn_ThreeD_Input();


    ////线程
    //给线程动态分配空间，但是不能指定父对象
    m_stathread = new StaThread;
    m_simudynthread = new SimuDynThread;
    //创建子线程
    threadsta = new QThread(this);
    threadsd = new QThread(this);
    //把自定义的线程加入到子线程中
    m_stathread->moveToThread(threadsta);
    m_simudynthread->moveToThread(threadsd);


    ////Sta部分
    //建立连接,一点下按钮就收集读取的数据,由于该成员变量不是指针，所以需要取一下地址
    connect(&stainput,&Sta_Input::stainput,this,&RBEvaluation::stadealinput);
    //建立连接,一点下按钮就开始计算
    connect(this,&RBEvaluation::startthreadsta,m_stathread,&StaThread::sta);
    //建立连接,接收函数
    connect(m_stathread,&StaThread::stasendback,this,&RBEvaluation::stadealresult);
    //建立连接，参数传到output窗口
    connect(this,&RBEvaluation::statooutput,staoutput,&Sta_Output::stadealoutput);
    //建立连接，参数传到charts窗口
    connect(this,&RBEvaluation::statocharts,stacharts,&Sta_Charts::stadealcharts);
    //建立连接，如果sta计算完成，则停止线程
    connect(m_stathread,&StaThread::staprogress,this,&RBEvaluation::dealdestroyed);


    ////SD部分
    //建立连接,一点下按钮就收集读取的数据,由于该成员变量不是指针，所以需要取一下地址
    connect(&simudyninput,&SimuDyn_Input::sdinput,this,&RBEvaluation::sddealinput);
    //建立连接,一点下按钮就开始计算
    connect(this,&RBEvaluation::startthreadsd,m_simudynthread,&SimuDynThread::dyn);
    //建立连接,接收误差参数类进行主窗口绘图
    //connect(m_simudynthread,&SimuDynThread::sdthreadtodiagro,this,&RBEvaluation::sddealerro);
    //建立连接,接收函数准备分发进行绘图等等工作
    connect(m_simudynthread,&SimuDynThread::sdthreadtomain,this,&RBEvaluation::sddealresult);
    //建立连接，参数传到output窗口
    connect(this,&RBEvaluation::sdtooutput,simudynoutput,&SimuDyn_Output::sddealoutput);
    //建立连接，参数传到charts窗口
    connect(this,&RBEvaluation::sdtocharts,simudyncharts,&SimuDyn_Charts::sddealcharts);
    //建立连接，如果simudyn超出极限次数，则停止线程
    connect(m_simudynthread,&SimuDynThread::sdthreadnotwork,this,&RBEvaluation::dealdestroyed);
    //建立连接，如果simudyn计算结束，则停止线程，否则会无法使用destroy窗口信号
    connect(m_simudynthread,&SimuDynThread::sdthreadisallover,this,&RBEvaluation::dealdestroyed);
    //建立连接，simudyn计算被中断
    connect(m_simudynthread,&SimuDynThread::stopdynthread,
            [=]()
            {
            if(threadsd->isRunning()==false)
            {
                return;
            }
            threadsd->quit();
            threadsd->wait();
            }
            );


    ////DYN部分
    //建立与数据输入窗口的联系，输入数据
    connect(&dyninput,&Dyn_Input::dyninput,this,&RBEvaluation::dyndealinput);

    ////3D部分
    connect(this,&RBEvaluation::MainWindowToThreeD,indiaopengl,&IndiaOpenGL::dealtopview);
    //建立与三维输入界面的连接，输入最大赫兹压力
    connect(this,&RBEvaluation::MainWindowToThreeDInput,SD_3D_Input,&SimuDyn_ThreeD_Input::dealMainWindowToThreeDInput);
    //建立与三维输入界面的连接，输入读取文件的名称
    connect(this,&RBEvaluation::FilenameToThreeD,indiaopengl,&IndiaOpenGL::dealSentFilename);
    //建立与云图的连接，输入读取文件的名称
    connect(this,&RBEvaluation::FilenameToCloud,cloudtest,&CloudTest::dealCloudSentFilename);

    ////公共部分
    //与自己建立连接，当关闭窗口的时候，也可以终止线程,两个都关
    connect(this,&RBEvaluation::destroyed,this,&RBEvaluation::dealdestroyed);

    //建立关闭主界面工作区tab连接
    connect(ui->tabWidgetworkingarea,&QTabWidget::tabCloseRequested,this,&RBEvaluation::TabClose);


    //设计逻辑结构，使得初始化的时候一些按键无法被按下
    ui->actionstarun->setEnabled(false);
    ui->actionstaoutput->setEnabled(false);
    ui->actionstachart->setEnabled(false);
    ui->actionsdrun->setEnabled(false);
    ui->actionsdoutput->setEnabled(false);
    ui->actionsdchart->setEnabled(false);
    //ui->action3D->setEnabled(false);
    //ui->actionsta->setEnabled(false);
    //ui->actionsimudyn->setEnabled(false);
    ui->actionstaalpha->setEnabled(false);
    ui->actionstaq->setEnabled(false);
    ui->actionalphai->setEnabled(false);
    ui->actionalphae->setEnabled(false);
    ui->actionlamda->setEnabled(false);
    ui->actionu->setEnabled(false);
    ui->actionQi->setEnabled(false);
    ui->actionQe->setEnabled(false);
    ui->actionFc->setEnabled(false);
    ui->actionMg->setEnabled(false);
    ui->actionwb->setEnabled(false);
    ui->actionwc->setEnabled(false);
    ui->actionSRi->setEnabled(false);
    ui->actionSRe->setEnabled(false);

    //标志为初始化
    flag_stacharts = false; //标志当前没有标签页
    flag_staoutput = false;
    flag_simudynoutput = false;
    flag_simudyncharts = false;
}


RBEvaluation::~RBEvaluation()
{
    delete ui;
}

////Sta部分
//按下新建按钮便打开静力学输入参数Form
void RBEvaluation::on_actionstainput_triggered()
{
    if(m_mode == 1) //如果选定了rb模式1
    {
        stainput.show();
        //让窗口显示在屏幕中央
        stainput.move ((QApplication::desktop()->width() - stainput.width())/2,(QApplication::desktop()->height() - stainput.height())/2);
    }
}


//槽函数进行数据传递，从input传到这里
void RBEvaluation::stadealinput(int sz, double sD, double sdm, double salpha0, double sfi, double sfe, double sFr, double sFa, double sM)
{
    z=sz;
    D=sD;
    dm=sdm;
    alpha0=salpha0;
    fi=sfi;
    fe=sfe;
    Fr=sFr;
    Fa=sFa;
    M=sM;

    //将sta计算设置为true
    ui->actionstarun->setEnabled(true);

    //那边点了应用，这边就开始画TreeWidget
    ui->treeWidget->clear();    //清空以前的东西

    ui->treeWidget->setColumnCount(1); //设置列数
    //设置str编码类型
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    ui->treeWidget->setHeaderLabel(tr("静力学计算输入参数"));    //设置标题
    QList<QTreeWidgetItem *> items;

    //创建两个节点
    QTreeWidgetItem *father_Item_1 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("工况条件")));
    QTreeWidgetItem *father_Item_2 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("结构参数")));

    items.append(father_Item_1);
    items.append(father_Item_2);

    //添加顶层节点
    ui->treeWidget->insertTopLevelItems(0,items);
    //添加子节点_1
    QTreeWidgetItem *Child_Item_Fr = new QTreeWidgetItem(father_Item_1,QStringList(QString("径向载荷(Fr)")));
    QTreeWidgetItem *Child_Item_Fa = new QTreeWidgetItem(father_Item_1,QStringList(QString("轴向载荷(Fa)")));
    QTreeWidgetItem *Child_Item_M = new QTreeWidgetItem(father_Item_1,QStringList(QString("力矩(M)")));
    father_Item_1->addChild(Child_Item_Fr);
    father_Item_1->addChild(Child_Item_Fa);
    father_Item_1->addChild(Child_Item_M);
    //添加子节点_2
    QTreeWidgetItem *Child_Item_Z = new QTreeWidgetItem(father_Item_2,QStringList(QString("钢球个数(Z)")));
    QTreeWidgetItem *Child_Item_D = new QTreeWidgetItem(father_Item_2,QStringList(QString("钢球直径(D)")));
    QTreeWidgetItem *Child_Item_dm = new QTreeWidgetItem(father_Item_2,QStringList(QString("内圈直径(dm)")));
    QTreeWidgetItem *Child_Item_alpha0 = new QTreeWidgetItem(father_Item_2,QStringList(QString("初始接触角")));
    QTreeWidgetItem *Child_Item_fi = new QTreeWidgetItem(father_Item_2,QStringList(QString("内圈沟渠率半径系数")));
    QTreeWidgetItem *Child_Item_fe = new QTreeWidgetItem(father_Item_2,QStringList(QString("外圈沟渠率半径系数")));
    father_Item_2->addChild(Child_Item_Z);
    father_Item_2->addChild(Child_Item_D);
    father_Item_2->addChild(Child_Item_dm);
    father_Item_2->addChild(Child_Item_alpha0);
    father_Item_2->addChild(Child_Item_fi);
    father_Item_2->addChild(Child_Item_fe);

    ui->treeWidget->expandAll();
    m_sta_simudyn_status = 1; //置一表示当前是静力学分析

    //pixmap设置，并且自适应图片
    //ui->labelpixmap->setPixmap(QPixmap("simupixmap.png"));
    //QPixmap *pixmap = new QPixmap("rb/pixmap.png");
    //pixmap->scaled(ui->labelpixmap->size(), Qt::KeepAspectRatio);
    //ui->labelpixmap->setScaledContents(true);
    //ui->labelpixmap->setPixmap(*pixmap);
}


//按下静力学运行按钮进行计算，把数据从这里传到thread
void RBEvaluation::on_actionstarun_triggered()
{
    //判断一下，不再运行的时候才启动
    if(threadsta->isRunning()==true)
    {
        return;
    }
    //启动线程，但是没有启动线程处理函数
    threadsta->start();
    //发送信号告诉线程该启动了
    emit startthreadsta(z,D,dm,alpha0,fi,fe,Fr,Fa,M);
}


//槽函数把算好的值都放回来
void RBEvaluation::stadealresult(double deltar, double deltaa, double theta, QVector<double> vecsalpha, QVector<double> vecsq)
{
    stadeltar=deltar;
    stadeltaa=deltaa;
    statheta=theta;
    static int i;
    for(i=0;i<z;i++)
    {
        vecsalphatocharts[i]=vecsalpha[i];
        vecsqtocharts[i]=vecsq[i];
    }

    //关闭sta线程
    if(threadsta->isRunning()==false)
    {
        return;
    }
    threadsta->quit();
    threadsta->wait();

    //计算完成，可显示查看结果，图表，查看txt按钮
    ui->actionstaoutput->setEnabled(true);
    ui->actionstachart->setEnabled(true);
    //ui->actionsta->setEnabled(true);
}


//按下显示结果按钮便打开静力学计算结果
void RBEvaluation::on_actionstaoutput_triggered()
{
    if(flag_staoutput == false)    //如果没被按下
    {
        //标志为设置
        flag_staoutput = true;

        //发送数据信号
        emit statooutput(D,dm,alpha0,fi,fe,Fr,Fa,M,stadeltaa,stadeltar,statheta,z,vecsalphatocharts,vecsqtocharts);
        //如果不存在该标签页，则创建一个新的标签页
        m_tabstaoutputdyn = new QWidget();
        int currentindex = ui->tabWidgetworkingarea->addTab(m_tabstaoutputdyn,"静力学计算结果");
        ui->tabWidgetworkingarea->setCurrentIndex(currentindex);
        ui->tabWidgetworkingarea->setTabsClosable(true);    //设置为可关闭的

        //将图表写进来
        staoutput->setParent(m_tabstaoutputdyn);
        //stacharts->move ((QApplication::desktop()->width() - stacharts->width())/2,(QApplication::desktop()->height() - stacharts->height())/2);//让窗口显示在屏幕中央
        //获取长和宽
        qreal tabstaoutputdyn_width,tabstaoutputdyn_height;
        tabstaoutputdyn_width = ui->tabWidgetworkingarea->geometry().width();
        tabstaoutputdyn_height = ui->tabWidgetworkingarea->geometry().height();

        //resize安排窗口，使得其能自适应填满
        qreal heightratio;
        heightratio = 0.95;
        staoutput->resize(tabstaoutputdyn_width,tabstaoutputdyn_height*heightratio);
        //显示在左上角
        staoutput->move(0,0);
        staoutput->show();
    }

    //如果存在，则发出警告
    else if(flag_staoutput == true)
    {
        SetMessageBoxSize msgBox;   //自己写了一个类，可以设置size的继承于QMessageBox的类
        msgBox.AutosetSize(300,100);
        msgBox.setIcon(QMessageBox::Warning); //设置类型
        msgBox.setWindowTitle("警告");
        msgBox.setText("静力学计算结果结果已存在");
        //msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
    //让窗口显示在屏幕中央
    //staoutput.move ((QApplication::desktop()->width() - staoutput.width())/2,(QApplication::desktop()->height() - staoutput.height())/2);
}


//按下图表按钮便打开静力学图表
void RBEvaluation::on_actionstachart_triggered()
{
    if(flag_stacharts == false)    //如果没被按下
    {
        //标志为设置
        flag_stacharts = true;

        //发送数据信号
        emit statocharts(z,vecsalphatocharts,vecsqtocharts);
        //如果不存在该标签页，则创建一个新的标签页
        m_tabstachartsdyn = new QWidget();

        int currentindex = ui->tabWidgetworkingarea->addTab(m_tabstachartsdyn,"静力学图表");
        ui->tabWidgetworkingarea->setCurrentIndex(currentindex);
        ui->tabWidgetworkingarea->setTabsClosable(true);    //设置为可关闭的
        //将图表写进来
        stacharts->setParent(m_tabstachartsdyn);
        //stacharts->move ((QApplication::desktop()->width() - stacharts->width())/2,(QApplication::desktop()->height() - stacharts->height())/2);//让窗口显示在屏幕中央
        //获取长和宽
        qreal tabstachartsdyn_width,tabstachartsdyn_height;
        tabstachartsdyn_width = ui->tabWidgetworkingarea->geometry().width();
        tabstachartsdyn_height = ui->tabWidgetworkingarea->geometry().height();

        //resize安排窗口，使得其能自适应填满
        qreal heightratio;
        heightratio = 0.95;
        stacharts->resize(tabstachartsdyn_width,tabstachartsdyn_height*heightratio);
        //显示在左上角
        stacharts->move(0,0);
        stacharts->show();
    }

    //如果存在，则发出警告
    else if(flag_stacharts == true)
    {
        SetMessageBoxSize msgBox;   //自己写了一个类，可以设置size的继承于QMessageBox的类
        msgBox.AutosetSize(300,100);
        msgBox.setIcon(QMessageBox::Warning); //设置类型
        msgBox.setWindowTitle("警告");
        msgBox.setText("静力学图表结果已存在");
        //msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}


////SimuDyn部分
//按下新建按钮便打开拟动力学输入参数Form
void RBEvaluation::on_actionsdinput_triggered()
{
    if(m_mode == 1)
    {
        simudyninput.show();
        //让窗口显示在屏幕中央
        simudyninput.move ((QApplication::desktop()->width() - simudyninput.width())/2,(QApplication::desktop()->height() - simudyninput.height())/2);
    }
}

//槽函数进行数据传递，从input传到这里
void RBEvaluation::sddealinput(double E, double v, double rho, double alpha0, double D, double di, double fe, double fi, int Z, double Fr, double Fa, double M, double ni, double omiga, double omiga1, double omiga2, int OR, double erro, int numbers)
{
    Esd=E;
    vsd=v;
    rhosd=rho;
    alpha0sd=alpha0;
    Dsd=D;
    dmsd=di;
    fesd=fe;
    fisd=fi;
    zsd=Z;
    Fasd=Fa;
    Frsd=Fr;
    Msd=M;
    nisd=ni;
    ORsd=OR;
    osd=omiga;
    o1sd=omiga1;
    o2sd=omiga2;
    errosd=erro;
    numberssd=numbers;
    //让用户可以开始点计算按钮
    ui->actionsdrun->setEnabled(true);

    //那边点了应用，这边就ka开始画TreeWidget
    ui->treeWidget->clear();    //清空以前的东西

    ui->treeWidget->setColumnCount(1); //设置列数
    //设置str编码类型
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    ui->treeWidget->setHeaderLabel(tr("拟动力学计算输入参数"));    //设置标题
    QList<QTreeWidgetItem *> items;

    //创建两个节点
    QTreeWidgetItem *father_Item_1 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("工况条件")));
    QTreeWidgetItem *father_Item_2 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("结构参数")));
    QTreeWidgetItem *father_Item_3 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("材料参数")));
    QTreeWidgetItem *father_Item_4 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("引导方式")));
    QTreeWidgetItem *father_Item_5 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("润滑剂/摩擦相关参数")));
    QTreeWidgetItem *father_Item_6 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("数值计算相关参数")));

    items.append(father_Item_1);
    items.append(father_Item_2);
    items.append(father_Item_3);
    items.append(father_Item_4);
    items.append(father_Item_5);
    items.append(father_Item_6);

    //添加顶层节点
    ui->treeWidget->insertTopLevelItems(0,items);
    //添加子节点_1
    QTreeWidgetItem *Child_Item_Fr = new QTreeWidgetItem(father_Item_1,QStringList(QString("径向载荷(Fr)")));
    QTreeWidgetItem *Child_Item_Fa = new QTreeWidgetItem(father_Item_1,QStringList(QString("轴向载荷(Fa)")));
    QTreeWidgetItem *Child_Item_M = new QTreeWidgetItem(father_Item_1,QStringList(QString("力矩(M)")));
    QTreeWidgetItem *Child_Item_ni = new QTreeWidgetItem(father_Item_1,QStringList(QString("内圈转速(ni)")));
    father_Item_1->addChild(Child_Item_Fr);
    father_Item_1->addChild(Child_Item_Fa);
    father_Item_1->addChild(Child_Item_M);
    father_Item_1->addChild(Child_Item_ni);
    //添加子节点_2
    QTreeWidgetItem *Child_Item_Z = new QTreeWidgetItem(father_Item_2,QStringList(QString("钢球个数(Z)")));
    QTreeWidgetItem *Child_Item_D = new QTreeWidgetItem(father_Item_2,QStringList(QString("钢球直径(D)")));
    QTreeWidgetItem *Child_Item_dm = new QTreeWidgetItem(father_Item_2,QStringList(QString("内圈直径(dm)")));
    QTreeWidgetItem *Child_Item_alpha0 = new QTreeWidgetItem(father_Item_2,QStringList(QString("初始接触角")));
    QTreeWidgetItem *Child_Item_fi = new QTreeWidgetItem(father_Item_2,QStringList(QString("内圈沟渠率半径系数")));
    QTreeWidgetItem *Child_Item_fe = new QTreeWidgetItem(father_Item_2,QStringList(QString("外圈沟渠率半径系数")));
    father_Item_2->addChild(Child_Item_Z);
    father_Item_2->addChild(Child_Item_D);
    father_Item_2->addChild(Child_Item_dm);
    father_Item_2->addChild(Child_Item_alpha0);
    father_Item_2->addChild(Child_Item_fi);
    father_Item_2->addChild(Child_Item_fe);
    //添加子节点_3
    QTreeWidgetItem *Child_Item_rho = new QTreeWidgetItem(father_Item_3,QStringList(QString("钢球材料密度")));
    QTreeWidgetItem *Child_Item_E = new QTreeWidgetItem(father_Item_3,QStringList(QString("弹性模量")));
    QTreeWidgetItem *Child_Item_v = new QTreeWidgetItem(father_Item_3,QStringList(QString("泊松比")));
    father_Item_3->addChild(Child_Item_rho);
    father_Item_3->addChild(Child_Item_E);
    father_Item_3->addChild(Child_Item_v);
    //添加子节点_4
    QTreeWidgetItem *Child_Item_OR = new QTreeWidgetItem(father_Item_4,QStringList(QString("引导方式")));
    father_Item_4->addChild(Child_Item_OR);
    //添加子节点_5
    QTreeWidgetItem *Child_Item_episilo = new QTreeWidgetItem(father_Item_5,QStringList(QString("润滑油黏度(η)")));
    QTreeWidgetItem *Child_Item_rr = new QTreeWidgetItem(father_Item_5,QStringList(QString("润滑油密度(ρ)")));
    QTreeWidgetItem *Child_Item_alpha = new QTreeWidgetItem(father_Item_5,QStringList(QString("润滑油黏压系数(α)")));
    QTreeWidgetItem *Child_Item_beita = new QTreeWidgetItem(father_Item_5,QStringList(QString("润滑油黏温(β)")));
    QTreeWidgetItem *Child_Item_mu = new QTreeWidgetItem(father_Item_5,QStringList(QString("摩擦系数(μ)")));
    father_Item_5->addChild(Child_Item_episilo);
    father_Item_5->addChild(Child_Item_rr);
    father_Item_5->addChild(Child_Item_alpha);
    father_Item_5->addChild(Child_Item_beita);
    father_Item_5->addChild(Child_Item_mu);
    //添加子节点_6
    QTreeWidgetItem *Child_Item_omigaD = new QTreeWidgetItem(father_Item_6,QStringList(QString("位移修正系数(ωD)")));
    QTreeWidgetItem *Child_Item_omigaRr = new QTreeWidgetItem(father_Item_6,QStringList(QString("姿态角修正系数(ωγ)")));
    QTreeWidgetItem *Child_Item_erro = new QTreeWidgetItem(father_Item_6,QStringList(QString("规定迭代误差")));
    QTreeWidgetItem *Child_Item_numbers = new QTreeWidgetItem(father_Item_6,QStringList(QString("极限迭代次数")));
    father_Item_6->addChild(Child_Item_omigaD);
    father_Item_6->addChild(Child_Item_omigaRr);
    father_Item_6->addChild(Child_Item_erro);
    father_Item_6->addChild(Child_Item_numbers);


    ui->treeWidget->expandAll();
    m_sta_simudyn_status = 2; //置二表示当前是拟动力学分析

    //pixmap设置，并且自适应图片
    //ui->labelpixmap->setPixmap(QPixmap("simupixmap.png"));
    //QPixmap *pixmap = new QPixmap("rbpixmap.png");
    //pixmap->scaled(ui->labelpixmap->size(), Qt::KeepAspectRatio);
    //ui->labelpixmap->setScaledContents(true);
    //ui->labelpixmap->setPixmap(*pixmap);
}


//按下拟动力学运行按钮进行计算
void RBEvaluation::on_actionsdrun_triggered()
{
    //判断一下，不再运行的时候才启动
    if(threadsd->isRunning()==true)
    {
        return;
    }

    //启动线程，但是没有启动线程处理函数
    threadsd->start();
    //发送信号告诉线程该启动了
    emit startthreadsd(Esd,vsd,rhosd,alpha0sd,Dsd,dmsd,fesd,fisd,zsd,Frsd,Fasd,Msd,nisd,osd,o1sd,o2sd,ORsd,errosd,numberssd);
}

//收集数据进行处理，准备发放,可以直接在这里把数据就传给各个窗口
void RBEvaluation::sddealresult(double Dthetat, double Ddeltaat, double Ddeltart, QVector<double> vecsdlamdat, QVector<double> vecsdalphaet, QVector<double> vecsdalphait, QVector<double> vecsdut, QVector<double> vecsdQet, QVector<double> vecsdQit, QVector<double> vecsdFct, QVector<double> vecsdMgt, QVector<double> vecsdwbt, QVector<double> vecsdwct, QVector<double> vecsdSRet, QVector<double> vecsdSRit ,double P0)
{
    //给output窗口发送数据
    emit sdtooutput(Esd,vsd,rhosd,alpha0sd,Dsd,dmsd,fesd,fisd,Frsd,Fasd,Msd,nisd,osd,o1sd,o2sd,ORsd,errosd,numberssd,zsd,Dthetat,Ddeltaat,Ddeltart, vecsdlamdat,vecsdalphaet,vecsdalphait,vecsdut,vecsdQet,vecsdQit,vecsdFct,vecsdMgt,vecsdwbt,vecsdwct,vecsdSRet,vecsdSRit);
    //给charts窗口发送数据
    emit sdtocharts(zsd,vecsdlamdat,vecsdalphaet,vecsdalphait,vecsdut,vecsdQet,vecsdQit,vecsdFct,vecsdMgt,vecsdwbt,vecsdwct,vecsdSRet,vecsdSRit);
    //与三维图交互
    sd_p0 = P0;
    //给输入界面传入数据
    emit MainWindowToThreeDInput(sd_p0);

    //关闭sd线程
    if(threadsd->isRunning()==false)
    {
        return;
    }
    threadsd->quit();
    threadsd->wait();

    //计算结束 使得可以查看结果
    ui->actionsdoutput->setEnabled(true);
    ui->actionsdchart->setEnabled(true);
    //ui->actionsimudyn->setEnabled(true);
}



//按下图表按钮便打开拟动力学图表
void RBEvaluation::on_actionsdchart_triggered()
{
    if(flag_simudyncharts == false)    //如果没被按下
    {
        //标志为设置
        flag_simudyncharts = true;

        //如果不存在该标签页，则创建一个新的标签页
        m_tabsimudynchartsdyn = new QWidget();

        int currentindex = ui->tabWidgetworkingarea->addTab(m_tabsimudynchartsdyn,"拟动力学图表");
        ui->tabWidgetworkingarea->setCurrentIndex(currentindex);
        ui->tabWidgetworkingarea->setTabsClosable(true);    //设置为可关闭的

        //将图表写进来
        simudyncharts->setParent(m_tabsimudynchartsdyn);
        //stacharts->move ((QApplication::desktop()->width() - stacharts->width())/2,(QApplication::desktop()->height() - stacharts->height())/2);//让窗口显示在屏幕中央
        //获取长和宽
        qreal tabsimudynchartsdyn_width,tabsimudynchartsdyn_height;
        tabsimudynchartsdyn_width = ui->tabWidgetworkingarea->geometry().width();
        tabsimudynchartsdyn_height = ui->tabWidgetworkingarea->geometry().height();

        //resize安排窗口，使得其能自适应填满
        qreal heightratio;
        heightratio = 0.95;
        simudyncharts->resize(tabsimudynchartsdyn_width,tabsimudynchartsdyn_height*heightratio);

        //显示在左上角
        simudyncharts->move(0,0);
        simudyncharts->show();
    }

    //如果存在，则发出警告
    else if(flag_simudyncharts == true)
    {
        SetMessageBoxSize msgBox;   //自己写了一个类，可以设置size的继承于QMessageBox的类
        msgBox.AutosetSize(300,100);
        msgBox.setIcon(QMessageBox::Warning); //设置类型
        msgBox.setWindowTitle("警告");
        msgBox.setText("拟动力学图表结果已存在");
        //msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
    //让窗口显示在屏幕中央
    //simudyncharts->move ((QApplication::desktop()->width() - simudyncharts->width())/2,(QApplication::desktop()->height() - simudyncharts->height())/2);
}


//按下显示结果按钮便打开拟动力学计算结果
void RBEvaluation::on_actionsdoutput_triggered()
{
    if(flag_simudynoutput == false)    //如果没被按下
    {
        //标志为设置
        flag_simudynoutput = true;

        //如果不存在该标签页，则创建一个新的标签页
        m_tabsimudynoutptudyn = new QWidget();
        int currentindex = ui->tabWidgetworkingarea->addTab(m_tabsimudynoutptudyn,"拟动力学计算结果");
        ui->tabWidgetworkingarea->setCurrentIndex(currentindex);
        ui->tabWidgetworkingarea->setTabsClosable(true);    //设置为可关闭的

        //将图表写进来
        simudynoutput->setParent(m_tabsimudynoutptudyn);
        //stacharts->move ((QApplication::desktop()->width() - stacharts->width())/2,(QApplication::desktop()->height() - stacharts->height())/2);//让窗口显示在屏幕中央
        //获取长和宽
        qreal tabsimudynoutputdyn_width,tabsimudynoutputdyn_height;
        tabsimudynoutputdyn_width = ui->tabWidgetworkingarea->geometry().width();
        tabsimudynoutputdyn_height = ui->tabWidgetworkingarea->geometry().height();

        //resize安排窗口，使得其能自适应填满
        qreal heightratio;
        heightratio = 0.95;
        simudynoutput->resize(tabsimudynoutputdyn_width,tabsimudynoutputdyn_height*heightratio);

        //显示在左上角
        simudynoutput->move(0,0);
        simudynoutput->show();
    }

    //如果存在，则发出警告
    else if(flag_simudynoutput == true)
    {
        SetMessageBoxSize msgBox;   //自己写了一个类，可以设置size的继承于QMessageBox的类
        msgBox.AutosetSize(300,100);
        msgBox.setIcon(QMessageBox::Warning); //设置类型
        msgBox.setWindowTitle("警告");
        msgBox.setText("拟动力学计算结果已存在");
        //msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }

    //让窗口显示在屏幕中央
    //simudynoutput.move ((QApplication::desktop()->width() - simudynoutput.width())/2,(QApplication::desktop()->height() - simudynoutput.height())/2);
}


////Dyn部分
//打开输入界面
void RBEvaluation::on_actiondyninput_triggered()
{
    if(m_mode == 1)
    {
        dyninput.show();
        //让窗口显示在屏幕中央
        dyninput.move ((QApplication::desktop()->width() - dyninput.width())/2,(QApplication::desktop()->height() - dyninput.height())/2);
    }
}

//接收到来自input的存好的数据
void RBEvaluation::dyndealinput(int zdyn, double Ddyn, double dmdyn, double alpha0dyn, double fidyn, double fedyn, double Cpdyn, double Cgdyn, double Edyn, double vdyn, double rhodyn, double Ecdyn, double vcdyn, double rhocdyn, double nidyn, double Fadyn, double Frdyn, double Mydyn, double Mzdy, double ORdyn, double T0dyn, double n0dyn, double alphadyn, double betadyn, double Kdyn,double h0dyn,double ktdyn,double Ferrdyn,double uerrdyn,double Tdyn)
{
    //数据存入主界面
    z_dyn = zdyn;
    D_dyn = Ddyn,dm_dyn = dmdyn,alpha0_dyn=alpha0dyn,fi_dyn=fidyn,fe_dyn=fedyn,Cp_dyn=Cpdyn,Cg_dyn=Cgdyn;
    E_dyn=Edyn,v_dyn=vdyn,rho_dyn=rhodyn,Ec_dyn=Ecdyn,vc_dyn=vcdyn,rhoc_dyn=rhocdyn;
    ni_dyn=nidyn,Fa_dyn=Fadyn,Fr_dyn=Frdyn,My_dyn=Mydyn,Mz_dyn=Mzdy,OR_dyn=ORdyn;
    T0_dyn=T0dyn,n0_dyn=n0dyn,alpha_dyn=alphadyn,beta_dyn=betadyn,K_dyn=Kdyn;
    h0_dyn=h0dyn,kt_dyn=ktdyn,Ferr_dyn=Ferrdyn,uerr_dyn=uerrdyn,T_dyn=Tdyn;


    //TreeWidget
    //那边点了应用，这边就ka开始画TreeWidget
    ui->treeWidget->clear();    //清空以前的东西
    ui->treeWidget->setColumnCount(1); //设置列数
    //设置str编码类型
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    ui->treeWidget->setHeaderLabel(tr("动力学计算输入参数"));    //设置标题
    QList<QTreeWidgetItem *> items;
    //创建两个节点
    QTreeWidgetItem *father_Item_1 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("工况条件")));
    QTreeWidgetItem *father_Item_2 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("结构参数")));
    QTreeWidgetItem *father_Item_3 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("材料参数")));
    QTreeWidgetItem *father_Item_4 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("润滑剂/摩擦相关参数")));
    QTreeWidgetItem *father_Item_5 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("数值计算相关参数")));
    items.append(father_Item_1);
    items.append(father_Item_2);
    items.append(father_Item_3);
    items.append(father_Item_4);
    items.append(father_Item_5);

    //添加顶层节点
    ui->treeWidget->insertTopLevelItems(0,items);
    //添加子节点_1
    QTreeWidgetItem *Child_Item_Fr = new QTreeWidgetItem(father_Item_1,QStringList(QString("径向载荷(Fr)")));
    QTreeWidgetItem *Child_Item_Fa = new QTreeWidgetItem(father_Item_1,QStringList(QString("轴向载荷(Fa)")));
    QTreeWidgetItem *Child_Item_My = new QTreeWidgetItem(father_Item_1,QStringList(QString("力矩载荷(My)")));
    QTreeWidgetItem *Child_Item_Mz = new QTreeWidgetItem(father_Item_1,QStringList(QString("力矩载荷(Mz)")));
    QTreeWidgetItem *Child_Item_ni = new QTreeWidgetItem(father_Item_1,QStringList(QString("轴承转速(ni)")));
    QTreeWidgetItem *Child_Item_OR = new QTreeWidgetItem(father_Item_1,QStringList(QString("保持架引导方式(OR)")));
    father_Item_1->addChild(Child_Item_ni);
    father_Item_1->addChild(Child_Item_Fa);
    father_Item_1->addChild(Child_Item_Fr);
    father_Item_1->addChild(Child_Item_My);
    father_Item_1->addChild(Child_Item_Mz);
    father_Item_1->addChild(Child_Item_OR);
    //添加子节点_2
    QTreeWidgetItem *Child_Item_Z = new QTreeWidgetItem(father_Item_2,QStringList(QString("钢球个数(Z)")));
    QTreeWidgetItem *Child_Item_D = new QTreeWidgetItem(father_Item_2,QStringList(QString("钢球直径(D)")));
    QTreeWidgetItem *Child_Item_dm = new QTreeWidgetItem(father_Item_2,QStringList(QString("内圈直径(dm)")));
    QTreeWidgetItem *Child_Item_alpha0 = new QTreeWidgetItem(father_Item_2,QStringList(QString("初始接触角")));
    QTreeWidgetItem *Child_Item_fi = new QTreeWidgetItem(father_Item_2,QStringList(QString("内圈沟渠率半径系数")));
    QTreeWidgetItem *Child_Item_fe = new QTreeWidgetItem(father_Item_2,QStringList(QString("外圈沟渠率半径系数")));
    QTreeWidgetItem *Child_Item_Cp = new QTreeWidgetItem(father_Item_2,QStringList(QString("保持架兜孔间隙")));
    QTreeWidgetItem *Child_Item_Cg = new QTreeWidgetItem(father_Item_2,QStringList(QString("保持架引导间隙")));
    father_Item_2->addChild(Child_Item_Z);
    father_Item_2->addChild(Child_Item_D);
    father_Item_2->addChild(Child_Item_dm);
    father_Item_2->addChild(Child_Item_alpha0);
    father_Item_2->addChild(Child_Item_fi);
    father_Item_2->addChild(Child_Item_fe);
    father_Item_2->addChild(Child_Item_Cp);
    father_Item_2->addChild(Child_Item_Cg);
    //添加子节点_3
    //QTreeWidgetItem *Child_Item_rb = new QTreeWidgetItem(father_Item_3,QStringList(QString("滚动体/内外圆")));
    //QTreeWidgetItem *Child_Item_holder = new QTreeWidgetItem(father_Item_3,QStringList(QString("保持架")));
    QTreeWidgetItem *Child_Item_rho = new QTreeWidgetItem(father_Item_3,QStringList(QString("滚动体材料密度")));
    QTreeWidgetItem *Child_Item_E = new QTreeWidgetItem(father_Item_3,QStringList(QString("滚动体弹性模量")));
    QTreeWidgetItem *Child_Item_v = new QTreeWidgetItem(father_Item_3,QStringList(QString("滚动体泊松比")));
    QTreeWidgetItem *Child_Item_rhoc = new QTreeWidgetItem(father_Item_3,QStringList(QString("保持架材料密度")));
    QTreeWidgetItem *Child_Item_Ec = new QTreeWidgetItem(father_Item_3,QStringList(QString("保持架弹性模量")));
    QTreeWidgetItem *Child_Item_vc = new QTreeWidgetItem(father_Item_3,QStringList(QString("保持架泊松比")));
    //father_Item_3->addChild(Child_Item_rb);
    father_Item_3->addChild(Child_Item_E);
    father_Item_3->addChild(Child_Item_v);
    father_Item_3->addChild(Child_Item_rho);
    //father_Item_3->addChild(Child_Item_holder);
    father_Item_3->addChild(Child_Item_Ec);
    father_Item_3->addChild(Child_Item_vc);
    father_Item_3->addChild(Child_Item_rhoc);
    //添加子节点_4
    QTreeWidgetItem *Child_Item_T0 = new QTreeWidgetItem(father_Item_4,QStringList(QString("环境温度(T0)")));
    QTreeWidgetItem *Child_Item_n0 = new QTreeWidgetItem(father_Item_4,QStringList(QString("润滑油粘度(η0)")));
    QTreeWidgetItem *Child_Item_alpha = new QTreeWidgetItem(father_Item_4,QStringList(QString("润滑油黏压系数(α)")));
    QTreeWidgetItem *Child_Item_beta = new QTreeWidgetItem(father_Item_4,QStringList(QString("润滑油黏温系数(β)")));
    QTreeWidgetItem *Child_Item_K = new QTreeWidgetItem(father_Item_4,QStringList(QString("润滑油热传导系数(K)")));
    father_Item_4->addChild(Child_Item_T0);
    father_Item_4->addChild(Child_Item_n0);
    father_Item_4->addChild(Child_Item_alpha);
    father_Item_4->addChild(Child_Item_beta);
    father_Item_4->addChild(Child_Item_K);
    //添加子节点_5
    QTreeWidgetItem *Child_Item_h0 = new QTreeWidgetItem(father_Item_5,QStringList(QString("初始步长(h0)")));
    QTreeWidgetItem *Child_Item_kt = new QTreeWidgetItem(father_Item_5,QStringList(QString("步长修正系数(kt)")));
    QTreeWidgetItem *Child_Item_Ferr = new QTreeWidgetItem(father_Item_5,QStringList(QString("力残差(Ferr)")));
    QTreeWidgetItem *Child_Item_Uerr = new QTreeWidgetItem(father_Item_5,QStringList(QString("位移残差(Uerr)")));
    QTreeWidgetItem *Child_Item_T = new QTreeWidgetItem(father_Item_5,QStringList(QString("动力学分析时间(T)")));
    father_Item_5->addChild(Child_Item_h0);
    father_Item_5->addChild(Child_Item_kt);
    father_Item_5->addChild(Child_Item_Ferr);
    father_Item_5->addChild(Child_Item_Uerr);
    father_Item_5->addChild(Child_Item_T);

    ui->treeWidget->expandAll();
    m_sta_simudyn_status = 3; //置3表示当前是动力学分析
}


////公共部分
//关闭窗口终止线程
void RBEvaluation::dealdestroyed()
{
    //if(threadsta->isRunning()==false)
    //{
    //    return;
    //}
    //threadsta->quit();
    //threadsta->wait();

    if(threadsd->isRunning()==false)
    {
        return;
    }
    threadsd->quit();
    threadsd->wait();
}

//接收来自欢迎界面的信号
void RBEvaluation::dealWelcometoMain(int mode_rb)
{
    //this->show();
    m_mode = mode_rb;
    QString str_pixmap;
    switch(m_mode)
    {
    case 1:str_pixmap ="rbpixmap.png" ;break;
    case 2:str_pixmap ="tbpixmap.png" ;break;
    case 3:str_pixmap ="cbpixmap.png" ;break;
    default:break;
    }
    QPixmap *pixmap = new QPixmap(str_pixmap);
    pixmap->scaled(ui->labelpixmap->size(), Qt::KeepAspectRatio);
    ui->labelpixmap->setScaledContents(true);
    ui->labelpixmap->setPixmap(*pixmap);
}



//测试打开QFileDialog,负责查看角接触球轴承计算数据
void RBEvaluation::on_actionstadata_1_triggered()
{
    QString dataopenfile_name = QFileDialog::getOpenFileName(this,"数据文件",".","文本文档(*.txt);;WORD文档(*.doc *.docx);;EXCEL文档(*.xls *.xlsx *.csv);;ALL(*.*)");
    if(!dataopenfile_name.isEmpty())
        {
            //读取qstring最后四位或者五位
            //判断打开的对象是不是txt文件，调用notepad打开
            if(dataopenfile_name.right(4) == ".txt")
            {
                //QProcess *txtprocess = new QProcess();
                //QString notepadpath = "notepad.exe " + dataopenfile_name;   //草了我太牛逼了，试了一下 + 就成功了
                //txtprocess->start(notepadpath);
                //这个直接调用windows启动更加方便
                QDesktopServices::openUrl(QUrl::fromLocalFile(dataopenfile_name));
            }
            //判断打开的对象是不是xls，调用.excel打开
            else if(dataopenfile_name.right(4) == ".xls" || dataopenfile_name.right(5) ==".xlsx"|| dataopenfile_name.right(4) ==".csv")
            {
                QDesktopServices::openUrl(QUrl::fromLocalFile(dataopenfile_name));
            }
            //判断格式，调用word打开word文档
            else if(dataopenfile_name.right(4) == ".doc" || dataopenfile_name.right(5) ==".docx")
            {
                QDesktopServices::openUrl(QUrl::fromLocalFile(dataopenfile_name));
            }
        }
}

//打开图表图片文档
void RBEvaluation::on_actioncharts_triggered()
{
    QString chartsopenfile_name = QFileDialog::getOpenFileName(this,"图表图片",".","图片(*.png *.jpg)");
    QDesktopServices::openUrl(QUrl::fromLocalFile(chartsopenfile_name));
}



//专业画表头
void RBEvaluation::creattablewidgetheaders(QString title,double data,QString unit)
{
    //QTableWidget 表格创建
    //设置为不可编辑状态
    ui->tableWidgetmainwindow->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //规范行列数
    ui->tableWidgetmainwindow->setColumnCount(3);
    ui->tableWidgetmainwindow->setRowCount(1);  //暂时只显示一行
    //设置可见情况
    ui->tableWidgetmainwindow->verticalHeader()->setVisible(false);
    ui->tableWidgetmainwindow->horizontalHeader()->setVisible(true);
    //第一个表头
    QTableWidgetItem *item0 = new QTableWidgetItem();
    item0->setText("变量名称（常用符号）");
    item0->setTextAlignment(Qt::AlignRight |Qt::AlignVCenter);
    ui->tableWidgetmainwindow->setHorizontalHeaderItem(0,item0);
    //第二个水平表头
    QTableWidgetItem *item1 = new QTableWidgetItem();
    item1->setText("值");
    item1->setTextAlignment(Qt::AlignRight |Qt::AlignVCenter);
    ui->tableWidgetmainwindow->setHorizontalHeaderItem(1,item1);
    //第三个水平表头
    QTableWidgetItem *item2 = new QTableWidgetItem();
    item2->setText("单位");
    item2->setTextAlignment(Qt::AlignLeft |Qt::AlignVCenter);
    ui->tableWidgetmainwindow->setHorizontalHeaderItem(2,item2);
    //列宽设置
    ui->tableWidgetmainwindow->setColumnWidth(0,200);
    ui->tableWidgetmainwindow->setColumnWidth(1,100);
    ui->tableWidgetmainwindow->setColumnWidth(2,100);

    //第一列
    QTableWidgetItem *itemFr = new QTableWidgetItem();
    itemFr->setText(title);
    itemFr->setTextAlignment(Qt::AlignRight |Qt::AlignVCenter);
    ui->tableWidgetmainwindow->setItem(0,0,itemFr);

    //第二列
    ui->tableWidgetmainwindow->setItem(0,1,new QTableWidgetItem(QString::number(data)));
    ui->tableWidgetmainwindow->item(0,1)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

    //第三列
    ui->tableWidgetmainwindow->setItem(0,2,new QTableWidgetItem(unit));
}

//处理Tab关闭事件的槽函数
void RBEvaluation::TabClose(int index)
{
    //获取各个窗口当前的index位置，这个可与index吻合
    m_tabWidgetworkingarea_index_staoutput = ui->tabWidgetworkingarea->indexOf(m_tabstaoutputdyn);
    m_tabWidgetworkingarea_index_stacharts = ui->tabWidgetworkingarea->indexOf(m_tabstachartsdyn);
    m_tabWidgetworkingarea_index_simudynoutput = ui->tabWidgetworkingarea->indexOf(m_tabsimudynoutptudyn);
    m_tabWidgetworkingarea_index_simudyncharts = ui->tabWidgetworkingarea->indexOf(m_tabsimudynchartsdyn);
    m_tabWidgetworkingarea_index_openGL_3D = ui->tabWidgetworkingarea->indexOf(m_tabopenGL_3D);
    m_tabWidgetworkingarea_index_openGL_Cloud = ui->tabWidgetworkingarea->indexOf(m_tabopenGL_Cloud);


    //根据不同的被点下的情况,但是这里的index是实时判断，二者无法吻合
    if(index==m_tabWidgetworkingarea_index_staoutput)
    {
       flag_staoutput = false; //标志为恢复
   }
   else if(index == m_tabWidgetworkingarea_index_stacharts)
   {
       flag_stacharts = false; //标志为恢复
   }
    else if(index == m_tabWidgetworkingarea_index_simudynoutput)
    {
        flag_simudynoutput = false; //标志为恢复
    }
    else if(index == m_tabWidgetworkingarea_index_simudyncharts)
    {
        flag_simudyncharts = false; //标志为恢复
    }
    else if(index == m_tabWidgetworkingarea_index_openGL_3D)
    {
        flag_openGL_3D = false; //标志为恢复
    }
    else if(index == m_tabWidgetworkingarea_index_openGL_Cloud)
    {
        flag_openGL_Cloud = false; //标志为恢复
    }
    //删除窗口
    ui->tabWidgetworkingarea->removeTab(index);
}



//QWidgettree itemclicked响应
void RBEvaluation::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    //如果是静力学计算
    if(m_sta_simudyn_status == 1)
    {
        //获得父节点
        QTreeWidgetItem *parent = item->parent();
        //如果是父节点，则它自己没有父节点，返回
        if(parent == NULL)
            return;
        //普通节点有父节点值，获取行号
        int row = parent->indexOfChild(item);
        //获取父节点名字,第0列column的
        QString mainrowname = parent->text(0);
        //判断点的是哪一个目录
        if(mainrowname == "工况条件")
        {
            switch(row)
            {
                case 0:creattablewidgetheaders("径向载荷(Fr)",Fr,"N");break;
                case 1:creattablewidgetheaders("轴向载荷(Fr)",Fa,"N");break;
                case 2:creattablewidgetheaders("力矩(M)",M,"N*mm");break;
                default:break;
            }
        }
        else if(mainrowname == "结构参数")
        {
            switch(row)
            {
                case 0:creattablewidgetheaders("钢球个数(Z)",z," ");break;
                case 1:creattablewidgetheaders("钢球直径(D)",D,"mm");break;
                case 2:creattablewidgetheaders("内圈直径(dm)",dm,"mm");break;
                case 3:creattablewidgetheaders("初始接触角",alpha0,"°");break;
                case 4:creattablewidgetheaders("内圈沟渠率半径系数",fi," ");break;
                case 5:creattablewidgetheaders("外圈沟渠率半径系数",fe," ");break;
                default:break;
            }
        }

    }
    //如果是拟动力学计算
    else if(m_sta_simudyn_status == 2)
    {
        //获得父节点
        QTreeWidgetItem *parent = item->parent();
        //如果是父节点，则它自己没有父节点，返回
        if(parent == NULL)
            return;
        //普通节点有父节点值，获取行号
        int row = parent->indexOfChild(item);
        //获取父节点名字,第0列column的
        QString mainrowname = parent->text(0);
        //判断点的是哪一个目录
        if(mainrowname == "工况条件")
        {
            switch(row)
            {
                case 0:creattablewidgetheaders("径向载荷(Fr)",Frsd,"N");break;
                case 1:creattablewidgetheaders("轴向载荷(Fa)",Fasd,"N");break;
                case 2:creattablewidgetheaders("力矩(M)",Msd,"N*mm");break;
                case 3:creattablewidgetheaders("内圈转速(ni)",nisd,"rpm");break;
                default:break;
            }
        }
        else if(mainrowname == "结构参数")
        {
            switch(row)
            {
                case 0:creattablewidgetheaders("钢球个数(Z)",zsd," ");break;
                case 1:creattablewidgetheaders("钢球直径(D)",Dsd,"mm");break;
                case 2:creattablewidgetheaders("内圈直径(dm)",dmsd,"mm");break;
                case 3:creattablewidgetheaders("初始接触角",alpha0sd,"°");break;
                case 4:creattablewidgetheaders("内圈沟渠率半径系数",fisd," ");break;
                case 5:creattablewidgetheaders("外圈沟渠率半径系数",fesd," ");break;
                default:break;
            }
        }
        else if(mainrowname == "材料参数")
        {
            switch(row)
            {
                case 0:creattablewidgetheaders("钢球材料密度",rhosd,"kg/m^3");break;
                case 1:creattablewidgetheaders("弹性模量",Esd,"N/mm^2");break;
                case 2:creattablewidgetheaders("泊松比",vsd," ");break;
                default:break;
            }
        }
        else if(mainrowname == "引导方式")
        {
            switch(row)
            {
                case 0:creattablewidgetheaders("引导方式",ORsd," ");break;
                default:break;
            }
        }
        else if(mainrowname == "润滑剂/摩擦相关参数")
        {
            switch(row)
            {
                //case 0:creattablewidgetheaders("径向载荷(Fr)",Frsd,"N");break;
                //case 1:creattablewidgetheaders("轴向载荷(Fr)",Fasd,"N");break;
                //case 2:creattablewidgetheaders("力矩(M)",Msd,"N*mm");break;
                //case 3:creattablewidgetheaders("内圈转速(ni)",nisd,"rpm");break;
                case 4:creattablewidgetheaders("摩擦系数(μ)",o2sd," ");break;
                default:break;
            }
        }
        else if(mainrowname == "数值计算相关参数")
        {
            switch(row)
            {
                case 0:creattablewidgetheaders("位移修正系数(ωD)",osd," ");break;
                case 1:creattablewidgetheaders("姿态角修正系数(ωγ)",o1sd," ");break;
                case 2:creattablewidgetheaders("规定迭代误差",errosd," ");break;
                case 3:creattablewidgetheaders("极限迭代次数",numberssd," ");break;
                default:break;
            }
        }
    }
    //如果是动力学计算
    else if(m_sta_simudyn_status == 3)
    {
        //获得父节点
        QTreeWidgetItem *parent = item->parent();
        //如果是父节点，则它自己没有父节点，返回
        if(parent == NULL)
            return;
        //普通节点有父节点值，获取行号
        int row = parent->indexOfChild(item);
        //获取父节点名字,第0列column的
        QString mainrowname = parent->text(0);
        //判断点的是哪一个目录
        if(mainrowname == "工况条件")
        {
            switch(row)
            {
                case 0:creattablewidgetheaders("径向载荷(Fr)",Fr_dyn,"N");break;
                case 1:creattablewidgetheaders("轴向载荷(Fr)",Fa_dyn,"N");break;
                case 2:creattablewidgetheaders("力矩载荷(My)",My_dyn,"N*mm");break;
                case 3:creattablewidgetheaders("力矩载荷(Mz)",Mz_dyn,"N*mm");break;
                case 4:creattablewidgetheaders("内圈转速(ni)",ni_dyn,"rpm");break;
                case 5:creattablewidgetheaders("保持架引导方式(OR)",OR_dyn," ");break;
                default:break;
            }
        }
        else if(mainrowname == "结构参数")
        {
            switch(row)
            {
                case 0:creattablewidgetheaders("钢球个数(Z)",z_dyn," ");break;
                case 1:creattablewidgetheaders("钢球直径(D)",D_dyn,"mm");break;
                case 2:creattablewidgetheaders("内圈直径(dm)",dm_dyn,"mm");break;
                case 3:creattablewidgetheaders("初始接触角",alpha0_dyn,"°");break;
                case 4:creattablewidgetheaders("内圈沟渠率半径系数",fi_dyn," ");break;
                case 5:creattablewidgetheaders("外圈沟渠率半径系数",fe_dyn," ");break;
                case 6:creattablewidgetheaders("保持架兜孔间隙",Cp_dyn," ");break;
                case 7:creattablewidgetheaders("保持架引导间隙",Cg_dyn," ");break;
                default:break;
            }
        }
        else if(mainrowname == "材料参数")
        {
            switch(row)
            {
                case 0:creattablewidgetheaders("滚动体材料密度",rho_dyn,"kg/m^3");break;
                case 1:creattablewidgetheaders("滚动体弹性模量",E_dyn,"N/mm^2");break;
                case 2:creattablewidgetheaders("滚动体泊松比",v_dyn," ");break;
                case 3:creattablewidgetheaders("保持架材料密度",rhoc_dyn,"kg/m^3");break;
                case 4:creattablewidgetheaders("保持架弹性模量",Ec_dyn,"N/mm^2");break;
                case 5:creattablewidgetheaders("保持架泊松比",vc_dyn," ");break;
                default:break;
            }
        }
        else if(mainrowname == "润滑剂/摩擦相关参数")
        {
            switch(row)
            {
                case 0:creattablewidgetheaders("环境温度(T0)",T0_dyn,"°C");break;
                case 1:creattablewidgetheaders("润滑油粘度(η0)",n0_dyn,"Pa·s");break;
                case 2:creattablewidgetheaders("润滑油黏压系数(α)",alpha_dyn,"Pa-1");break;
                case 3:creattablewidgetheaders("润滑油粘温系数(β)",beta_dyn,"K-1");break;
                case 4:creattablewidgetheaders("润滑油热传导系数(K)",K_dyn,"N/(s·K)");break;
                default:break;
            }
        }
        else if(mainrowname == "数值计算相关参数")
        {
            switch(row)
            {
                case 0:creattablewidgetheaders("初始步长(h0)",h0_dyn,"s");break;
                case 1:creattablewidgetheaders("步长修正参数(kt)",kt_dyn," ");break;
                case 2:creattablewidgetheaders("力残差(Ferr)",Ferr_dyn,"N");break;
                case 3:creattablewidgetheaders("位移残差(Uerr)",uerr_dyn,"mm");break;
                case 4:creattablewidgetheaders("动力学分析时间(T)",T_dyn,"s");break;
                default:break;
            }
        }
    }
}

//界面右侧的编辑按钮
void RBEvaluation::on_pushButtoneditable_clicked()
{
    if(m_sta_simudyn_status == 1)
    {
        stainput.show();
    }
    else if(m_sta_simudyn_status == 2)
    {
        simudyninput.show();
    }
    else if(m_sta_simudyn_status == 3)
    {
        dyninput.show();
    }
}

void RBEvaluation::on_actionabout_triggered()
{

}


////3D部分

//三维计算
void RBEvaluation::on_actionThreeD_triggered()
{
    SD_3D_Input->show();
}

//三维测试部分
void RBEvaluation::on_action3D_triggered()
{
    //测试 显示三维绘图窗口
    //indiaopengl->show();
    //判断标志位是否已经被按下一次了
    if(flag_openGL_3D == false)    //如果没被按下
    {
        ////标志为设置
        flag_openGL_3D = true;

        ////读取文档
        m_input3D_name = QFileDialog::getOpenFileName(this,"读取文件",".","应力计算结果输入文件(*.3Ddata)");
        //把要读取的文件名发送给opneGL窗口
        emit FilenameToThreeD(m_input3D_name);

        ////如果不存在该标签页，则创建一个新的标签页
        m_tabopenGL_3D = new QWidget();
        int currentindex = ui->tabWidgetworkingarea->addTab(m_tabopenGL_3D,"三维分析结果显示");
        ui->tabWidgetworkingarea->setCurrentIndex(currentindex);
        ui->tabWidgetworkingarea->setTabsClosable(true);    //设置为可关闭的

        //获取工作界面的长和宽
        qreal tabopenGL_3D_width,tabopenGL_3D_height;
        tabopenGL_3D_width = ui->tabWidgetworkingarea->geometry().width();
        tabopenGL_3D_height = ui->tabWidgetworkingarea->geometry().height();

        indiaopengl->setParent(m_tabopenGL_3D);
        indiaopengl->setGeometry(0,0,tabopenGL_3D_width,tabopenGL_3D_height);
        indiaopengl->show();

        ////把QOpenGLWindow通过套娃的方式写进来
        ////测试把QOpenGLWindow写进QWidget里面，用creatWindowContainer
        //QWindow *window = new QWindow();
        ////第2层套娃，QWindow套在QWidget
        //QWidget *WindowContainer = QWidget::createWindowContainer(window);
        ////第1层套娃，QWidget套在QWidget上
        //WindowContainer->setParent(m_tabopenGL_3D);
        //WindowContainer->setGeometry(0,0,tabopenGL_3D_width,tabopenGL_3D_height);
        //
        //qreal WindowContainer_width,WindowContainer_height;
        //WindowContainer_width = WindowContainer->geometry().width();
        //WindowContainer_height = WindowContainer->geometry().height();
        //window->setGeometry(0,0,WindowContainer_width,WindowContainer_height);
        //
        //////第3层套娃，QOpenGLWindow套在QWindow上
        //indiaopengl->setParent(window);
        //qreal window_width,window_height;
        //window_width = window->geometry().width();
        //window_height = window->geometry().height();
        //qreal ratio = 0.9;
        //indiaopengl->setGeometry(0,0,window_width*ratio,window_height*ratio);
        //
        //WindowContainer->show();
        //window->show();
        //indiaopengl->show();
    }

    //如果存在，则发出警告
    else if(flag_openGL_3D == true)
    {
        SetMessageBoxSize msgBox;   //自己写了一个类，可以设置size的继承于QMessageBox的类
        msgBox.AutosetSize(300,100);
        msgBox.setIcon(QMessageBox::Warning); //设置类型
        msgBox.setWindowTitle("警告");
        msgBox.setText("三维分析结果结果已存在");
        //msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}


//云图二继承与openGLWindow
void RBEvaluation::on_actioncloud_2_triggered()
{
    //cloudtest->show();
    //判断标志位是否已经被按下一次了
    if(flag_openGL_Cloud == false)    //如果没被按下
    {
        ////标志为设置
        flag_openGL_Cloud = true;

        ////读取文档
        m_inputCloud_name = QFileDialog::getOpenFileName(this,"读取文件",".","云图计算结果输入文件(*.Clouddata)");
        //把要读取的文件名发送给opneGL窗口
        emit FilenameToCloud(m_inputCloud_name);

        ////开放视图
        //如果不存在该标签页，则创建一个新的标签页
        m_tabopenGL_Cloud = new QWidget();
        int currentindex = ui->tabWidgetworkingarea->addTab(m_tabopenGL_Cloud,"云图显示");
        ui->tabWidgetworkingarea->setCurrentIndex(currentindex);
        ui->tabWidgetworkingarea->setTabsClosable(true);    //设置为可关闭的

        ////将图表写进来
        cloudtest->setParent(m_tabopenGL_Cloud);   //这里QOpenGLWindow改成了QOoenGLWidget可以直接继承
        ////获取长和宽
        qreal tabopenGL_Cloud_width,tabopenGL_Cloud_height;
        tabopenGL_Cloud_width = ui->tabWidgetworkingarea->geometry().width();
        tabopenGL_Cloud_height = ui->tabWidgetworkingarea->geometry().height();

        //////显示在左上角
        cloudtest->setGeometry(0,0,tabopenGL_Cloud_width,tabopenGL_Cloud_height);
        cloudtest->show();

        ////把QOpenGLWindow通过套娃的方式写进来
        //测试把QOpenGLWindow写进QWidget里面，用creatWindowContainer
        //QWindow *window = new QWindow();
        ////第2层套娃，QWindow套在QWidget
        //QWidget *WindowContainer = QWidget::createWindowContainer(window);
        ////第1层套娃，QWidget套在QWidget上
        //WindowContainer->setParent(m_tabopenGL_Cloud);
        //WindowContainer->setGeometry(0,0,tabopenGL_Cloud_width,tabopenGL_Cloud_height);
        //
        //qreal WindowContainer_width,WindowContainer_height;
        //WindowContainer_width = WindowContainer->geometry().width();
        //WindowContainer_height = WindowContainer->geometry().height();
        //window->setGeometry(0,0,WindowContainer_width,WindowContainer_height);
        //
        //////第3层套娃，QOpenGLWindow套在QWindow上
        //cloudtest->setParent(window);
        //qreal window_width,window_height;
        //window_width = window->geometry().width();
        //window_height = window->geometry().height();
        //qreal ratio = 0.9;
        //cloudtest->setGeometry(0,0,window_width*ratio,window_height*ratio);
        //
        //WindowContainer->show();
        //window->show();
        //cloudtest->show();
    }

    //如果存在，则发出警告
    else if(flag_openGL_Cloud == true)
    {
        SetMessageBoxSize msgBox;   //自己写了一个类，可以设置size的继承于QMessageBox的类
        msgBox.AutosetSize(300,100);
        msgBox.setIcon(QMessageBox::Warning); //设置类型
        msgBox.setWindowTitle("警告");
        msgBox.setText("云图分析结果结果已存在");
        //msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}



