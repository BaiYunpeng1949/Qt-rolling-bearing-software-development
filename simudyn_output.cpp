#include "simudyn_output.h"
#include "ui_simudyn_output.h"

//为了使用比较大小函数，包含以下头文件和内存拓展
#include<math.h>
#include<QDebug>
using namespace std;

//定义变量储存最大最小数据
double Salphaeoutput[100],sdmaxalphae;
double Salphaioutput[100],sdmaxalphai;
double SQeoutput[100],sdmaxqe;
double SQioutput[100],sdmaxqi;
double Swcoutput[100],sdmaxwc;
double Swboutput[100],sdmaxwb;
double SMgoutput[100],sdmaxMg;
double SFcoutput[100],sdmaxFc;
double Suoutput[100],sdmaxu;
double SRioutput[100],sdmaxSRi;
double SReoutput[100],sdmaxSRe;
double Slamdaoutput[100],sdmaxlamda;

double sdminalphaeo;
double sdminalphaio;
double sdminqeo;
double sdminqio;
double sdminwco;
double sdminwbo;
double sdminMgo;
double sdminFco;
double sdminuo;
double sdminSRio;
double sdminSReo;
double sdminlamdao;

int sd_1_number,sd_1_numbers,sd_1_OR;
double sd_1_E,sd_1_v,sd_1_rho,sd_1_alpha0,sd_1_D,sd_1_di,sd_1_fe,sd_1_fi,sd_1_Fr,sd_1_Fa,sd_1_M,sd_1_ni,sd_1_omiga,sd_1_omiga1,sd_1_omiga2,sd_1_erro;
double sd_1_Deltaa,sd_1_Deltar,sd_1_theta;


SimuDyn_Output::SimuDyn_Output(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimuDyn_Output)
{
    ui->setupUi(this);
    //嵌入主窗口
    setWindowFlag(Qt::CustomizeWindowHint);
    hide();
}

SimuDyn_Output::~SimuDyn_Output()
{
    delete ui;
}

void SimuDyn_Output::sddealoutput(double E, double v, double rho, double alpha0, double D, double di, double fe, double fi, double Fr, double Fa, double M, double ni, double omiga, double omiga1, double omiga2, int OR, double erro, int numbers,int z, double Dthetat, double Ddeltaat, double Ddeltart, QVector<double> vecsdlamdat, QVector<double> vecsdalphaet, QVector<double> vecsdalphait, QVector<double> vecsdut, QVector<double> vecsdQet, QVector<double> vecsdQit, QVector<double> vecsdFct, QVector<double> vecsdMgt, QVector<double> vecsdwbt, QVector<double> vecsdwct, QVector<double> vecsdSRet, QVector<double> vecsdSRit)
{
    sd_1_number = z;
    sd_1_E = E;
    sd_1_v = v;
    sd_1_rho = rho;
    sd_1_alpha0 = alpha0;
    sd_1_D = D;
    sd_1_di = di;
    sd_1_fe = fe;
    sd_1_fi = fi;
    sd_1_Fr = Fr;
    sd_1_Fa = Fa;
    sd_1_M = M;
    sd_1_ni = ni;
    sd_1_omiga = omiga;
    sd_1_omiga1 = omiga1;
    sd_1_omiga2 = omiga2;
    sd_1_OR = OR;
    sd_1_erro = erro;
    sd_1_numbers = numbers;
    sd_1_Deltar = Ddeltart;
    sd_1_Deltaa = Ddeltaat;
    sd_1_theta = Dthetat;

    static int j;
    for(j=0;j<z;j++)
    {
        Salphaeoutput[j]=vecsdalphaet[j];
        Salphaioutput[j]=vecsdalphait[j];
        SQeoutput[j]=vecsdQet[j];
        SQioutput[j]=vecsdQit[j];
        Swcoutput[j]=vecsdwct[j];
        Swboutput[j]=vecsdwbt[j];
        SMgoutput[j]=vecsdMgt[j];
        SFcoutput[j]=vecsdFct[j];
        Suoutput[j]=vecsdut[j];
        SRioutput[j]=vecsdSRit[j];
        SReoutput[j]=vecsdSRet[j];
        Slamdaoutput[j]=vecsdlamdat[j];
    }

    //用找到数组中最大元素的方法来设置范围
    sdmaxalphae = *max_element(Salphaeoutput,Salphaeoutput+z);
    sdmaxalphai = *max_element(Salphaioutput,Salphaioutput+z);
    sdmaxqe=*max_element(SQeoutput,SQeoutput+z);
    sdmaxqi=*max_element(SQioutput,SQioutput+z);
    sdmaxwc=*max_element(Swcoutput,Swcoutput+z);
    sdmaxwb=*max_element(Swboutput,Swboutput+z);
    sdmaxMg=*max_element(SMgoutput,SMgoutput+z);
    sdmaxFc=*max_element(SFcoutput,SFcoutput+z);
    sdmaxu=*max_element(Suoutput,Suoutput+z);
    sdmaxSRi=*max_element(SRioutput,SRioutput+z);
    sdmaxSRe=*max_element(SReoutput,SReoutput+z);
    sdmaxlamda=*max_element(Slamdaoutput,Slamdaoutput+z);

    //找最小元素
    sdminalphaeo = *min_element(Salphaeoutput,Salphaeoutput+z);
    sdminalphaio = *min_element(Salphaioutput,Salphaioutput+z);
    sdminqeo=*min_element(SQeoutput,SQeoutput+z);
    sdminqio=*min_element(SQioutput,SQioutput+z);
    sdminwco=*min_element(Swcoutput,Swcoutput+z);
    sdminwbo=*min_element(Swboutput,Swboutput+z);
    sdminMgo=*min_element(SMgoutput,SMgoutput+z);
    sdminFco=*min_element(SFcoutput,SFcoutput+z);
    sdminuo=*min_element(Suoutput,Suoutput+z);
    sdminSRio=*min_element(SRioutput,SRioutput+z);
    sdminSReo=*min_element(SReoutput,SReoutput+z);
    sdminlamdao=*min_element(Slamdaoutput,Slamdaoutput+z);



    QString sdtheta=QString::number(Dthetat);
    ui->lineEditsdtheta->setText(sdtheta);
    QString stadeltaroutput= QString::number(Ddeltart);
    ui->lineEditsddeltar->setText(stadeltaroutput);
    QString stadeltaaoutput= QString::number(Ddeltaat);
    ui->lineEditsddeltaa->setText(stadeltaaoutput);

    QString a= QString::number(sdmaxalphae);
    ui->lineEditsdalphae->setText(a);
    QString b= QString::number(sdmaxalphai);
    ui->lineEditsdalphai->setText(b);
    QString c= QString::number(sdmaxqe);
    ui->lineEditsdQe->setText(c);
    QString d= QString::number(sdmaxqi);
    ui->lineEditsdQi->setText(d);
    QString e= QString::number(sdmaxwc);
    ui->lineEditsdwc->setText(e);
    QString f= QString::number(sdmaxwb);
    ui->lineEditsdwb->setText(f);
    QString g= QString::number(sdmaxMg);
    ui->lineEditsdMg->setText(g);
    QString h= QString::number(sdmaxFc);
    ui->lineEditsdFc->setText(h);
    QString i= QString::number(sdmaxu);
    ui->lineEditsdu->setText(i);
    QString j2= QString::number(sdmaxSRe);
    ui->lineEditsdSRe->setText(j2);
    QString k= QString::number(sdmaxSRi);
    ui->lineEditsdSRi->setText(k);
    QString l= QString::number(sdmaxlamda);
    ui->lineEditsdlamda->setText(l);

    QString a2= QString::number(sdminalphaeo);
    ui->lineEditsdalphae_2->setText(a2);
    QString b2= QString::number(sdminalphaio);
    ui->lineEditsdalphai_2->setText(b2);
    QString c2= QString::number(sdminqeo);
    ui->lineEditsdQe_2->setText(c2);
    QString d2= QString::number(sdminqio);
    ui->lineEditsdQi_2->setText(d2);
    QString e2= QString::number(sdminwco);
    ui->lineEditsdwc_2->setText(e2);
    QString f2= QString::number(sdminwbo);
    ui->lineEditsdwb_2->setText(f2);
    QString g2= QString::number(sdminMgo);
    ui->lineEditsdMg_2->setText(g2);
    QString h2= QString::number(sdminFco);
    ui->lineEditsdFc_2->setText(h2);
    QString i2= QString::number(sdminuo);
    ui->lineEditsdu_2->setText(i2);
    QString j22= QString::number(sdminSReo);
    ui->lineEditsdSRe_2->setText(j22);
    QString k2= QString::number(sdminSRio);
    ui->lineEditsdSRi_2->setText(k2);
    QString l2= QString::number(sdminlamdao);
    ui->lineEditsdlamda_2->setText(l2);


}


//按下按键读取txt文档
void SimuDyn_Output::on_pushButtonsdoutput_clicked()
{
    //确认保存路径
    QString datasavefile_name = QFileDialog::getSaveFileName(this,"分析结果",".","文本文档(*.txt)");
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
    sddata_1_out << tr("输入数据:")  << "\n";
    sddata_1_out << tr("滚动体个数(z) = ") << sd_1_number << "\n";
    sddata_1_out << tr("初始接触角(alpha0) = ") << sd_1_alpha0 <<tr("(°)")<< "\n";
    sddata_1_out << tr("滚动体直径(D) = ") << sd_1_D << "(mm)"<<"\n";
    sddata_1_out << tr("轴承节圆直径(dm) = ") << sd_1_di << "(mm)"<<"\n";
    sddata_1_out << tr("外圈沟曲率半径系数(fe) = ") << sd_1_fe << "\n";
    sddata_1_out << tr("内圈沟曲率半径系数(fi) = ") << sd_1_fi << "\n";
    sddata_1_out << tr("径向载荷(Fr) = ") << sd_1_Fr <<"(N)"<< "\n";
    sddata_1_out << tr("轴向载荷(Fa) = ") << sd_1_Fa << "(N)" << "\n";
    sddata_1_out << tr("力矩(M) = ") << sd_1_M << "(N*mm)" << "\n";
    sddata_1_out << tr("材料杨氏模量(E) = ") << sd_1_E << "(N/mm^3)" << "\n";
    sddata_1_out << tr("泊松比(v) = ") << sd_1_v << "\n";
    sddata_1_out << tr("引导方式(OR) = ") << sd_1_OR <<"\n";
    sddata_1_out << tr("位移修正系数(omiga) = ") << sd_1_omiga << "\n";
    sddata_1_out << tr("姿态角修正系数(omiga1) = ") << sd_1_omiga1 << "\n";
    sddata_1_out << tr("摩擦修正系数(omiga2) = ") << sd_1_omiga2 << "\n";
    sddata_1_out << tr("滚动体材料密度(rho) = ") << sd_1_rho <<"(kg/m^3)"<< "\n";
    sddata_1_out << tr("轴向载荷(numbers) = ") << sd_1_numbers << "(N)" << "\n";
    sddata_1_out << tr("力矩(erro) = ") << sd_1_erro << "(N*mm)" << "\n";
    sddata_1_out << tr("内圈转速(ni) = ") << sd_1_ni << "(rpm)"<< "\n"<<"\n";

    sddata_1_out << tr("分析结果:")  << endl;
    sddata_1_out << tr("径向位移(delta_r) = ") << sd_1_Deltar << "(mm)" << "\n";
    sddata_1_out << tr("轴向位移(delta_a) = ") << sd_1_Deltaa << "(mm)" << "\n";
    sddata_1_out << tr("接触角位移(theta) = ") << sd_1_theta << tr("(°)") << "\n"<<"\n";

    //设置输出文本格式
    //第一组
    sddata_1_out<<"\n"<<"\n";
    sddata_1_out.setFieldAlignment(QTextStream::AlignLeft);
    sddata_1_out <<qSetFieldWidth(20)<<tr("i")<<tr("alphai/(°)") << tr("alphae/(°)") << tr("lamda/(°)") << tr("u") << qSetFieldWidth(0)<< endl;
    for (int i = 0; i < sd_1_number; i++)
    {
        sddata_1_out <<qSetFieldWidth(20)<< i + 1 <<Salphaioutput[i] <<Salphaeoutput[i] <<Slamdaoutput[i]<<Suoutput[i]<<qSetFieldWidth(0)<< endl;
    }

    //第二组
    sddata_1_out<<"\n"<<"\n";
    sddata_1_out <<qSetFieldWidth(20)<<tr("i") << tr("Qi/(N)") << tr("Qe/(N)") << tr("Fc/(N)") << tr("Mg/(N*m)")<< qSetFieldWidth(0)<< endl;
    for (int i = 0; i < sd_1_number; i++)
    {
        sddata_1_out <<qSetFieldWidth(20)<< i + 1 <<SQioutput[i] <<SQeoutput[i] <<SFcoutput[i]<<SMgoutput[i]<< qSetFieldWidth(0)<<endl;
    }

    //第三组
    sddata_1_out<<"\n"<<"\n";
    sddata_1_out <<qSetFieldWidth(20)<<tr("i") << tr("wc/(rad/s)") << tr("wb/(rad/s)") << tr("SRi") << tr("SRe")<< qSetFieldWidth(0)<< endl;
    for (int i = 0; i < sd_1_number; i++)
    {
        sddata_1_out <<qSetFieldWidth(20)<< i + 1 <<Swcoutput[i] <<Swboutput[i] <<SRioutput[i]<<SReoutput[i]<< qSetFieldWidth(0)<<endl;
    }

    datasavesta_1_file.close();
    //this->hide();
}

////关闭窗口
//void SimuDyn_Output::on_pushButton_clicked()
//{
//    this->hide();
//}
