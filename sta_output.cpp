#include "sta_output.h"
#include "ui_sta_output.h"

using namespace std;

//定义变量储存最大最小数据
double stamaxalpha,stamaxq;
double Salphaoutput[100];
double SQoutput[100];
int stanumber_1;
double  sD_output, sdm_output, salpha0_output, sfi_output, sfe_output, sFr_output, sFa_output, sM_output;
double stadelta_a,stadelta_r,sta_theta;


Sta_Output::Sta_Output(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sta_Output)
{
    ui->setupUi(this);
    //嵌入主窗口
    setWindowFlag(Qt::CustomizeWindowHint);
    hide();
}

Sta_Output::~Sta_Output()
{
    delete ui;
}

void Sta_Output::stadealoutput(double D,double dm,double alpha0,double fi,double fe,double Fr,double Fa,double M,double staoutputdeltaa,double staoutputdeltat,double staoutputtheta,int z,QVector<double> vecsalpha,QVector<double> vecsq)
{
    stanumber_1 = z;
    sD_output = D;
    sdm_output = dm;
    salpha0_output = alpha0;
    sfi_output = fi;
    sfe_output = fe;
    sFa_output = Fa;
    sFr_output = Fr;
    sM_output = M;
    stadelta_a= staoutputdeltaa;
    stadelta_r= staoutputdeltat;
    sta_theta= staoutputtheta;
    static int j;
    for(j=0;j<z;j++)
    {
        Salphaoutput[j]=vecsalpha[j];
        SQoutput[j]=vecsq[j];
    }

    //用找到数组中最大元素的方法来设置范围
    stamaxalpha = *max_element(Salphaoutput,Salphaoutput+z);
    stamaxq = *max_element(SQoutput,SQoutput+z);

    QString stathetaoutput=QString::number(staoutputdeltaa);
    ui->lineEditstatheta->setText(stathetaoutput);
    QString stadeltaroutput= QString::number(staoutputdeltat);
    ui->lineEditstadeltar->setText(stadeltaroutput);
    QString stadeltaaoutput= QString::number(staoutputtheta);
    ui->lineEditstadeltaa->setText(stadeltaaoutput);
    QString staalphamax= QString::number(stamaxalpha);
    ui->lineEditstamaxalpha->setText(staalphamax);
    QString staqmax= QString::number(stamaxq);
    ui->lineEditstamaxq->setText(staqmax);

}

//保存文本文档
void Sta_Output::on_pushButtonstaoutput_clicked()
{
    //确认保存路径
    QString datasavefile_name = QFileDialog::getSaveFileName(this,"分析结果",".","文本文档(*.txt)");
    //开始保存
    QFile datasavesta_1_file(datasavefile_name);
    if (!datasavesta_1_file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QTextStream stadata_1_out(&datasavesta_1_file);

    //设置输出文字格式，使得中文也能输出
    //QSettings settings(datasavefile_name, QSettings::IniFormat);
    //settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    stadata_1_out.setCodec(QTextCodec::codecForName("utf-8"));

    //开始写入
    stadata_1_out << tr("输入数据:")  << "\n";
    stadata_1_out << tr("滚动体个数(z) = ") << stanumber_1 << "\n";
    stadata_1_out << tr("初始接触角(alpha0) = ") << salpha0_output <<tr("(°)")<< "\n";
    stadata_1_out << tr("滚动体直径(D) = ") << sD_output << "(mm)"<<"\n";
    stadata_1_out << tr("轴承节圆直径(dm) = ") << sdm_output << "(mm)"<<"\n";
    stadata_1_out << tr("外圈沟曲率半径系数(fe) = ") << sfe_output << "\n";
    stadata_1_out << tr("内圈沟曲率半径系数(fi) = ") << sfi_output << "\n";
    stadata_1_out << tr("径向载荷(Fr) = ") << sFr_output <<"(N)"<< "\n";
    stadata_1_out << tr("轴向载荷(Fa) = ") << sFa_output << "(N)" << "\n";
    stadata_1_out << tr("力矩(M) = ") << sM_output << "(N*mm)" << "\n"<<"\n";

    stadata_1_out << tr("分析结果:")  << endl;
    stadata_1_out << tr("径向位移(delta_r) = ") << stadelta_r << "(mm)" << "\n";
    stadata_1_out << tr("轴向位移(delta_a) = ") << stadelta_a << "(mm)" << "\n";
    stadata_1_out << tr("接触角位移(theta) = ") << sta_theta << tr("(°)") << "\n"<<"\n";

    //设置输出文本格式
    stadata_1_out <<"\n"<<"\n";
    stadata_1_out.setFieldAlignment(QTextStream::AlignLeft);
    stadata_1_out.setFieldWidth(20);
    stadata_1_out <<tr("i") << tr("alpha/(°)") << tr("Q/(N)") <<qSetFieldWidth(0)<< endl;
    //草了这个换行也要占用setFieldWidth
    for (int i = 0; i < stanumber_1; i++)
    {
        stadata_1_out <<qSetFieldWidth(20)<< i + 1 <<Salphaoutput[i] <<SQoutput[i] <<qSetFieldWidth(0)<<endl;
    }
    datasavesta_1_file.close();
    //this->hide();
}

////退出界面
//void Sta_Output::on_pushButton_clicked()
//{
//    this->hide();
//}
