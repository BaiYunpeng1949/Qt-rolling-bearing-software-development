#include "erroanalysis.h"
#include "ui_erroanalysis.h"

ErroAnalysis::ErroAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ErroAnalysis)
{
    ui->setupUi(this);

    //点击计算按键才开始画图
    //初始化动图背景
    //初始化一个chart
    m_errochart = new QChart();
    //初始化一条曲线
    m_erroline = new QSplineSeries();
    //初始化一个画笔，一个刷子
    //定义画笔和刷子
    QPen penx,peny,penline;
    QBrush brush;

    //初始线
    m_erroline->append(0,1); //曲线上的点的初始化
    //设置粗细
    penline.setStyle(Qt::SolidLine);
    penline.setWidth(2);    //2像素点线宽
    penline.setColor(Qt::blue);
    m_erroline->setPen(penline);

    //设置颜色
    //m_erroline->setColor(QColor(0,0,255));

    //将线加入图表
    m_errochart->addSeries(m_erroline);


    //初始坐标轴
    m_erroaxisx = new QValueAxis();
    m_erroaxisx->setRange(0,5);
    m_erroaxisx->setTitleText("计算次数");
    m_erroaxisx->setLabelFormat("%d");


    //让坐标轴适当变粗
    penx.setStyle(Qt::SolidLine);
    penx.setWidth(2);    //2像素点线宽
    penx.setColor(Qt::black);
    m_erroaxisx->setLinePen(penx);
    m_erroaxisx->setLineVisible(true);
    //m_erroaxisx->setLinePenColor(Qt::blue);

    m_erroaxisy = new QValueAxis();
    m_erroaxisy->setRange(0,1.0);
    m_erroaxisy->setTitleText("计算误差");

    peny.setStyle(Qt::SolidLine);
    peny.setWidth(2);    //2像素点线宽
    peny.setColor(Qt::black);
    m_erroaxisy->setLinePen(peny);
    m_erroaxisy->setLineVisible(true);

    //坐标轴字体设置
    //设置坐标轴标签和标注字体大小
    QFont labelfontd("Microsoft YaHei",10,75);
    m_erroaxisx->setLabelsFont(labelfontd);
    m_erroaxisy->setLabelsFont(labelfontd);


    //将坐标与系列绑定
    m_errochart->addAxis(m_erroaxisx,Qt::AlignBottom);
    m_errochart->addAxis(m_erroaxisy,Qt::AlignLeft);
    //绑定坐标轴与line
    m_erroline->attachAxis(m_erroaxisx);
    m_erroline->attachAxis(m_erroaxisy);
    //隐藏图例
    m_errochart->legend()->hide();
    m_errochart->layout()->setContentsMargins(0,0,0,0);

    //设置图标主题
    //m_errochart->setTheme(QtCharts::QChart::ChartThemeBlueIcy);

    //绑定视图
    ui->widgeterro->setChart(m_errochart);

    //定位在屏幕中间
    this->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    //初始化控件
    ui->pushButtonclose->setEnabled(false);
    //玩具初始化
    m_count = 1;
}

ErroAnalysis::~ErroAnalysis()
{
    delete ui;
}

//实时更新数据
void ErroAnalysis::dealthreadtoerro(int currentnumbers, double erro,qint64 timegoesby)
{
    //只要在画图，标志为就是0
    m_flag = 0;
    ui->pushButtonclose->setEnabled(false);
    ui->pushButtonstop->setEnabled(true);

    //显示,并且显示在屏幕中央
    this->show();

    //设置当前坐标轴范围
    if(currentnumbers>5)
    {
    m_erroaxisx->setRange(0,currentnumbers);
    }

    //这里发现需要把曲线定义成成员变量,读取新数据，加进来
    //并且为了清空上一次的曲线，也需要把QVector<QPointF> pts设置成成员变量来清空
    m_pts = m_erroline ->pointsVector();
    m_pts.append(QPointF(currentnumbers,erro));
    //更新系列
    m_erroline->replace(m_pts);
    ////绑定坐标轴与line
    //m_erroline->attachAxis(m_erroaxisx);
    //m_erroline->attachAxis(m_erroaxisy);


    //状态设置
    switch (m_count%3)
    {
        case 1:ui->label_status->setText("正在计算.");break;
        case 2:ui->label_status->setText("正在计算..");break;
        case 0:ui->label_status->setText("正在计算...");break;
        default:break;
    }
    m_count++;

    m_time = double(int(timegoesby/100)*0.1);
    QString l0= QString::number(m_time);
    ui->label_time->setText(l0);
    //数据读入：
    QString l1= QString::number(currentnumbers);
    ui->label_numbers->setText(l1);
    QString l2= QString::number(erro);
    ui->label_erro->setText(l2);
}

//清除上一次的图像
void ErroAnalysis::dealerroclearchart()
{
    //清空QVector中的数据
    m_pts.clear();
    //清空QVector中的内存
    QVector <QPointF> ().swap(m_pts);
    m_erroline->replace(m_pts);

    //同时坐标轴也需要清空，回复默认设置
    m_erroaxisx->setRange(0,5);
    //玩具初始化
    m_count = 1;
}

//线程结束
void ErroAnalysis::threadisover()
{
    //标志为置为1
    m_flag = 1;
    ui->pushButtonclose->setEnabled(true);
    ui->pushButtonstop->setEnabled(false);
    ui->label_status->setText("计算完成 ！");
}

//线程中断
void ErroAnalysis::threadinterruptted()
{
    //标志为置为1
    m_flag = 1;
    ui->pushButtonclose->setEnabled(true);
    ui->pushButtonstop->setEnabled(false);
    ui->label_status->setText("计算中止 ");
    int ret = QMessageBox::warning(this,"失败","规定次数内不收敛，请重新输入数据");
    switch (ret)
    {
    case QMessageBox::Ok :
        this->close(); //隐藏窗口,用hide话会失败
        break;
    default:
        break;
    }
}

//重写关闭事件
void ErroAnalysis::closeEvent(QCloseEvent *)
{
    switch (m_flag)
    {
        case 0: break;   //没计算完
        case 1: dealerroclearchart();break;  //计算结束
        default:break;
    }
}



//关闭按钮
void ErroAnalysis::on_pushButtonclose_clicked()
{
    //this->hide();
    //dealerroclearchart();
    this->close();
}

//中止计算按钮
void ErroAnalysis::on_pushButtonstop_clicked()
{
    emit stopthread();//发送信号给线程，让它给自己的父对象发送信号提醒

    ui->label_status->setText("计算中止 ");
    SetMessageBoxSize msgBox;   //自己写了一个类，可以设置size的继承于QMessageBox的类
    msgBox.AutosetSize(200,100);
    msgBox.setIcon(QMessageBox::Warning); //设置类型
    msgBox.setWindowTitle("警告");
    msgBox.setText("  计算已中止");
    //msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Ok);
    //msgBox.setDefaultButton(QMessageBox::Save);

    int ret = msgBox.exec();
    switch (ret)
    {
    case QMessageBox::Ok :
        m_flag = 1;
        this->close();
        //dealerroclearchart(); //销毁痕迹，为下次做准备
        //this->hide(); //隐藏窗口
        break;
    default:
        break;
    }

}
