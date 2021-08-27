#include "simudyn_charts.h"
#include "ui_simudyn_charts.h"

//为了使用比较大小函数，包含以下头文件和内存拓展
#include<math.h>
#include<QDebug>
using namespace std;

//定义变量储存最大最小数据,应该重新命名变量的，但是太繁琐了所以就复制过来了
double Salphaeoutputc[100],sdmaxalphaec;
double Salphaioutputc[100],sdmaxalphaic;
double SQeoutputc[100],sdmaxqec;
double SQioutputc[100],sdmaxqic;
double Swcoutputc[100],sdmaxwcc;
double Swboutputc[100],sdmaxwbc;
double SMgoutputc[100],sdmaxMgc;
double SFcoutputc[100],sdmaxFcc;
double Suoutputc[100],sdmaxuc;
double SRioutputc[100],sdmaxSRic;
double SReoutputc[100],sdmaxSRec;
double Slamdaoutputc[100],sdmaxlamdac;

double sdminalphae;
double sdminalphai;
double sdminqe;
double sdminqi;
double sdminwc;
double sdminwb;
double sdminMg;
double sdminFc;
double sdminu;
double sdminSRi;
double sdminSRe;
double sdminlamda;


SimuDyn_Charts::SimuDyn_Charts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimuDyn_Charts)
{
    ui->setupUi(this);

    //嵌入主窗口
    setWindowFlag(Qt::CustomizeWindowHint);
    hide();

    //设置默认界面为第一页
    ui->tabsdinclude->setCurrentWidget(ui->tabsdgroup1);
    //设置每一个子页面
    ui->tabsdsub1->setCurrentWidget(ui->tabsdalphai);
    ui->tabsdsub2->setCurrentWidget(ui->tabsdQi);
    ui->tabsdsub3->setCurrentWidget(ui->tabsdwb);
}

SimuDyn_Charts::~SimuDyn_Charts()
{
    delete ui;
}

void SimuDyn_Charts::sddealcharts(int z, QVector<double> vecsdlamdat, QVector<double> vecsdalphaet, QVector<double> vecsdalphait, QVector<double> vecsdut, QVector<double> vecsdQet, QVector<double> vecsdQit, QVector<double> vecsdFct, QVector<double> vecsdMgt, QVector<double> vecsdwbt, QVector<double> vecsdwct, QVector<double> vecsdSRet, QVector<double> vecsdSRit)
{
    static int j;
    for(j=0;j<z;j++)
    {
        Salphaeoutputc[j]=vecsdalphaet[j];
        Salphaioutputc[j]=vecsdalphait[j];
        SQeoutputc[j]=vecsdQet[j];
        SQioutputc[j]=vecsdQit[j];
        Swcoutputc[j]=vecsdwct[j];
        Swboutputc[j]=vecsdwbt[j];
        SMgoutputc[j]=vecsdMgt[j];
        SFcoutputc[j]=vecsdFct[j];
        Suoutputc[j]=vecsdut[j];
        SRioutputc[j]=vecsdSRit[j];
        SReoutputc[j]=vecsdSRet[j];
        Slamdaoutputc[j]=vecsdlamdat[j];
    }

    //找到数组中最大最小值
    sdmaxalphaec = *max_element(Salphaeoutputc,Salphaeoutputc+z);
    sdmaxalphaic = *max_element(Salphaioutputc,Salphaioutputc+z);
    sdmaxqec=*max_element(SQeoutputc,SQeoutputc+z);
    sdmaxqic=*max_element(SQioutputc,SQioutputc+z);
    sdmaxwcc=*max_element(Swcoutputc,Swcoutputc+z);
    sdmaxwbc=*max_element(Swboutputc,Swboutputc+z);
    sdmaxMgc=*max_element(SMgoutputc,SMgoutputc+z);
    sdmaxFcc=*max_element(SFcoutputc,SFcoutputc+z);
    sdmaxuc=*max_element(Suoutputc,Suoutputc+z);
    sdmaxSRic=*max_element(SRioutputc,SRioutputc+z);
    sdmaxSRec=*max_element(SReoutputc,SReoutputc+z);
    sdmaxlamdac=*max_element(Slamdaoutputc,Slamdaoutputc+z);

    sdminalphae = *min_element(Salphaeoutputc,Salphaeoutputc+z);
    sdminalphai = *min_element(Salphaioutputc,Salphaioutputc+z);
    sdminqe=*min_element(SQeoutputc,SQeoutputc+z);
    sdminqi=*min_element(SQioutputc,SQioutputc+z);
    sdminwc=*min_element(Swcoutputc,Swcoutputc+z);
    sdminwb=*min_element(Swboutputc,Swboutputc+z);
    sdminMg=*min_element(SMgoutputc,SMgoutputc+z);
    sdminFc=*min_element(SFcoutputc,SFcoutputc+z);
    sdminu=*min_element(Suoutputc,Suoutputc+z);
    sdminSRi=*min_element(SRioutputc,SRioutputc+z);
    sdminSRe=*min_element(SReoutputc,SReoutputc+z);
    sdminlamda=*min_element(Slamdaoutputc,Slamdaoutputc+z);


    //建立cahrt
    m_sdchartlamda = new QChart();
    m_sdchartalphae = new QChart();
    m_sdchartalphai = new QChart();
    m_sdchartqe = new QChart();
    m_sdchartqi = new QChart();
    m_sdchartwc = new QChart();
    m_sdchartwb = new QChart();
    m_sdchartSre = new QChart();
    m_sdchartSri = new QChart();
    m_sdchartFc = new QChart();
    m_sdchartMg = new QChart();
    m_sdchartu = new QChart();
    //建立chart中一会儿要用到的线
    QSplineSeries *staserieslamda = new QSplineSeries();
    QSplineSeries *staseriesalphae = new QSplineSeries();
    QSplineSeries *staseriesalphai = new QSplineSeries();
    QSplineSeries *staseriesqe = new QSplineSeries();
    QSplineSeries *staseriesqi = new QSplineSeries();
    QSplineSeries *staserieswc = new QSplineSeries();
    QSplineSeries *staserieswb = new QSplineSeries();
    QSplineSeries *staseriessre = new QSplineSeries();
    QSplineSeries *staseriessri = new QSplineSeries();
    QSplineSeries *staseriesFc = new QSplineSeries();
    QSplineSeries *staseriesMg = new QSplineSeries();
    QSplineSeries *staseriesu = new QSplineSeries();


    static int i;
    for(i=0;i<z;i++)
    {
        //根据需要画线
        staserieslamda->append(i+1,Slamdaoutputc[i]);
        staseriesalphae->append(i+1,Salphaeoutputc[i]);
        staseriesalphai->append(i+1,Salphaioutputc[i]);
        staseriesqe->append(i+1,SQeoutputc[i]);
        staseriesqi->append(i+1,SQioutputc[i]);
        staserieswc->append(i+1,Swcoutputc[i]);
        staserieswb->append(i+1,Swboutputc[i]);
        staseriessre->append(i+1,SReoutputc[i]);
        staseriessri->append(i+1,SRioutputc[i]);
        staseriesFc->append(i+1,SFcoutputc[i]);
        staseriesMg->append(i+1,SMgoutputc[i]);
        staseriesu->append(i+1,Suoutputc[i]);
    }

    //给线命名
    /*
    staserieslamda->setName("姿态角-滚珠个数");
    staseriesalphae->setName("外圈接触角-滚珠个数");
    staseriesalphai->setName("内圈接触角-滚珠个数");
    staseriesqe->setName("外圈接触载荷-滚珠个数");
    staseriesqi->setName("内圈接触载荷-滚珠个数");
    staserieswc->setName("滚珠自转角速度-滚珠个数");
    staserieswb->setName("滚珠公转角速度-滚珠个数");
    staseriessre->setName("滚珠与外滚道旋滚比-滚珠个数");
    staseriessri->setName("滚珠与内滚道旋滚比-滚珠个数");
    staseriesFc->setName("离心力-滚珠个数");
    staseriesMg->setName("陀螺力矩-滚珠个数");
    staseriesu->setName("摩擦系数-滚珠个数");
    */

    //自定义线段的颜色
    /*
    staserieslamda->setColor(QColor(0,0,250));
    staseriesalphae->setColor(QColor(0,0,250));
    staseriesalphai->setColor(QColor(0,0,250));
    staseriesqe->setColor(QColor(0,0,250));
    staseriesqi->setColor(QColor(0,0,250));
    staserieswc->setColor(QColor(0,0,250));
    staserieswb->setColor(QColor(0,0,250));
    staseriessre->setColor(QColor(0,0,250));
    staseriessri->setColor(QColor(0,0,250));
    staseriesFc->setColor(QColor(0,0,250));
    staseriesMg->setColor(QColor(0,0,250));
    staseriesu->setColor(QColor(0,0,250));
    */
    //曲线粗细
    QPen penlinesd;
    penlinesd.setStyle(Qt::SolidLine);
    penlinesd.setWidth(2);    //2像素点线宽
    penlinesd.setColor(Qt::blue);

    //曲线粗也设计一下
    staserieslamda->setPen(penlinesd);
    staseriesalphae->setPen(penlinesd);
    staseriesalphai->setPen(penlinesd);
    staseriesqe->setPen(penlinesd);
    staseriesqi->setPen(penlinesd);
    staserieswc->setPen(penlinesd);
    staserieswb->setPen(penlinesd);
    staseriessre->setPen(penlinesd);
    staseriessri->setPen(penlinesd);
    staseriesFc->setPen(penlinesd);
    staseriesMg->setPen(penlinesd);
    staseriesu->setPen(penlinesd);


    //开始定义坐标轴
    QValueAxis *staaxisxlamda = new QValueAxis;
    QValueAxis *staaxisylamda = new QValueAxis;
    QValueAxis *staaxisxae = new QValueAxis;
    QValueAxis *staaxisyae = new QValueAxis;
    QValueAxis *staaxisxai = new QValueAxis;
    QValueAxis *staaxisyai = new QValueAxis;
    QValueAxis *staaxisxqe = new QValueAxis;
    QValueAxis *staaxisyqe = new QValueAxis;
    QValueAxis *staaxisxqi = new QValueAxis;
    QValueAxis *staaxisyqi = new QValueAxis;
    QValueAxis *staaxisxsre = new QValueAxis;
    QValueAxis *staaxisysre = new QValueAxis;
    QValueAxis *staaxisxsri = new QValueAxis;
    QValueAxis *staaxisysri = new QValueAxis;
    QValueAxis *staaxisxu = new QValueAxis;
    QValueAxis *staaxisyu = new QValueAxis;
    QValueAxis *staaxisxfc = new QValueAxis;
    QValueAxis *staaxisyfc = new QValueAxis;
    QValueAxis *staaxisxmg = new QValueAxis;
    QValueAxis *staaxisymg = new QValueAxis;
    QValueAxis *staaxisxwc = new QValueAxis;
    QValueAxis *staaxisywc = new QValueAxis;
    QValueAxis *staaxisxwb = new QValueAxis;
    QValueAxis *staaxisywb = new QValueAxis;

    //给坐标轴设置线宽
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);    //2像素点线宽
    pen.setColor(Qt::black);

    staaxisxlamda->setLinePen(pen);
    staaxisxlamda->setLineVisible(true);
    staaxisylamda->setLinePen(pen);
    staaxisylamda->setLineVisible(true);

    staaxisxae->setLinePen(pen);
    staaxisxae->setLineVisible(true);
    staaxisyae->setLinePen(pen);
    staaxisyae->setLineVisible(true);

    staaxisxai->setLinePen(pen);
    staaxisxai->setLineVisible(true);
    staaxisyai->setLinePen(pen);
    staaxisyai->setLineVisible(true);

    staaxisxqe->setLinePen(pen);
    staaxisxqe->setLineVisible(true);
    staaxisyqe->setLinePen(pen);
    staaxisyqe->setLineVisible(true);

    staaxisxqi->setLinePen(pen);
    staaxisxqi->setLineVisible(true);
    staaxisyqi->setLinePen(pen);
    staaxisyqi->setLineVisible(true);

    staaxisxsre->setLinePen(pen);
    staaxisxsre->setLineVisible(true);
    staaxisysre->setLinePen(pen);
    staaxisysre->setLineVisible(true);

    staaxisxsri->setLinePen(pen);
    staaxisxsri->setLineVisible(true);
    staaxisysri->setLinePen(pen);
    staaxisysri->setLineVisible(true);

    staaxisxu->setLinePen(pen);
    staaxisxu->setLineVisible(true);
    staaxisyu->setLinePen(pen);
    staaxisyu->setLineVisible(true);

    staaxisxfc->setLinePen(pen);
    staaxisxfc->setLineVisible(true);
    staaxisyfc->setLinePen(pen);
    staaxisyfc->setLineVisible(true);

    staaxisxmg->setLinePen(pen);
    staaxisxmg->setLineVisible(true);
    staaxisymg->setLinePen(pen);
    staaxisymg->setLineVisible(true);

    staaxisxwc->setLinePen(pen);
    staaxisxwc->setLineVisible(true);
    staaxisywc->setLinePen(pen);
    staaxisywc->setLineVisible(true);

    staaxisxwb->setLinePen(pen);
    staaxisxwb->setLineVisible(true);
    staaxisywb->setLinePen(pen);
    staaxisywb->setLineVisible(true);

    //给坐标轴定义范围
    staaxisxlamda->setRange(1,z);
    staaxisxae->setRange(1,z);
    staaxisxai->setRange(1,z);
    staaxisxqe->setRange(1,z);
    staaxisxqi->setRange(1,z);
    staaxisxsre->setRange(1,z);
    staaxisxsri->setRange(1,z);
    staaxisxu->setRange(1,z);
    staaxisxfc->setRange(1,z);
    staaxisxmg->setRange(1,z);
    staaxisxwc->setRange(1,z);
    staaxisxwb->setRange(1,z);

    //用找到数组中最大最小元素的方法来设置范围
    staaxisylamda->setRange(calculatemin(sdminlamda,sdmaxlamdac),calculatemax(sdminlamda,sdmaxlamdac));
    staaxisyae->setRange(calculatemin(sdminalphae,sdmaxalphaec),calculatemax(sdminalphae,sdmaxalphaec));
    staaxisyai->setRange(calculatemin(sdminalphai,sdmaxalphaic),calculatemax(sdminalphai,sdmaxalphaic));
    staaxisyqe->setRange(calculatemin(sdminqe,sdmaxqec),calculatemax(sdminqe,sdmaxqec));
    staaxisyqi->setRange(calculatemin(sdminqi,sdmaxqic),calculatemax(sdminqi,sdmaxqic));
    staaxisysre->setRange(calculatemin(sdminSRe,sdmaxSRec),calculatemax(sdminSRe,sdmaxSRec));
    staaxisysri->setRange(calculatemin(sdminSRi,sdmaxSRic),calculatemax(sdminSRi,sdmaxSRic));
    staaxisyu->setRange(calculatemin(sdminu,sdmaxuc),calculatemax(sdminu,sdmaxuc));
    staaxisyfc->setRange(calculatemin(sdminFc,sdmaxFcc),calculatemax(sdminFc,sdmaxFcc));
    staaxisymg->setRange(calculatemin(sdminMg,sdmaxMgc),calculatemax(sdminMg,sdmaxMgc));
    staaxisywc->setRange(calculatemin(sdminwc,sdmaxwcc),calculatemax(sdminwc,sdmaxwcc));
    staaxisywb->setRange(calculatemin(sdminwb,sdmaxwbc),calculatemax(sdminwb,sdmaxwbc));

    //设置坐标轴要有几个刻度
    staaxisxlamda->setTickCount(z);
    staaxisxae->setTickCount(z);
    staaxisxai->setTickCount(z);
    staaxisxqe->setTickCount(z);
    staaxisxqi->setTickCount(z);
    staaxisxsre->setTickCount(z);
    staaxisxsri->setTickCount(z);
    staaxisxu->setTickCount(z);
    staaxisxfc->setTickCount(z);
    staaxisxmg->setTickCount(z);
    staaxisxwc->setTickCount(z);
    staaxisxwb->setTickCount(z);

    //设置y轴的小刻度
    staaxisyqe->setMinorTickCount(4);
    staaxisyqi->setMinorTickCount(4);
    staaxisysre->setMinorTickCount(4);
    staaxisysri->setMinorTickCount(4);
    staaxisyfc->setMinorTickCount(4);
    staaxisymg->setMinorTickCount(4);
    staaxisywc->setMinorTickCount(4);
    staaxisywb->setMinorTickCount(4);




    //使得坐标只显示不带小数点的整数   //方便放大缩小功能
    //staaxisxlamda->setLabelFormat("%d");
    //staaxisxae->setLabelFormat("%d");
    //staaxisxai->setLabelFormat("%d");
    //staaxisxqe->setLabelFormat("%d");
    //staaxisxqi->setLabelFormat("%d");
    //staaxisxsre->setLabelFormat("%d");
    //staaxisxsri->setLabelFormat("%d");
    //staaxisxu->setLabelFormat("%d");
    //staaxisxfc->setLabelFormat("%d");
    //staaxisxmg->setLabelFormat("%d");
    //staaxisxwc->setLabelFormat("%d");
    //staaxisxwb->setLabelFormat("%d");

    //设置纵坐标精确度
    staaxisylamda->setLabelFormat(accuracy(sdminlamda,sdmaxlamdac));
    staaxisyae->setLabelFormat(accuracy(sdminalphae,sdmaxalphaec));
    staaxisyai->setLabelFormat(accuracy(sdminalphai,sdmaxalphaic));
    staaxisyqe->setLabelFormat(accuracy(sdminqe,sdmaxqec));
    staaxisyqi->setLabelFormat(accuracy(sdminqi,sdmaxqic));
    staaxisysre->setLabelFormat(accuracy(sdminSRe,sdmaxSRec));
    staaxisysri->setLabelFormat(accuracy(sdminSRi,sdmaxSRic));
    staaxisyu->setLabelFormat(accuracy(sdminu,sdmaxuc));
    staaxisyfc->setLabelFormat(accuracy(sdminFc,sdmaxFcc));
    staaxisymg->setLabelFormat(accuracy(sdminMg,sdmaxMgc));
    staaxisywc->setLabelFormat(accuracy(sdminwc,sdmaxwcc));
    staaxisywb->setLabelFormat(accuracy(sdminwb,sdmaxwbc));


    //给坐标轴设置label字体
    //设置坐标轴标签和标注字体大小
    QFont labelfontsd("Microsoft YaHei",10,75);
    staaxisxlamda->setLabelsFont(labelfontsd);
    staaxisxae->setLabelsFont(labelfontsd);
    staaxisxai->setLabelsFont(labelfontsd);
    staaxisxqe->setLabelsFont(labelfontsd);
    staaxisxqi->setLabelsFont(labelfontsd);
    staaxisxsre->setLabelsFont(labelfontsd);
    staaxisxsri->setLabelsFont(labelfontsd);
    staaxisxu->setLabelsFont(labelfontsd);
    staaxisxfc->setLabelsFont(labelfontsd);
    staaxisxmg->setLabelsFont(labelfontsd);
    staaxisxwc->setLabelsFont(labelfontsd);
    staaxisxwb->setLabelsFont(labelfontsd);

    staaxisylamda->setLabelsFont(labelfontsd);
    staaxisyae->setLabelsFont(labelfontsd);
    staaxisyai->setLabelsFont(labelfontsd);
    staaxisyqe->setLabelsFont(labelfontsd);
    staaxisyqi->setLabelsFont(labelfontsd);
    staaxisysre->setLabelsFont(labelfontsd);
    staaxisysri->setLabelsFont(labelfontsd);
    staaxisyu->setLabelsFont(labelfontsd);
    staaxisyfc->setLabelsFont(labelfontsd);
    staaxisymg->setLabelsFont(labelfontsd);
    staaxisywc->setLabelsFont(labelfontsd);
    staaxisywb->setLabelsFont(labelfontsd);


    //设置坐标轴含义
    //x轴坐标标注
    staaxisxlamda->setTitleText("滚动体个数");
    staaxisxae->setTitleText("滚动体个数");
    staaxisxai->setTitleText("滚动体个数");
    staaxisxqe->setTitleText("滚动体个数");
    staaxisxqi->setTitleText("滚动体个数");
    staaxisxsre->setTitleText("滚动体个数");
    staaxisxsri->setTitleText("滚动体个数");
    staaxisxu->setTitleText("滚动体个数");
    staaxisxfc->setTitleText("滚动体个数");
    staaxisxmg->setTitleText("滚动体个数");
    staaxisxwc->setTitleText("滚动体个数");
    staaxisxwb->setTitleText("滚动体个数");
    //y轴标注
    staaxisylamda->setTitleText("姿态角 （°）");
    staaxisyae->setTitleText("外圈接触角 （°）");
    staaxisyai->setTitleText("内圈接触角 （°）");
    staaxisyqe->setTitleText("外圈接触载荷 （N）");
    staaxisyqi->setTitleText("内圈接触载荷 （N）");
    staaxisysre->setTitleText("滚珠与外滚道旋滚比");
    staaxisysri->setTitleText("滚珠与内滚道旋滚比");
    staaxisyu->setTitleText("摩擦系数");
    staaxisyfc->setTitleText("离心力 （N）");
    staaxisymg->setTitleText("陀螺力矩 （N*m）");
    staaxisywc->setTitleText("滚珠自转角速度 （rad/s）");
    staaxisywb->setTitleText("滚珠公转角速度 （rad/s）");


    //将线段加在chart中显示
    m_sdchartlamda->addSeries(staserieslamda);
    m_sdchartalphae->addSeries(staseriesalphae);
    m_sdchartalphai->addSeries(staseriesalphai);
    m_sdchartqe->addSeries(staseriesqe);
    m_sdchartqi->addSeries(staseriesqi);
    m_sdchartu->addSeries(staseriesu);
    m_sdchartFc->addSeries(staseriesFc);
    m_sdchartMg->addSeries(staseriesMg);
    m_sdchartSre->addSeries(staseriessre);
    m_sdchartSri->addSeries(staseriessri);
    m_sdchartwc->addSeries(staserieswc);
    m_sdchartwb->addSeries(staserieswb);


    //在chart中加上编辑好的坐标轴
    m_sdchartlamda->addAxis(staaxisxlamda,Qt::AlignBottom);
    m_sdchartlamda->addAxis(staaxisylamda,Qt::AlignLeft);
    m_sdchartalphae->addAxis(staaxisxae,Qt::AlignBottom);
    m_sdchartalphae->addAxis(staaxisyae,Qt::AlignLeft);
    m_sdchartalphai->addAxis(staaxisxai,Qt::AlignBottom);
    m_sdchartalphai->addAxis(staaxisyai,Qt::AlignLeft);
    m_sdchartqe->addAxis(staaxisxqe,Qt::AlignBottom);
    m_sdchartqe->addAxis(staaxisyqe,Qt::AlignLeft);
    m_sdchartqi->addAxis(staaxisxqi,Qt::AlignBottom);
    m_sdchartqi->addAxis(staaxisyqi,Qt::AlignLeft);
    m_sdchartu->addAxis(staaxisxu,Qt::AlignBottom);
    m_sdchartu->addAxis(staaxisyu,Qt::AlignLeft);
    m_sdchartFc->addAxis(staaxisxfc,Qt::AlignBottom);
    m_sdchartFc->addAxis(staaxisyfc,Qt::AlignLeft);
    m_sdchartMg->addAxis(staaxisxmg,Qt::AlignBottom);
    m_sdchartMg->addAxis(staaxisymg,Qt::AlignLeft);
    m_sdchartSre->addAxis(staaxisxsre,Qt::AlignBottom);
    m_sdchartSre->addAxis(staaxisysre,Qt::AlignLeft);
    m_sdchartSri->addAxis(staaxisxsri,Qt::AlignBottom);
    m_sdchartSri->addAxis(staaxisysri,Qt::AlignLeft);
    m_sdchartwc->addAxis(staaxisxwc,Qt::AlignBottom);
    m_sdchartwc->addAxis(staaxisywc,Qt::AlignLeft);
    m_sdchartwb->addAxis(staaxisxwb,Qt::AlignBottom);
    m_sdchartwb->addAxis(staaxisywb,Qt::AlignLeft);

    //将坐标轴与曲线绑定
    staserieslamda->attachAxis(staaxisxlamda);
    staserieslamda->attachAxis(staaxisylamda);
    staseriesalphae->attachAxis(staaxisxae);
    staseriesalphae->attachAxis(staaxisyae);
    staseriesalphai->attachAxis(staaxisxai);
    staseriesalphai->attachAxis(staaxisyai);
    staseriesqe->attachAxis(staaxisxqe);
    staseriesqe->attachAxis(staaxisyqe);
    staseriesqi->attachAxis(staaxisxqi);
    staseriesqi->attachAxis(staaxisyqi);
    staseriesu->attachAxis(staaxisxu);
    staseriesu->attachAxis(staaxisyu);
    staseriesFc->attachAxis(staaxisxfc);
    staseriesFc->attachAxis(staaxisyfc);
    staseriesMg->attachAxis(staaxisxmg);
    staseriesMg->attachAxis(staaxisymg);
    staseriessre->attachAxis(staaxisxsre);
    staseriessre->attachAxis(staaxisysre);
    staseriessri->attachAxis(staaxisxsri);
    staseriessri->attachAxis(staaxisysri);
    staserieswc->attachAxis(staaxisxwc);
    staserieswc->attachAxis(staaxisywc);
    staserieswb->attachAxis(staaxisxwb);
    staserieswb->attachAxis(staaxisywb);

    //设置外边界为0
    m_sdchartlamda->layout()->setContentsMargins(0, 0, 0, 0);
    m_sdchartalphae->layout()->setContentsMargins(0, 0, 0, 0);
    m_sdchartalphai->layout()->setContentsMargins(0, 0, 0, 0);
    m_sdchartqe->layout()->setContentsMargins(0, 0, 0, 0);
    m_sdchartqi->layout()->setContentsMargins(0, 0, 0, 0);
    m_sdchartu->layout()->setContentsMargins(0, 0, 0, 0);
    m_sdchartFc->layout()->setContentsMargins(0, 0, 0, 0);
    m_sdchartMg->layout()->setContentsMargins(0, 0, 0, 0);
    m_sdchartSre->layout()->setContentsMargins(0, 0, 0, 0);
    m_sdchartSri->layout()->setContentsMargins(0, 0, 0, 0);
    m_sdchartwc->layout()->setContentsMargins(0, 0, 0, 0);
    m_sdchartwb->layout()->setContentsMargins(0, 0, 0, 0);

    //隐藏图例
    m_sdchartlamda->legend()->hide();
    m_sdchartalphae->legend()->hide();
    m_sdchartalphai->legend()->hide();
    m_sdchartqe->legend()->hide();
    m_sdchartqi->legend()->hide();
    m_sdchartu->legend()->hide();
    m_sdchartFc->legend()->hide();
    m_sdchartMg->legend()->hide();
    m_sdchartSre->legend()->hide();
    m_sdchartSri->legend()->hide();
    m_sdchartwc->legend()->hide();
    m_sdchartwb->legend()->hide();

    //chart命名
    //stachart1->setTitle("静力学分析图一");
    //stachart2->setTitle("静力学分析图二");

    //放到抬升的地方
    ui->plotlamda->setChart(m_sdchartlamda);
    ui->plotalphae->setChart(m_sdchartalphae);
    ui->plotalphai->setChart(m_sdchartalphai);
    ui->plotQe->setChart(m_sdchartqe);
    ui->plotQi->setChart(m_sdchartqi);
    ui->plotSRe->setChart(m_sdchartSre);
    ui->plotSRi->setChart(m_sdchartSri);
    ui->plotu->setChart(m_sdchartu);
    ui->plotwc->setChart(m_sdchartwc);
    ui->plotwb->setChart(m_sdchartwb);
    ui->plotFc->setChart(m_sdchartFc);
    ui->plotMg->setChart(m_sdchartMg);

    //zoom初始化
    m_sdchartlamda->zoom(1.25);
    m_sdchartlamda->zoom(0.8);
    m_sdchartalphae->zoom(1.25);
    m_sdchartalphae->zoom(0.8);
    m_sdchartalphai->zoom(1.25);
    m_sdchartalphai->zoom(0.8);
    m_sdchartqe->zoom(1.25);
    m_sdchartqe->zoom(0.8);
    m_sdchartqi->zoom(1.25);
    m_sdchartqi->zoom(0.8);
    m_sdchartu->zoom(1.25);
    m_sdchartu->zoom(0.8);
    m_sdchartFc->zoom(1.25);
    m_sdchartFc->zoom(0.8);
    m_sdchartMg->zoom(1.25);
    m_sdchartMg->zoom(0.8);
    m_sdchartSre->zoom(1.25);
    m_sdchartSre->zoom(0.8);
    m_sdchartSri->zoom(1.25);
    m_sdchartSri->zoom(0.8);
    m_sdchartwc->zoom(1.25);
    m_sdchartwc->zoom(0.8);
    m_sdchartwb->zoom(1.25);
    m_sdchartwb->zoom(0.8);
}

//图像下限定义
double SimuDyn_Charts::calculatemin(double min, double max)
{
    double delta = max - min;
    double change = delta * 0.1;
    //最小值设置
    min = min - change;
    if(min < 0)
        min = 0;
    //精确度标准化
    if(change>=0 && change<0.00001)
        min = double(int(min/0.0000005)*0.0000005);
    else if(change>=0.00001 && change<0.0001)
        min = double(int(min/0.000005)*0.000005);
    else if(change>=0.0001 && change<0.001)
        min = double(int(min/0.00005)*0.00005);
    else if(change>=0.001 && change<0.01)
        min = double(int(min/0.0005)*0.0005);
    else if(change>=0.01 && change<0.1)
        min = double(int(min/0.005)*0.005);
    else if(change>=0.1 && change<1)
        min = double(int(min/0.05)*0.05);
    else if(change>=1)
        min = double(int(min/0.5)*0.5);
    return min;

}


//图像上限定义
double SimuDyn_Charts::calculatemax(double min, double max)
{
    double delta = max - min;
    double change = delta * 0.1;
    //最大值设置
    max = max + change;
    //精确度标准化
    if(change>=0 && change<0.00001)
        max = double(int(max/0.0000005)*0.0000005+0.0000005);
    else if(change>=0.00001 && change<0.0001)
        max = double(int(max/0.000005)*0.000005+0.000005);
    else if(change>=0.0001 && change<0.001)
        max = double(int(max/0.00005)*0.00005+0.00005);
    else if(change>=0.001 && change<0.01)
        max = double(int(max/0.0005)*0.0005+0.0005);
    else if(change>=0.01 &&change<0.1 )
        max = double(int(max/0.005)*0.005+0.005);
    else if(change>=0.1 && change<1 )
        max = double(int(max/0.05)*0.05+0.05);
    else if(change>=1)
        max = double(int(max/0.5)*0.5+0.5);
    return max;
}

//设置精度
QString SimuDyn_Charts::accuracy(double min, double max)
{
    double delta = max - min;
    double change = delta * 0.1;
    QString decimal;
    if(change>=0 && change<0.00001)
        decimal = "%.7f";
    else if(change>=0.00001 && change<0.0001)
        decimal = "%.6f";
    else if(change>=0.0001 && change<0.001)
        decimal = "%.5f";
    else if(change>=0.001 && change<0.01)
        decimal = "%.4f";
    else if(change>=0.01 &&change<0.1 )
        decimal = "%.3f";
    else if(change>=0.1 && change<1 )
        decimal = "%.2f";
    else if(change>=1)
        decimal = "%.1f";
    return decimal;
}

void SimuDyn_Charts::zoombeforescoll_simu_charts(QChart *m_charts)
{
    m_charts->zoom(1.25);
    m_charts->zoom(0.8);
}


//保存图片

void SimuDyn_Charts::on_pushButton_5_clicked()
{
    //确认保存路径
    QString chartsavefile_name = QFileDialog::getSaveFileName(this,"图表结果",".","图片(*.png);;图片(*.jpg)");
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap pstaa = screen->grabWindow(ui->plotalphai->winId());
    QImage imagestaa = pstaa.toImage();
    imagestaa.save(chartsavefile_name);
}

void SimuDyn_Charts::on_pushButton_6_clicked()
{
    //确认保存路径
    QString chartsavefile_name = QFileDialog::getSaveFileName(this,"图表结果",".","图片(*.png);;图片(*.jpg)");
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap pstaa = screen->grabWindow(ui->plotalphae->winId());
    QImage imagestaa = pstaa.toImage();
    imagestaa.save(chartsavefile_name);
}

void SimuDyn_Charts::on_pushButton_7_clicked()
{
    //确认保存路径
    QString chartsavefile_name = QFileDialog::getSaveFileName(this,"图表结果",".","图片(*.png);;图片(*.jpg)");
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap pstaa = screen->grabWindow(ui->plotlamda->winId());
    QImage imagestaa = pstaa.toImage();
    imagestaa.save(chartsavefile_name);
}

void SimuDyn_Charts::on_pushButton_9_clicked()
{
    //确认保存路径
    QString chartsavefile_name = QFileDialog::getSaveFileName(this,"图表结果",".","图片(*.png);;图片(*.jpg)");
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap pstaa = screen->grabWindow(ui->plotu->winId());
    QImage imagestaa = pstaa.toImage();
    imagestaa.save(chartsavefile_name);
}

void SimuDyn_Charts::on_pushButton_clicked()
{
    //确认保存路径
    QString chartsavefile_name = QFileDialog::getSaveFileName(this,"图表结果",".","图片(*.png);;图片(*.jpg)");
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap pstaa = screen->grabWindow(ui->plotQi->winId());
    QImage imagestaa = pstaa.toImage();
    imagestaa.save(chartsavefile_name);
}


void SimuDyn_Charts::on_pushButton_2_clicked()
{
    //确认保存路径
    QString chartsavefile_name = QFileDialog::getSaveFileName(this,"图表结果",".","图片(*.png);;图片(*.jpg)");
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap pstaa = screen->grabWindow(ui->plotQe->winId());
    QImage imagestaa = pstaa.toImage();
    imagestaa.save(chartsavefile_name);
}

void SimuDyn_Charts::on_pushButton_3_clicked()
{
    //确认保存路径
    QString chartsavefile_name = QFileDialog::getSaveFileName(this,"图表结果",".","图片(*.png);;图片(*.jpg)");
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap pstaa = screen->grabWindow(ui->plotFc->winId());
    QImage imagestaa = pstaa.toImage();
    imagestaa.save(chartsavefile_name);
}

void SimuDyn_Charts::on_pushButton_4_clicked()
{
    //确认保存路径
    QString chartsavefile_name = QFileDialog::getSaveFileName(this,"图表结果",".","图片(*.png);;图片(*.jpg)");
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap pstaa = screen->grabWindow(ui->plotMg->winId());
    QImage imagestaa = pstaa.toImage();
    imagestaa.save(chartsavefile_name);
}

void SimuDyn_Charts::on_pushButton_10_clicked()
{
    //确认保存路径
    QString chartsavefile_name = QFileDialog::getSaveFileName(this,"图表结果",".","图片(*.png);;图片(*.jpg)");
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap pstaa = screen->grabWindow(ui->plotwb->winId());
    QImage imagestaa = pstaa.toImage();
    imagestaa.save(chartsavefile_name);
}

void SimuDyn_Charts::on_pushButton_11_clicked()
{
    //确认保存路径
    QString chartsavefile_name = QFileDialog::getSaveFileName(this,"图表结果",".","图片(*.png);;图片(*.jpg)");
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap pstaa = screen->grabWindow(ui->plotwc->winId());
    QImage imagestaa = pstaa.toImage();
    imagestaa.save(chartsavefile_name);
}

void SimuDyn_Charts::on_pushButton_12_clicked()
{
    //确认保存路径
    QString chartsavefile_name = QFileDialog::getSaveFileName(this,"图表结果",".","图片(*.png);;图片(*.jpg)");
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap pstaa = screen->grabWindow(ui->plotSRi->winId());
    QImage imagestaa = pstaa.toImage();
    imagestaa.save(chartsavefile_name);
}

void SimuDyn_Charts::on_pushButton_13_clicked()
{
    //确认保存路径
    QString chartsavefile_name = QFileDialog::getSaveFileName(this,"图表结果",".","图片(*.png);;图片(*.jpg)");
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap pstaa = screen->grabWindow(ui->plotSRe->winId());
    QImage imagestaa = pstaa.toImage();
    imagestaa.save(chartsavefile_name);
}

////关闭按钮
//void SimuDyn_Charts::on_pushButton_8_clicked()
//{
//    this->close();
//}

void SimuDyn_Charts::on_pushButton_u_clicked()
{
    m_sdchartu->zoomReset();
}

void SimuDyn_Charts::on_pushButton_alphai_clicked()
{
    m_sdchartalphai->zoomReset();
}

void SimuDyn_Charts::on_pushButton_alphae_clicked()
{
    m_sdchartalphae->zoomReset();
}

void SimuDyn_Charts::on_pushButton_lamda_clicked()
{
    m_sdchartlamda->zoomReset();
}

void SimuDyn_Charts::on_pushButton_qi_clicked()
{
    m_sdchartqi->zoomReset();
}

void SimuDyn_Charts::on_pushButton_qe_clicked()
{
    m_sdchartqe->zoomReset();
}

void SimuDyn_Charts::on_pushButton_Fc_clicked()
{
    m_sdchartFc->zoomReset();
}

void SimuDyn_Charts::on_pushButton_M_clicked()
{
    m_sdchartMg->zoomReset();
}

void SimuDyn_Charts::on_pushButton_wb_clicked()
{
    m_sdchartwb->zoomReset();
}

void SimuDyn_Charts::on_pushButton_wc_clicked()
{
    m_sdchartwc->zoomReset();
}

void SimuDyn_Charts::on_pushButton_SRi_clicked()
{
    m_sdchartSri->zoomReset();
}

void SimuDyn_Charts::on_pushButton_SRe_clicked()
{
    m_sdchartSre->zoomReset();
}


//放大缩小操作
void SimuDyn_Charts::wheelEvent(QWheelEvent *event)
{
    //对图像进行操作
    double zoomfactorin,zoomfactorout;  //定义放大缩小参数，但是numSteps.y()每次移动都是+1或者-1
    zoomfactorin = 0.88;    //缩小因子
    zoomfactorout = 1.15;   //放大因子

    if(ui->widgetalphaighost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        //只有当鼠标光标在图像内，才获取当前坐标x,y
        double cursor_x;
        double cursor_y;
        cursor_x = event->position().x();
        cursor_y = event->position().y();
        //测出与中点距离
        double scroll_delta_x,scroll_delta_y;
        scroll_delta_x = (m_sdchartalphai->plotArea().center().x() - cursor_x)*(zoomfactorout - 1);
        scroll_delta_y = (m_sdchartalphai->plotArea().center().y() - cursor_y)*(zoomfactorout - 1);


        QPoint numDegree = event->angleDelta() / 8; //滚动的角度，*8就是鼠标滚动的距离
        QPoint numSteps;    //定义滚动的步数
        if(!numDegree.isNull())
        {
            numSteps = numDegree / 15;   //滚动的步数，*15就是鼠标滚动的角度
        }
        if(numSteps.y() < 0)    //向后转，缩小图像
        {
            m_sdchartalphai->zoom(zoomfactorin);
            m_sdchartalphai->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
        else if(numSteps.y() > 0)   //向前转，放大图像
        {
            m_sdchartalphai->zoom(zoomfactorout);
            m_sdchartalphai->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
    }
    else if(ui->widgetalphaeghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        //只有当鼠标光标在图像内，才获取当前坐标x,y
        double cursor_x;
        double cursor_y;
        cursor_x = event->position().x();
        cursor_y = event->position().y();
        //测出与中点距离
        double scroll_delta_x,scroll_delta_y;
        scroll_delta_x = (m_sdchartalphae->plotArea().center().x() - cursor_x)*(zoomfactorout - 1);
        scroll_delta_y = (m_sdchartalphae->plotArea().center().y() - cursor_y)*(zoomfactorout - 1);


        QPoint numDegree = event->angleDelta() / 8; //滚动的角度，*8就是鼠标滚动的距离
        QPoint numSteps;    //定义滚动的步数
        if(!numDegree.isNull())
        {
            numSteps = numDegree / 15;   //滚动的步数，*15就是鼠标滚动的角度
        }
        if(numSteps.y() < 0)    //向后转，缩小图像
        {
            m_sdchartalphae->zoom(zoomfactorin);
            m_sdchartalphae->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
        else if(numSteps.y() > 0)   //向前转，放大图像
        {
            m_sdchartalphae->zoom(zoomfactorout);
            m_sdchartalphae->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
    }
    else if(ui->widgetlamdaghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        //只有当鼠标光标在图像内，才获取当前坐标x,y
        double cursor_x;
        double cursor_y;
        cursor_x = event->position().x();
        cursor_y = event->position().y();
        //测出与中点距离
        double scroll_delta_x,scroll_delta_y;
        scroll_delta_x = (m_sdchartlamda->plotArea().center().x() - cursor_x)*(zoomfactorout - 1);
        scroll_delta_y = (m_sdchartlamda->plotArea().center().y() - cursor_y)*(zoomfactorout - 1);


        QPoint numDegree = event->angleDelta() / 8; //滚动的角度，*8就是鼠标滚动的距离
        QPoint numSteps;    //定义滚动的步数
        if(!numDegree.isNull())
        {
            numSteps = numDegree / 15;   //滚动的步数，*15就是鼠标滚动的角度
        }
        if(numSteps.y() < 0)    //向后转，缩小图像
        {
            m_sdchartlamda->zoom(zoomfactorin);
            m_sdchartlamda->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
        else if(numSteps.y() > 0)   //向前转，放大图像
        {
            m_sdchartlamda->zoom(zoomfactorout);
            m_sdchartlamda->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
    }
    else if(ui->widgetughost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        //只有当鼠标光标在图像内，才获取当前坐标x,y
        double cursor_x;
        double cursor_y;
        cursor_x = event->position().x();
        cursor_y = event->position().y();
        //测出与中点距离
        double scroll_delta_x,scroll_delta_y;
        scroll_delta_x = (m_sdchartu->plotArea().center().x() - cursor_x)*(zoomfactorout - 1);
        scroll_delta_y = (m_sdchartu->plotArea().center().y() - cursor_y)*(zoomfactorout - 1);


        QPoint numDegree = event->angleDelta() / 8; //滚动的角度，*8就是鼠标滚动的距离
        QPoint numSteps;    //定义滚动的步数
        if(!numDegree.isNull())
        {
            numSteps = numDegree / 15;   //滚动的步数，*15就是鼠标滚动的角度
        }
        if(numSteps.y() < 0)    //向后转，缩小图像
        {
            m_sdchartu->zoom(zoomfactorin);
            m_sdchartu->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
        else if(numSteps.y() > 0)   //向前转，放大图像
        {
            m_sdchartu->zoom(zoomfactorout);
            m_sdchartu->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
    }
    else if(ui->widgetQighost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        //只有当鼠标光标在图像内，才获取当前坐标x,y
        double cursor_x;
        double cursor_y;
        cursor_x = event->position().x();
        cursor_y = event->position().y();
        //测出与中点距离
        double scroll_delta_x,scroll_delta_y;
        scroll_delta_x = (m_sdchartqi->plotArea().center().x() - cursor_x)*(zoomfactorout - 1);
        scroll_delta_y = (m_sdchartqi->plotArea().center().y() - cursor_y)*(zoomfactorout - 1);


        QPoint numDegree = event->angleDelta() / 8; //滚动的角度，*8就是鼠标滚动的距离
        QPoint numSteps;    //定义滚动的步数
        if(!numDegree.isNull())
        {
            numSteps = numDegree / 15;   //滚动的步数，*15就是鼠标滚动的角度
        }
        if(numSteps.y() < 0)    //向后转，缩小图像
        {
            m_sdchartqi->zoom(zoomfactorin);
            m_sdchartqi->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
        else if(numSteps.y() > 0)   //向前转，放大图像
        {
            m_sdchartqi->zoom(zoomfactorout);
            m_sdchartqi->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
    }
    else if(ui->widgetQeghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        //只有当鼠标光标在图像内，才获取当前坐标x,y
        double cursor_x;
        double cursor_y;
        cursor_x = event->position().x();
        cursor_y = event->position().y();
        //测出与中点距离
        double scroll_delta_x,scroll_delta_y;
        scroll_delta_x = (m_sdchartqe->plotArea().center().x() - cursor_x)*(zoomfactorout - 1);
        scroll_delta_y = (m_sdchartqe->plotArea().center().y() - cursor_y)*(zoomfactorout - 1);


        QPoint numDegree = event->angleDelta() / 8; //滚动的角度，*8就是鼠标滚动的距离
        QPoint numSteps;    //定义滚动的步数
        if(!numDegree.isNull())
        {
            numSteps = numDegree / 15;   //滚动的步数，*15就是鼠标滚动的角度
        }
        if(numSteps.y() < 0)    //向后转，缩小图像
        {
            m_sdchartqe->zoom(zoomfactorin);
            m_sdchartqe->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
        else if(numSteps.y() > 0)   //向前转，放大图像
        {
            m_sdchartqe->zoom(zoomfactorout);
            m_sdchartqe->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
    }
    else if(ui->widgetFcghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        //只有当鼠标光标在图像内，才获取当前坐标x,y
        double cursor_x;
        double cursor_y;
        cursor_x = event->position().x();
        cursor_y = event->position().y();
        //测出与中点距离
        double scroll_delta_x,scroll_delta_y;
        scroll_delta_x = (m_sdchartFc->plotArea().center().x() - cursor_x)*(zoomfactorout - 1);
        scroll_delta_y = (m_sdchartFc->plotArea().center().y() - cursor_y)*(zoomfactorout - 1);


        QPoint numDegree = event->angleDelta() / 8; //滚动的角度，*8就是鼠标滚动的距离
        QPoint numSteps;    //定义滚动的步数
        if(!numDegree.isNull())
        {
            numSteps = numDegree / 15;   //滚动的步数，*15就是鼠标滚动的角度
        }
        if(numSteps.y() < 0)    //向后转，缩小图像
        {
            m_sdchartFc->zoom(zoomfactorin);
            m_sdchartFc->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
        else if(numSteps.y() > 0)   //向前转，放大图像
        {
            m_sdchartFc->zoom(zoomfactorout);
            m_sdchartFc->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
    }
    else if(ui->widgetMghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        //只有当鼠标光标在图像内，才获取当前坐标x,y
        double cursor_x;
        double cursor_y;
        cursor_x = event->position().x();
        cursor_y = event->position().y();
        //测出与中点距离
        double scroll_delta_x,scroll_delta_y;
        scroll_delta_x = (m_sdchartMg->plotArea().center().x() - cursor_x)*(zoomfactorout - 1);
        scroll_delta_y = (m_sdchartMg->plotArea().center().y() - cursor_y)*(zoomfactorout - 1);


        QPoint numDegree = event->angleDelta() / 8; //滚动的角度，*8就是鼠标滚动的距离
        QPoint numSteps;    //定义滚动的步数
        if(!numDegree.isNull())
        {
            numSteps = numDegree / 15;   //滚动的步数，*15就是鼠标滚动的角度
        }
        if(numSteps.y() < 0)    //向后转，缩小图像
        {
            m_sdchartMg->zoom(zoomfactorin);
            m_sdchartMg->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
        else if(numSteps.y() > 0)   //向前转，放大图像
        {
            m_sdchartMg->zoom(zoomfactorout);
            m_sdchartMg->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
    }
    else if(ui->widgetwbghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        //只有当鼠标光标在图像内，才获取当前坐标x,y
        double cursor_x;
        double cursor_y;
        cursor_x = event->position().x();
        cursor_y = event->position().y();
        //测出与中点距离
        double scroll_delta_x,scroll_delta_y;
        scroll_delta_x = (m_sdchartwb->plotArea().center().x() - cursor_x)*(zoomfactorout - 1);
        scroll_delta_y = (m_sdchartwb->plotArea().center().y() - cursor_y)*(zoomfactorout - 1);


        QPoint numDegree = event->angleDelta() / 8; //滚动的角度，*8就是鼠标滚动的距离
        QPoint numSteps;    //定义滚动的步数
        if(!numDegree.isNull())
        {
            numSteps = numDegree / 15;   //滚动的步数，*15就是鼠标滚动的角度
        }
        if(numSteps.y() < 0)    //向后转，缩小图像
        {
            m_sdchartwb->zoom(zoomfactorin);
            m_sdchartwb->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
        else if(numSteps.y() > 0)   //向前转，放大图像
        {
            m_sdchartwb->zoom(zoomfactorout);
            m_sdchartwb->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
    }
    else if(ui->widgetwcghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        //只有当鼠标光标在图像内，才获取当前坐标x,y
        double cursor_x;
        double cursor_y;
        cursor_x = event->position().x();
        cursor_y = event->position().y();
        //测出与中点距离
        double scroll_delta_x,scroll_delta_y;
        scroll_delta_x = (m_sdchartwc->plotArea().center().x() - cursor_x)*(zoomfactorout - 1);
        scroll_delta_y = (m_sdchartwc->plotArea().center().y() - cursor_y)*(zoomfactorout - 1);


        QPoint numDegree = event->angleDelta() / 8; //滚动的角度，*8就是鼠标滚动的距离
        QPoint numSteps;    //定义滚动的步数
        if(!numDegree.isNull())
        {
            numSteps = numDegree / 15;   //滚动的步数，*15就是鼠标滚动的角度
        }
        if(numSteps.y() < 0)    //向后转，缩小图像
        {
            m_sdchartwc->zoom(zoomfactorin);
            m_sdchartwc->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
        else if(numSteps.y() > 0)   //向前转，放大图像
        {
            m_sdchartwc->zoom(zoomfactorout);
            m_sdchartwc->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
    }
    else if(ui->widgetSRighost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        //只有当鼠标光标在图像内，才获取当前坐标x,y
        double cursor_x;
        double cursor_y;
        cursor_x = event->position().x();
        cursor_y = event->position().y();
        //测出与中点距离
        double scroll_delta_x,scroll_delta_y;
        scroll_delta_x = (m_sdchartSri->plotArea().center().x() - cursor_x)*(zoomfactorout - 1);
        scroll_delta_y = (m_sdchartSri->plotArea().center().y() - cursor_y)*(zoomfactorout - 1);


        QPoint numDegree = event->angleDelta() / 8; //滚动的角度，*8就是鼠标滚动的距离
        QPoint numSteps;    //定义滚动的步数
        if(!numDegree.isNull())
        {
            numSteps = numDegree / 15;   //滚动的步数，*15就是鼠标滚动的角度
        }
        if(numSteps.y() < 0)    //向后转，缩小图像
        {
            m_sdchartSri->zoom(zoomfactorin);
            m_sdchartSri->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
        else if(numSteps.y() > 0)   //向前转，放大图像
        {
            m_sdchartSri->zoom(zoomfactorout);
            m_sdchartSri->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
    }
    else if(ui->widgetSReghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        //只有当鼠标光标在图像内，才获取当前坐标x,y
        double cursor_x;
        double cursor_y;
        cursor_x = event->position().x();
        cursor_y = event->position().y();
        //测出与中点距离
        double scroll_delta_x,scroll_delta_y;
        scroll_delta_x = (m_sdchartSre->plotArea().center().x() - cursor_x)*(zoomfactorout - 1);
        scroll_delta_y = (m_sdchartSre->plotArea().center().y() - cursor_y)*(zoomfactorout - 1);


        QPoint numDegree = event->angleDelta() / 8; //滚动的角度，*8就是鼠标滚动的距离
        QPoint numSteps;    //定义滚动的步数
        if(!numDegree.isNull())
        {
            numSteps = numDegree / 15;   //滚动的步数，*15就是鼠标滚动的角度
        }
        if(numSteps.y() < 0)    //向后转，缩小图像
        {
            m_sdchartSre->zoom(zoomfactorin);
            m_sdchartSre->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
        else if(numSteps.y() > 0)   //向前转，放大图像
        {
            m_sdchartSre->zoom(zoomfactorout);
            m_sdchartSre->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
    }
}

void SimuDyn_Charts::mousePressEvent(QMouseEvent *event)
{
     m_lastpos = event->pos();
}

//鼠标拖动操作
void SimuDyn_Charts::mouseMoveEvent(QMouseEvent *event)
{
    //判断鼠标是否在这个控件之内
    //if(!ui->staplotalpha->geometry().contains(ui->tabstacharts->mapFromGlobal(QCursor::pos())));   //这个好像不咋行
    if(ui->widgetalphaighost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        zoombeforescoll_simu_charts(m_sdchartalphai);
        int dx = event->x() - m_lastpos.x();
        int dy = event->y() - m_lastpos.y();

        if (event->buttons() & Qt::LeftButton)
        {
            m_sdchartalphai->scroll(-1.0*dx,1.0*dy);
        }
        m_lastpos = event->pos();
    }
    else if(ui->widgetalphaeghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        zoombeforescoll_simu_charts(m_sdchartalphae);
        int dx = event->x() - m_lastpos.x();
        int dy = event->y() - m_lastpos.y();

        if (event->buttons() & Qt::LeftButton)
        {
            m_sdchartalphae->scroll(-1.0*dx,1.0*dy);
        }
        m_lastpos = event->pos();
    }
    else if(ui->widgetlamdaghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        zoombeforescoll_simu_charts(m_sdchartlamda);
        int dx = event->x() - m_lastpos.x();
        int dy = event->y() - m_lastpos.y();

        if (event->buttons() & Qt::LeftButton)
        {
            m_sdchartlamda->scroll(-1.0*dx,1.0*dy);
        }
        m_lastpos = event->pos();
    }
    else if(ui->widgetughost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        zoombeforescoll_simu_charts(m_sdchartu);
        int dx = event->x() - m_lastpos.x();
        int dy = event->y() - m_lastpos.y();

        if (event->buttons() & Qt::LeftButton)
        {
            m_sdchartu->scroll(-1.0*dx,1.0*dy);
        }
        m_lastpos = event->pos();
    }
    else if(ui->widgetQighost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        zoombeforescoll_simu_charts(m_sdchartqi);
        int dx = event->x() - m_lastpos.x();
        int dy = event->y() - m_lastpos.y();

        if (event->buttons() & Qt::LeftButton)
        {
            m_sdchartqi->scroll(-1.0*dx,1.0*dy);
        }
        m_lastpos = event->pos();
    }
    else if(ui->widgetQeghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        zoombeforescoll_simu_charts(m_sdchartqe);
        int dx = event->x() - m_lastpos.x();
        int dy = event->y() - m_lastpos.y();

        if (event->buttons() & Qt::LeftButton)
        {
            m_sdchartqe->scroll(-1.0*dx,1.0*dy);
        }
        m_lastpos = event->pos();
    }
    else if(ui->widgetFcghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        zoombeforescoll_simu_charts(m_sdchartFc);
        int dx = event->x() - m_lastpos.x();
        int dy = event->y() - m_lastpos.y();

        if (event->buttons() & Qt::LeftButton)
        {
            m_sdchartFc->scroll(-1.0*dx,1.0*dy);
        }
        m_lastpos = event->pos();
    }
    else if(ui->widgetMghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        zoombeforescoll_simu_charts(m_sdchartMg);
        int dx = event->x() - m_lastpos.x();
        int dy = event->y() - m_lastpos.y();

        if (event->buttons() & Qt::LeftButton)
        {
            m_sdchartMg->scroll(-1.0*dx,1.0*dy);
        }
        m_lastpos = event->pos();
    }
    else if(ui->widgetwbghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        zoombeforescoll_simu_charts(m_sdchartwb);
        int dx = event->x() - m_lastpos.x();
        int dy = event->y() - m_lastpos.y();

        if (event->buttons() & Qt::LeftButton)
        {
            m_sdchartwb->scroll(-1.0*dx,1.0*dy);
        }
        m_lastpos = event->pos();
    }
    else if(ui->widgetwcghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        zoombeforescoll_simu_charts(m_sdchartwc);
        int dx = event->x() - m_lastpos.x();
        int dy = event->y() - m_lastpos.y();

        if (event->buttons() & Qt::LeftButton)
        {
            m_sdchartwc->scroll(-1.0*dx,1.0*dy);
        }
        m_lastpos = event->pos();
    }
    else if(ui->widgetSRighost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        zoombeforescoll_simu_charts(m_sdchartSri);
        int dx = event->x() - m_lastpos.x();
        int dy = event->y() - m_lastpos.y();

        if (event->buttons() & Qt::LeftButton)
        {
            m_sdchartSri->scroll(-1.0*dx,1.0*dy);
        }
        m_lastpos = event->pos();
    }
    else if(ui->widgetSReghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        zoombeforescoll_simu_charts(m_sdchartSre);
        int dx = event->x() - m_lastpos.x();
        int dy = event->y() - m_lastpos.y();

        if (event->buttons() & Qt::LeftButton)
        {
            m_sdchartSre->scroll(-1.0*dx,1.0*dy);
        }
        m_lastpos = event->pos();
    }
}
