#include "simudyn_diaprogress.h"
#include "ui_simudyn_diaprogress.h"



SimuDyn_DiaProgress::SimuDyn_DiaProgress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimuDyn_DiaProgress)
{
    ui->setupUi(this);


    //ui->label1->setText("0");
    //QString l= QString::number(sdmaxlamda);
    ui->lineEditnumbers->setText(" ");
    ui->lineEditerro->setText(" ");

    //建立通信接口
    connect(this,&SimuDyn_DiaProgress::diatoerro,&erroanalysis,&ErroAnalysis::dealdiatoerro);
    //建立连接点击关闭按钮时候清除图像
    connect(this,&SimuDyn_DiaProgress::erroclearchart,&erroanalysis,&ErroAnalysis::dealerroclearchart);

    //建立连接点击xx按钮时候清除图像,但是不知道为撒没反应
    //初步判断是因为当前任务没有完结导致的，比如在主窗口的时候就是线程还在运行，destroyed也会没反应
    //根本原因是关闭窗口但是没有destroy窗口，也就是没有资源释放
    //可以使用Widget *w = new Widget();
    //w->setAttribute(Qt::WA_DeleteOnClose);模式
    //connect(this,&SimuDyn_DiaProgress::destroyed,
    //        [=]()
    //{   qDebug()<<"qwe";
    //}
    //        );

    //让窗口显示在屏幕中央
    erroanalysis.move ((QApplication::desktop()->width() - erroanalysis.width())/2,(QApplication::desktop()->height() - erroanalysis.height())/2);
}

SimuDyn_DiaProgress::~SimuDyn_DiaProgress()
{
    delete ui;
}

//接受正常信号
void SimuDyn_DiaProgress::dealerrodata(int numbers, int curretnumbers, double erro)
{

    //接收信号绘图，并且开始绘图
    emit diatoerro(curretnumbers,erro);
    //初始化计算状态
    ui->labelstatus->setText("正在计算");
    //初始化进度条
    ui->label->setText("已进行/规定次数");
    //初始话按键，没有计算完就不能被按下
    ui->pushButton->setEnabled(false);
    //标识符初始化
    m_flag = 0;
    //循环刷新动图
    erroanalysis.show();

    double haha;
    haha=(double)100*curretnumbers/numbers;
    //给进度条赋值
    ui->progressBar->setValue(haha);
    //QString l00= QString::number(haha);
    //ui->label1->setText(l00);  //有了进度条不用它了
    QString l1= QString::number(curretnumbers);
    ui->lineEditnumbers->setText(l1);
    QString l2= QString::number(erro);
    ui->lineEditerro->setText(l2);
    //此窗口也循环刷新
    this->show();  
}
//接收完成信号
void SimuDyn_DiaProgress::dealallisover()
{
    ui->labelstatus->setText("计算完成,在规定次数内收敛");
    ui->label->setText("最终占比");
    ui->pushButton->setEnabled(true);
    m_flag = 1;
    this->show();
}
//接收中断信号
void SimuDyn_DiaProgress::dealnotwork()
{
    ui->labelstatus->setText("迭代次数超出限额，本次计算已停止");
    ui->pushButton->setEnabled(true);
    m_flag = 1;
    this->show();
}

//关闭窗口,并且清空上次做的图像，否则会冲突
void SimuDyn_DiaProgress::on_pushButton_clicked()
{
    this->hide();
    erroanalysis.hide();
    //判断一下，计算结束并且关闭的时候才清空
    emit erroclearchart();
}

//重写窗口关闭事件
void SimuDyn_DiaProgress::closeEvent(QCloseEvent *)
{
    switch (m_flag)
    {
        case 0: NULL;break;   //没计算完
        case 1: emit erroclearchart();break;  //计算结束
        default:break;
    }
    erroanalysis.hide();
}
