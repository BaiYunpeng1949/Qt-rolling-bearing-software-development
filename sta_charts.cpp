#include "sta_charts.h"
#include "ui_sta_charts.h"

//为了使用比较大小函数，包含以下头文件和内存拓展
#include<math.h>
#include<QDebug>
using namespace std;

//定义数组储存变量
double Salphachart[100],SQchart[100];


Sta_Charts::Sta_Charts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sta_Charts)
{
    ui->setupUi(this);

    //嵌入主窗口
    setWindowFlag(Qt::CustomizeWindowHint);
    hide();

    //设置默认界面为第一页
    ui->tabstacharts->setCurrentWidget(ui->tabalpha);
    //设置鼠标可以被跟踪
    //setMouseTracking(false);
    //ui->tabstacharts->setMouseTracking(false);
    //ui->tabalpha->setMouseTracking(false);
    //ui->staplotalpha->setMouseTracking(false);
    //m_stachart1.setMouseTracking(true);
}

Sta_Charts::~Sta_Charts()
{
    delete ui;
}

void Sta_Charts::stadealcharts(int z, QVector<double> vecsalpha, QVector<double> vecsq)
{

    //将数据存入数组
    static int j;
    for(j=0;j<z;j++)
    {
        Salphachart[j]=vecsalpha[j];
        SQchart[j]=vecsq[j];
    }
    //建立cahrt
    m_stachart1 = new QChart();
    m_stachart2 = new QChart();
    //建立chart中一会儿要用到的线
    QSplineSeries *staseries1 = new QSplineSeries();
    QSplineSeries *staseries2 = new QSplineSeries();
    int i;
    for(i=0;i<z;i++)
    {
        //根据需要画线
        staseries1->append(i+1,Salphachart[i]);
        staseries2->append(i+1,SQchart[i]);
    }

    //给线命名
    /*
    staseries1->setName("接触角-滚珠个数");
    staseries2->setName("球-滚道接触载荷-滚珠个数");
    */
    //自定义线段的颜色
    //staseries1->setColor(QColor(0,0,255));
    //staseries2->setColor(QColor(0,0,255));
    //线设计一下
    QPen penlinesta;
    penlinesta.setStyle(Qt::SolidLine);
    penlinesta.setWidth(2);    //2像素点线宽
    penlinesta.setColor(Qt::blue);

    //曲线粗也设计一下
    staseries1->setPen(penlinesta);
    staseries2->setPen(penlinesta);


    //开始定义坐标轴
    QValueAxis *staaxisx1 = new QValueAxis;
    QValueAxis *staaxisy1 = new QValueAxis;
    QValueAxis *staaxisx2 = new QValueAxis;
    QValueAxis *staaxisy2 = new QValueAxis;



    //设置轴宽度
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);    //2像素点线宽
    pen.setColor(Qt::black);


    staaxisx1->setLinePen(pen);
    staaxisx1->setLineVisible(true);
    staaxisy1->setLinePen(pen);
    staaxisy1->setLineVisible(true);

    staaxisx2->setLinePen(pen);
    staaxisx2->setLineVisible(true);
    staaxisy2->setLinePen(pen);
    staaxisy2->setLineVisible(true);


    //给坐标轴定义范围
    staaxisx1->setRange(1,z);
    staaxisx2->setRange(1,z);
    //设置坐标轴要有几个刻度
    staaxisx1->setTickCount(z);
    staaxisx2->setTickCount(z);
    //设置纵坐标的小刻度
    staaxisy1->setMinorTickCount(4);
    staaxisy2->setMinorTickCount(4);
    //用找到数组中最大最小元素的方法来设置范围
    double minalpha = *min_element(Salphachart,Salphachart+z);
    double maxalpha = *max_element(Salphachart,Salphachart+z);
    double minQ = *min_element(SQchart,SQchart+z);
    double maxQ = *max_element(SQchart,SQchart+z);
    staaxisy1->setRange(calculatemin(minalpha,maxalpha),calculatemax(minalpha,maxalpha));
    staaxisy2->setRange(calculatemin(minQ,maxQ),calculatemax(minQ,maxQ));
    //使得横坐标只显示不带小数点的整数
    //staaxisx1->setLabelFormat("%d");      //为了保证放大以后也可以显示小数点
    //staaxisx2->setLabelFormat("%d");
    //设置纵坐标也有相应的位数
    //得配合一个判断精确度的函数来使用
    staaxisy1->setLabelFormat(accuracy(minalpha,maxalpha));
    staaxisy2->setLabelFormat(accuracy(minQ,maxQ));

    //设置坐标轴标签和标注字体大小
    QFont labelfont("Microsoft YaHei",10,75);
    staaxisx1->setLabelsFont(labelfont);
    staaxisx2->setLabelsFont(labelfont);
    staaxisy1->setLabelsFont(labelfont);
    staaxisy2->setLabelsFont(labelfont);

    //设置坐标轴含义
    staaxisx1->setTitleText("滚动体个数");
    staaxisy1->setTitleText("接触角（°）");
    staaxisx2->setTitleText("滚动体个数");
    staaxisy2->setTitleText("接触载荷（KN）");


    //将线段加在chart中显示
    m_stachart1->addSeries(staseries1);
    m_stachart2->addSeries(staseries2);
    //在chart中加上编辑好的坐标轴
    //stachart1->setAxisX(staaxisx1,staseries1);
    //stachart1->setAxisY(staaxisy1,staseries1);
    //stachart2->setAxisX(staaxisx2,staseries2);
    //stachart2->setAxisY(staaxisy2,staseries2);

    //绑定坐标轴
    m_stachart1->addAxis(staaxisx1,Qt::AlignBottom);
    m_stachart1->addAxis(staaxisy1,Qt::AlignLeft);
    m_stachart2->addAxis(staaxisx2,Qt::AlignBottom);
    m_stachart2->addAxis(staaxisy2,Qt::AlignLeft);

    //把线绑定坐标轴，位置必须在addAxis之后
    staseries1->attachAxis(staaxisx1);
    staseries1->attachAxis(staaxisy1);
    staseries2->attachAxis(staaxisx2);
    staseries2->attachAxis(staaxisy2);



    //设置外边界都是0
    m_stachart1->layout()->setContentsMargins(0, 0, 0, 0);
    m_stachart2->layout()->setContentsMargins(0, 0, 0, 0);

    //隐藏图例
    m_stachart1->legend()->hide();
    m_stachart2->legend()->hide();

    //chart命名
    //stachart1->setTitle("静力学分析图一");
    //stachart2->setTitle("静力学分析图二");

    ui->staplotalpha->setChart(m_stachart1);
    ui->staplotQ->setChart(m_stachart2);

    //初始化zoom,不在循环里面调用就不会卡了
    //为了能随便使用zoomReset函数
    m_stachart1->zoom(1.25);    //zoom(1)不起作用
    m_stachart1->zoom(0.8);
    m_stachart2->zoom(1.25);    //zoom(1)不起作用
    m_stachart2->zoom(0.8);
}

//计算最小值的函数
double Sta_Charts::calculatemin(double min,double max)
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

//计算最大值的函数
double Sta_Charts::calculatemax(double min,double max)
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

//判断精确度的函数
QString Sta_Charts::accuracy(double min, double max)
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

void Sta_Charts::zoombeforescroll_sta_charts(QChart *m_charts)
{
    m_charts->zoom(1.25);
    m_charts->zoom(0.8);
}

//保存图片
void Sta_Charts::on_pushButtonstaalpha_clicked()
{
    //确认保存路径
    QString chartsavefile_name = QFileDialog::getSaveFileName(this,"图表结果",".","图片(*.png);;图片(*.jpg)");
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap pstaa = screen->grabWindow(ui->staplotalpha->winId());
    QImage imagestaa = pstaa.toImage();
    imagestaa.save(chartsavefile_name);
}

//保存图片
void Sta_Charts::on_pushButtonstaq_clicked()
{
    //确认保存路径
    QString chartsavefile_name = QFileDialog::getSaveFileName(this,"图表结果",".","图片(*.png);;图片(*.jpg)");
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap pstaa = screen->grabWindow(ui->staplotQ->winId());
    QImage imagestaa = pstaa.toImage();
    imagestaa.save(chartsavefile_name);
}

////关闭按钮
//void Sta_Charts::on_pushButton_clicked()
//{
//    this->close();
//}

//鼠标轮滚动事件
void Sta_Charts::wheelEvent(QWheelEvent *event)
{
    //对图像进行操作
    double zoomfactorin,zoomfactorout;  //定义放大缩小参数，但是numSteps.y()每次移动都是+1或者-1
    zoomfactorin = 0.88;    //缩小因子
    zoomfactorout = 1.15;   //放大因子

    //判断在哪张图里面
    if(ui->widgetstachartsalphaghost->underMouse())
    {
        //只有当鼠标光标在图像内，才获取当前坐标x,y
        double cursor_x;
        double cursor_y;
        cursor_x = event->position().x();
        cursor_y = event->position().y();
        //测出与中点距离
        double scroll_delta_x,scroll_delta_y;
        scroll_delta_x = (m_stachart1->plotArea().center().x() - cursor_x)*(zoomfactorout - 1);
        scroll_delta_y = (m_stachart1->plotArea().center().y() - cursor_y)*(zoomfactorout - 1);


        QPoint numDegree = event->angleDelta() / 8; //滚动的角度，*8就是鼠标滚动的距离
        QPoint numSteps;    //定义滚动的步数
        if(!numDegree.isNull())
        {
            numSteps = numDegree / 15;   //滚动的步数，*15就是鼠标滚动的角度
        }
        if(numSteps.y() < 0)    //向后转，缩小图像
        {
            m_stachart1->zoom(zoomfactorin);
            m_stachart1->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
        else if(numSteps.y() > 0)   //向前转，放大图像
        {
            m_stachart1->zoom(zoomfactorout);
            m_stachart1->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
    }
    else if(ui->widgetstachartsqghost->underMouse())
    {
        //只有当鼠标光标在图像内，才获取当前坐标x,y
        double cursor_x;
        double cursor_y;
        cursor_x = event->position().x();
        cursor_y = event->position().y();
        //测出与中点距离
        double scroll_delta_x,scroll_delta_y;
        scroll_delta_x = (m_stachart2->plotArea().center().x() - cursor_x)*(zoomfactorout - 1);
        scroll_delta_y = (m_stachart2->plotArea().center().y() - cursor_y)*(zoomfactorout - 1);

        QPoint numDegree = event->angleDelta() / 8; //滚动的角度，*8就是鼠标滚动的距离
        QPoint numSteps;    //定义滚动的步数
        if(!numDegree.isNull())
        {
            numSteps = numDegree / 15;   //滚动的步数，*15就是鼠标滚动的角度
        }
        if(numSteps.y() < 0)    //向后转，缩小图像
        {
            m_stachart2->zoom(zoomfactorin);
            m_stachart2->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
        else if(numSteps.y() > 0)   //向前转，放大图像
        {
            m_stachart2->zoom(zoomfactorout);
            m_stachart2->scroll(-scroll_delta_x,scroll_delta_y);
            //sum_delta_x = sum_delta_x - scroll_delta_x;
            //sum_delta_y = sum_delta_y + scroll_delta_y;
        }
    }

    //qDebug()<<m_stachart1->plotArea().x()<<m_stachart1->plotArea().y()<<m_stachart1->plotArea().width()<<m_stachart1->plotArea().height();
    event->accept(); //接收事件
}

//鼠标按下位置
void Sta_Charts::mousePressEvent(QMouseEvent *event)
{
    m_lastpos = event->pos();
}

//鼠标移动事件
void Sta_Charts::mouseMoveEvent(QMouseEvent *event)
{
    //判断鼠标是否在这个控件之内
    //if(!ui->staplotalpha->geometry().contains(ui->tabstacharts->mapFromGlobal(QCursor::pos())));   //这个好像不咋行
    if(ui->widgetstachartsalphaghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        zoombeforescroll_sta_charts(m_stachart1);
        int dx = event->x() - m_lastpos.x();
        int dy = event->y() - m_lastpos.y();

        if (event->buttons() & Qt::LeftButton)
        {
            m_stachart1->scroll(-1.0*dx,1.0*dy);
        }
        m_lastpos = event->pos();
    }
    else if(ui->widgetstachartsqghost->underMouse())   //QChartView无法识别mousemoveevent,再在上面加一个widget控件就行了哈哈哈哈哈，我太TM机智了
    {
        zoombeforescroll_sta_charts(m_stachart2);
        int dx = event->x() - m_lastpos.x();
        int dy = event->y() - m_lastpos.y();

        if (event->buttons() & Qt::LeftButton)
        {
            m_stachart2->scroll(-1.0*dx,1.0*dy);
        }
        m_lastpos = event->pos();
    }
}

//reset 恢复到初始情况
void Sta_Charts::on_pushButtonreset_clicked()
{
    //根据zoomReset函数的定义，This will also reset scrolling and explicit axis range settings
    //specified between the first zoom operation and calling this method.
    //所以如果不是第一步就是zoom操作，就会导致第一步平移无法恢复
    //解决方法是在自己scroll前面加一个zoom(1)
    //害，又机智了一把
    m_stachart1->zoomReset();   //zoom恢复   
}

void Sta_Charts::on_pushButton_clicked()
{
    m_stachart2->zoomReset();
}
