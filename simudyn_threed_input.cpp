#include "simudyn_threed_input.h"
#include "ui_simudyn_threed_input.h"

int M_input,N_input;
double XIN_input,YIN_input,XOUT_input,YOUT_input;
double Pressure_3D[2048][2048];
double P0_input;

SimuDyn_ThreeD_Input::SimuDyn_ThreeD_Input(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimuDyn_ThreeD_Input)
{
    ui->setupUi(this); 
    //设置阴影
    setShadows3D(ui->lineEdit_M);
    setShadows3D(ui->lineEdit_N);
    setShadows3D(ui->lineEdit_XIN);
    setShadows3D(ui->lineEdit_XOUT);
    setShadows3D(ui->lineEdit_YIN);
    setShadows3D(ui->lineEdit_YOUT);

    //设置初始值
    ui->lineEdit_M->setText("128");
    ui->lineEdit_N->setText("128");
    ui->lineEdit_XIN->setText("-2.5");
    ui->lineEdit_XOUT->setText("1.5");
    ui->lineEdit_YIN->setText("-2");
    ui->lineEdit_YOUT->setText("2");
}

SimuDyn_ThreeD_Input::~SimuDyn_ThreeD_Input()
{
    delete ui;
}

//阴影函数
void SimuDyn_ThreeD_Input::setShadows3D(QLineEdit *lineedit)
{
    //设置边框的阴影效果
    m_staeffect = new QGraphicsDropShadowEffect(lineedit);
    m_staeffect->setBlurRadius(5);
    m_staeffect->setColor(Qt::black);
    m_staeffect->setOffset(0,0);
    //把阴影给需要的lineedit
    lineedit->setGraphicsEffect(m_staeffect);
}

//接收到最大赫兹力P0
void SimuDyn_ThreeD_Input::dealMainWindowToThreeDInput(double p0)
{
    QString qstring_p0 = QString::number(p0);
    ui->label_p0->setText(qstring_p0);
    P0_input = p0;
}



//关闭按钮
void SimuDyn_ThreeD_Input::on_pushButton_close_clicked()
{
    this->hide();
}

//重置按钮
void SimuDyn_ThreeD_Input::on_pushButton_reset_clicked()
{
    ui->lineEdit_M->setText("128");
    ui->lineEdit_N->setText("128");
    ui->lineEdit_XIN->setText("-2.5");
    ui->lineEdit_XOUT->setText("1.5");
    ui->lineEdit_YIN->setText("-2");
    ui->lineEdit_YOUT->setText("2");
}

//计算按钮
void SimuDyn_ThreeD_Input::on_pushButton_calculate_clicked()
{
    QString mid1 = ui->lineEdit_M->text();
    M_input = mid1.toInt();
    QString mid2 = ui->lineEdit_N->text();
    N_input = mid2.toInt();
    QString mid3 = ui->lineEdit_XIN->text();
    XIN_input = mid3.toDouble();
    QString mid4 = ui->lineEdit_YIN->text();
    YIN_input = mid4.toDouble();
    QString mid5 = ui->lineEdit_XOUT->text();
    XOUT_input = mid5.toDouble();
    QString mid6 = ui->lineEdit_YOUT->text();
    YOUT_input = mid6.toDouble();
    calculate(M_input,N_input,XIN_input,YIN_input,XOUT_input,YOUT_input);
}

//计算得出矩阵
void SimuDyn_ThreeD_Input::calculate(int M, int N, double XIN, double YIN, double XOUT, double YOUT)
{
    double dx,dy;
    double xy,x,y;
    dx = (XOUT - XIN)/M ;
    dy = (YOUT - YIN)/N ;
    int i=0;
    int j=0;
    for(i=0;i<=M;i++)
    {
        x = XIN + dx * i ;
        for (j=0;j<=N;j++)
        {
            y = YIN + dy * j ;
            xy = x * x + y * y ;
            if(xy <= 1)
            {
                Pressure_3D[i][j] = P0_input * sqrt(1-xy);
            }
            else if(xy>1)
            {
                Pressure_3D[i][j] = 0;
            }
        }
    }
   //弹出窗口进行选择
   SetMessageBoxSize msgBox;   //自己写了一个类，可以设置size的继承于QMessageBox的类
   msgBox.AutosetSize(400,100);
   msgBox.setIcon(QMessageBox::Information); //设置类型
   msgBox.setWindowTitle("提示");
   msgBox.setText("计算结束");
   msgBox.setInformativeText("是否保存应力计算结果为文件形式?");
   msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Discard);
   int ret = msgBox.exec();
   switch (ret)
   {
    case QMessageBox::Ok:
    {
       saveasfile();
       this->hide();
    }
    break;
    case QMessageBox::Discard:
    {
       this->hide();
    }
    break;
   }
}

//保存成我的文档的形式
void SimuDyn_ThreeD_Input::saveasfile()
{
    //确认保存路径
    QString datasavefile_name = QFileDialog::getSaveFileName(this,"3D分析结果",".","文本文档(*.3Ddata)");
    //开始保存
    QFile datasavesta_1_file(datasavefile_name);
    if (!datasavesta_1_file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QTextStream sddata_1_out(&datasavesta_1_file);

    //设置输出文字格式，使得中文也能输出
    //QSettings settings(datasavefile_name, QSettings::IniFormat);
    //settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    sddata_1_out.setCodec(QTextCodec::codecForName("utf-8"));

    //开始写入
    for(int i=0;i<=M_input;i++)
    {
        for(int j=0;j<=N_input;j++)
        {
            if(j==N_input)
            {
                sddata_1_out << Pressure_3D[i][j] <<"\n";
            }
            else
            {
                sddata_1_out << Pressure_3D[i][j] <<"\t";
            }
        }
    }
    datasavesta_1_file.close();
}
