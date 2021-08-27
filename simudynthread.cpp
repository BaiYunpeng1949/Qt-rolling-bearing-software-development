#include "simudynthread.h"

//引入功能头文件
#include<QVector>
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include<math.h>

//参数最后的t是线程thread的意思
using namespace std;
double pepst[300];
int iepst;
double Dlamdat[100], Dalphaet[100], Dalphait[100], DQet[100], DQit[100], DFct[100], DMgt[100], Dwct[100], Dwbt[100], Dut[100], DSRet[100], DSRit[100], Dthetat,Ddeltart,Ddeltaat;
QVector<double> vecsdlamdat(100);
QVector<double> vecsdalphaet(100);
QVector<double> vecsdalphait(100);
QVector<double> vecsdut(100);
QVector<double> vecsdQet(100);
QVector<double> vecsdQit(100);
QVector<double> vecsdFct(100);
QVector<double> vecsdMgt(100);
QVector<double> vecsdwct(100);
QVector<double> vecsdwbt(100);
QVector<double> vecsdSRet(100);
QVector<double> vecsdSRit(100);
double P0_SimuDyn; //储存最大赫兹载荷的


SimuDynThread::SimuDynThread(QObject *parent) : QObject(parent)
{ 
    //关闭子窗口的时候要同时释放内存
    //simudyndia= new SimuDyn_DiaProgress();
    //simudyndia->setAttribute(Qt::WA_DeleteOnClose); //这个可以destroy应有的东西
    //erroanalysis = new ErroAnalysis();
    //erroanalysis->setAttribute(Qt::WA_DeleteOnClose);

    //连接自己与对话框
    //正常数据传递
    connect(this,&SimuDynThread::sdthreadforerro,&erroanalysis,&ErroAnalysis::dealthreadtoerro);
    //结束
    connect(this,&SimuDynThread::sdthreadisallover,&erroanalysis,&ErroAnalysis::threadisover);
    //异常
    connect(this,&SimuDynThread::sdthreadnotwork,&erroanalysis,&ErroAnalysis::threadinterruptted);
    //中止
    connect(&erroanalysis,&ErroAnalysis::stopthread,
            [=]()
            {
                m_stop =  true; //中止标志位置为一
                emit stopdynthread();
            }
            );
}


//第一个子函数
double Hertz_contact_cal(double &w, double &E, double &v, double &r11, double &r12, double &r21, double &r22, double &a, double &ake)
{
    //该函数用于计算赫兹接触参数
    double b,p0;//w//施加的载荷, E//物体弹性模量, v//两物体速度，取相同,
    //r11和r12//物体1当量曲率半径, r21和r22//物体2当量曲率半径
    //a//赫兹接触椭圆长半轴长,  ake//椭圆比ke=b/a,
    double pi, E0, rx, ry, R,Ee;
    pi = 3.1415926535897932;
    E0 = 2.0 / ((1.0 - v * v) / E + (1.0 - v * v) / E);//当量弹性模量
    rx = 1.0 / r11 + 1.0 / r21;     //r21是特别大的那个
    rx = 1.0 / rx;
    ry = 1.0 / r12 + 1.0 / r22;
    ry = 1.0 / ry;
    R = 1.0 / rx + 1.0 / ry; //当量曲率半径，两圆柱构成的间隙
    R = 1.0 / R;
    ake = 1.0339*pow((ry / rx), 0.6360);
    //qDebug()<<rx<<ry;// ry太大了
    //qDebug()<<a<<r11<<r12<<r21<<r22; //主要就是a的问题，但是根本原因是进入不了初始化地方
    //再返回去看看是r11,r12,r21,r22有什么问题
    //qDebug()<<ake; //经过检查测试数据正常
    //qDebug()<<fabs(rx - ry); //看看是否会进入循环
    //全部都是大于一百的数，不进入循环a就没办法初始化
    if (fabs(rx - ry) <= 0.00001)   //改成误差大进行计算，可以了！不过这句话也就没啥存在的价值了
    {
        ake = 1.0;
    }
    Ee = 1.0003 + 0.5968*(rx / ry);
    a = 6.0*ake*ake*Ee*R*w / (pi*E0);
    a = pow(a, 0.333333333333);
    b = a / ake;
    p0 = 1.5*w / pi / a / b / 1000.0; //最大赫兹压力
    P0_SimuDyn = p0 ; //得到数据传回去画图用
    return 0;
}



//第二个子函数
double elliptic_integral(double &ake, double &Et, double &Kt)
{
    //这个子程序是用10点高斯 - 勒让德方法计算椭圆积分
    //elliptic_integral(ake, s1, s2)  椭圆积分
    double pi, a, b, dx;// ake, Et//第二类椭圆积分, Kt//模数;E（k,ake）
    double w[5], c[5], y1[2], y2[2];
    pi = 4.0*atan(1.0);
    a = 0.0;
    b = pi / 2.0;
    c[0] = 0.1488743389; c[1] = 0.4333953941; c[2] = 0.6794095682; c[3] = 0.8650633666; c[4] = 0.9739065285;
    w[0] = 0.2955242247; w[1] = 0.2692667193; w[2] = 0.2190863625; w[3] = 0.1494513491; w[4] = 0.0666713443;
    Et = 0.0;
    Kt = 0.0;
    for (int i = 0; i < 5; i++)
    {
        dx = 0.5*(b - a)*c[i];
        //definite_integration(ake, 0.5*(b + a) + dx, y1);   得注意一下 弧度制和角度制的转换
        y1[0] = pow((1.0 - (1.0 - (1.0 / ake / ake))*sin(0.5*(b + a) + dx)*sin(0.5*(b + a) + dx)), 0.5);
        y1[1] = pow((1.0 - (1.0 - (1.0 / ake / ake))*sin(0.5*(b + a) + dx)*sin(0.5*(b + a) + dx)), (-0.5));
        //definite_integration(ake, 0.5*(b + a) - dx, y2);
        y2[0] = pow((1.0 - (1.0 - (1.0 / ake / ake))*sin(0.5*(b + a) - dx)*sin(0.5*(b + a) - dx)), 0.5);
        y2[1] = pow((1.0 - (1.0 - (1.0 / ake / ake))*sin(0.5*(b + a) - dx)*sin(0.5*(b + a) - dx)), (-0.5));
        Et = Et + w[i] * (y1[0] + y2[0]);
        Kt = Kt + w[i] * (y1[1] + y2[1]);
    }
    Et = 0.5*(b - a)*Et;
    Kt = 0.5*(b - a)*Kt;

    //external definite_integration 外部定积分
    //这个子程序是确定方程y的值
    //definite_integration(ake, x, y) 定积分
    //double ake, x, y[2];
    //y[0] = pow((1.0 - (1.0 - (1.0 / ake / ake))*sin(x)*sin(x)),0.5);
    //y[1] = pow((1.0 - (1.0 - (1.0 / ake / ake))*sin(x)*sin(x)),(-0.5));
    return 0;

}


//第三个子函数
double K_cal(double &E, double &v, double &alpha0, double &D, double &dm, double &fe, double &fi, double &ke, double &ki)
{
    //这个子程序是用10点高斯 - 勒让德法计算载荷 - 挠度因子
    double  kn,pi, gamma, rhoi, rhoe, Fpe, Fpi;//E, v, alpha0, D, dm, fe, fi,ke, ki,载荷 - 挠度因子k
    double t, h, ake, Et, Kt, Gt, deltae, deltai;
    pi = 4.0*atan(1.0);
    //注意一下又有角度转换问题
    gamma = D * cos(alpha0) / dm;
    rhoe = (4.0 - 1.0 / fe - 2.0*gamma / (1.0 + gamma)) / D;
    rhoi = (4.0 - 1.0 / fi + 2.0*gamma / (1.0 - gamma)) / D;
    Fpe = (1. / fe - 2.*gamma / (1. + gamma)) / (4. - 1. / fe - 2.*gamma / (1. + gamma));
    Fpi = (1. / fi + 2.*gamma / (1. - gamma)) / (4. - 1. / fi + 2.*gamma / (1. - gamma));
    //外圈
    t = 0.5;
    h = 0.01;
L1: t = t + h; //100
    ake = pow((1.0 / (1.0 - t * t)), 0.5);
    //椭圆积分
    elliptic_integral(ake, Et, Kt);

    Gt = Fpe - 2.0*(1.0 - t * t)*(Et - Kt) / t / t / Et - 1.0;
    if (fabs(Gt) < 0.0000001)
        goto L2;
    else if (Gt > 0.)
        goto L1;
    else if (Gt < 0.)
    {
        t = t - h;
        h = h / 2.0;
        goto L1;
    }
L2: deltae = 2.0*Kt / pi * pow(((1.0 - t * t)*pi / 2.0 / Et), (1.0 / 3.0));
    ke = (2.0*pow(2.0, 0.5) / 3.0)*E / (1.0 - pow(v, 2)) / pow(rhoe, 0.5) / pow(deltae, 1.5);
    //内圈
    t = 0.5;
    h = 0.01;
L3: t = t + h;
    //cout << t << endl;
    if (t > 0.99999999)
    {
        goto L5;
    }
    ake = pow((1.0 / (1.0 - t * t)), 0.5);
    //椭圆积分
    elliptic_integral(ake, Et, Kt);



    Gt = Fpi - 2.0*(1.0 - t * t)*(Et - Kt) / t / t / Et - 1.0;



    if (fabs(Gt) < 0.0000001)
        goto L4;
    else if (Gt > 0.)
        goto L3;
    else if (Gt < 0.)
    {
    L5:		t = t - h;
        h = h / 2.0;
        goto L3;
    }
L4: deltai = 2.0*Kt / pi * pow(((1.0 - t * t)*pi / 2.0 / Et), (1.0 / 3.0));
    ki = (2.0*pow(2.0, 0.5) / 3.0)*E / (1.0 - pow(v, 2)) / pow(rhoi, 0.5) / pow(deltai, 1.5);
    //kn
    kn = pow((1.0 / (pow((1.0 / ki), (2.0 / 3.0)) + pow((1.0 / ke), (2.0 / 3.0)))), 1.5);

    return 0;
}




//主要功能函数，也是槽函数
void SimuDynThread::dyn(double E, double v, double rho, double alpha0, double D, double di, double fe, double fi, int Z, double Fr, double Fa, double M, double ni, double omiga, double omiga1, double omiga2, int OR, double erro, int numbers)
{
    //一系列初始化
    //Killer Queen发动！
    QElapsedTimer *m_timer= new QElapsedTimer();
    m_timer->start();
    //标志位
    m_stop = false;
    m_eccess = false;


    int s;
    double pi;//omiga, omiga1, omiga2
    double de, dm, Ri, wi, mm, JJ, ke, ki, delta_r, delta_a, theta, eps, Frp, Fap, Mp;
    double c[5][5], y[5], x[5], cc[3][3], yy[3], xx[3];

    s = Z;


    double* phi = new double[s]; //double, allocatable::phi(:), A1(:), A2(:), lamda(:), eps1(:), alpha_e(:), alpha_i(:), delta_e(:), delta_i(:), u(:)
    double* A1 = new double[s];
    double* A2 = new double[s];
    double* lamda = new double[s];
    double* eps1 = new double[s];
    double* alpha_e = new double[s];
    double* alpha_i = new double[s];
    double* delta_e = new double[s];
    double* delta_i = new double[s];
    double* u = new double[s];  //！轴承径向游隙

    double* eps2 = new double[s];//double, allocatable::eps2(:), Ce(:), Ci(:), Te(:), Ti(:), wc(:), Fc(:), Mg(:), H1(:), H2(:), H3(:), H4(:), H5(:)
    double* Ce = new double[s];
    double* Ci = new double[s]; //滚珠与内滚道的油膜阻尼
    double* Te = new double[s];
    double* Ti = new double[s];//轴承转动所需的驱动力矩
    double* wc = new double[s];
    double* Fc = new double[s];
    double* Mg = new double[s];
    double* H1 = new double[s];
    double* H2 = new double[s];
    double* H3 = new double[s];
    double* H4 = new double[s];
    double* H5 = new double[s];

    double* T0 = new double[s]; //double, allocatable::T0(:), wc_alpha_e(:), wc_alpha_i(:), Mg_alpha_e(:), Mg_alpha_i(:)
    double* wc_alpha_e = new double[s];
    double* wc_alpha_i = new double[s];
    double* Mg_alpha_e = new double[s];
    double* Mg_alpha_i = new double[s];

    double* Qe = new double[s];//double, allocatable::Qe(:), Qi(:), ae(:), ai(:), akee(:), akei(:), L2e(:), L2i(:), L1e(:), L1i(:), Msie(:)
    double* Qi = new double[s];
    double* ae = new double[s];
    double* ai = new double[s];
    double* akee = new double[s];
    double* akei = new double[s];
    double* L2e = new double[s];
    double* L2i = new double[s];
    double* L1e = new double[s];
    double* L1i = new double[s];
    double* Msie = new double[s];

    double* lamdap = new double[s];//double, allocatable::lamdap(:), wb(:), SRe(:), SRi(:)
    double* wb = new double[s];
    double* wbs_i = new double[s];
    double* wbs_e = new double[s];
    double* SRe = new double[s];
    double* SRi = new double[s];


    pi = 4 * atan(1.0);
    alpha0=alpha0*pi/180;


    /*
    E = m_E;		//[N/(mm*mm)] 材料杨氏模量
    v = m_v;			        //泊松比
    rho = m_rho;				//[kg / m * *3] 滚珠密度
    alpha0 = m_alpha0 * pi / 180.0;	//[degree] 初始接触角
    D = m_D;  //滚珠直径
    di = m_di;  //内圈直径
    fe = m_fe;
    fi = m_fi;  //内圈
    Z = m_Z;
    Fr = m_Fr;
    Fa = m_Fa;    //轴承标准列轴向载荷
    M = m_M;
    ni = m_ni;   //内圈转速
    omiga = m_omiga;
    omiga1 = m_omiga1;
    omiga2 = m_omiga2;
    OR = m_OR;
    */


    de = di + 2.0*D + 2.0*(fe + fi - 1.0)*D*(1.0 - cos(alpha0));
    dm = (di + de) / 2.0;
    Ri = 0.5*dm + (fi - 0.5)*D*cos(alpha0);
    wi = 2.0*pi*ni / 60.0;
    mm = rho * pi*pow(D, 3.0)*pow(10.0, (-9.0)) / 6.0;
    JJ = rho * pi*pow(D, 5.0)*pow(10.0, (-15.0)) / 60.0;

    //call K_cal(E, v, alpha0, D, dm, fe, fi, ke, ki)
    K_cal(E, v, alpha0, D, dm, fe, fi, ke, ki);

    delta_r = 0.001;
    delta_a = 0.001;
    theta = 0.001;
    eps = 1.0;
    iepst = 0;

    while (eps > erro && m_stop == false) //这样也不行，没法running完线程函数
    {
        //cout << "当前误差为" << eps << endl;
        //m_esp = floor(eps * 100000000.0f + 0.5) / 100000000.0f;
        pepst[iepst] = eps;
        iepst++;

        //往回传送信号
        //emit sdthreadtodiagro(iepst-1,pepst[iepst-1]);    //用不上了

        //还要计算时间
        m_timeelapsed = m_timer->elapsed();
        //如果不是中止，就正常传递信号
        if(m_stop == false)
            emit sdthreadforerro(iepst-1,pepst[iepst-1],m_timeelapsed);

        //判断是否超出极限计算
        if(iepst>numbers) //第一次不算迭代
        {
            emit sdthreadnotwork();
            m_eccess = true;
            break;
        }

        //判断是否被中止了，是就跳出循环
        //if(m_stop == true)
        //{
        //    break;
        //}

        //EPS::OnPaint;
        //UpdateData(FALSE);
        //DoEvents();
        //注意有许多角度问题
            for (int j = 0; j < Z; j++)
            {
                phi[j] = 2.0*pi*(j - 1) / Z;
                A1[j] = (fi + fe - 1.0)*D*sin(alpha0) + delta_a + Ri * theta*cos(phi[j]);  //轴向内外沟曲率中心距
                A2[j] = (fi + fe - 1.0)*D*cos(alpha0) + delta_r * cos(phi[j]);  //径向内外沟曲率中心距
                lamda[j] = tan(1.0*pi / 180.0);
                eps1[j] = 1.0;
                while (fabs(eps1[j]) > pow(10.0, (-6.0)))
                {
                    //DoEvents();               我应该是用不到
                        alpha_e[j] = 12.0*pi / 180.0;
                        alpha_i[j] = 18.0*pi / 180.0;
                        delta_e[j] = 0.035;
                        delta_i[j] = 0.025;
                        u[j] = 0.01;
                        eps2[j] = 1.0;
                        while (eps2[j] > pow(10.0, (-6.0)))
                        {
                            //DoEvents();
                            Ce[j] = (fe - 0.5)*D + delta_e[j];
                            Ci[j] = (fi - 0.5)*D + delta_i[j];
                            Te[j] = dm + D * cos(alpha_e[j]);
                            //看起来这里是万恶之源，加一句标准国际单位制度
                            Ti[j] = dm - D * cos(alpha_i[j]);
                            wc[j] = wi * Ti[j] * (cos(alpha_e[j]) + lamda[j] * sin(alpha_e[j])) / (Te[j] * (cos(alpha_i[j]) + lamda[j] * sin(alpha_i[j])) + Ti[j] * (cos(alpha_e[j]) + lamda[j] * sin(alpha_e[j])));
                            Fc[j] = 0.5*mm*dm*0.001*wc[j] * wc[j];
                            Mg[j] = JJ * wc[j] * wc[j] * lamda[j] * Te[j] / D / (cos(alpha_e[j]) + lamda[j] * sin(alpha_e[j]));

                            if (delta_i[j] < 0.0)
                                delta_i[j] = 0.0;

                            if (delta_e[j] < 0.0)
                                delta_e[j] = 0.0;

                            H1[j] = Ci[j] * sin(alpha_i[j]) + Ce[j] * sin(alpha_e[j]) - A1[j];
                            H2[j] = Ci[j] * cos(alpha_i[j]) + Ce[j] * cos(alpha_e[j]) - A2[j];
                            H3[j] = ki * pow(delta_i[j], 1.5)*(sin(alpha_i[j]) + u[j] * cos(alpha_i[j])) - ke * pow(delta_e[j], 1.5)*(sin(alpha_e[j]) + u[j] * cos(alpha_e[j]));
                            H4[j] = ki * pow(delta_i[j], 1.5)*(cos(alpha_i[j]) - u[j] * sin(alpha_i[j])) - ke * pow(delta_e[j], 1.5)*(cos(alpha_e[j]) - u[j] * sin(alpha_e[j])) + Fc[j];
                            H5[j] = u[j] * ki*pow(delta_i[j], 1.5) + u[j] * ke*pow(delta_e[j], 1.5) - 2.0*Mg[j] / (D*0.001);
                            c[0][0] = Ce[j] * cos(alpha_e[j]);
                            c[0][1] = Ci[j] * cos(alpha_i[j]);
                            c[0][2] = sin(alpha_e[j]);
                            c[0][3] = sin(alpha_i[j]);
                            c[0][4] = 0.0;
                            c[1][0] = -Ce[j] * sin(alpha_e[j]);
                            c[1][1] = -Ci[j] * sin(alpha_i[j]);
                            c[1][2] = cos(alpha_e[j]);
                            c[1][3] = cos(alpha_i[j]);
                            c[1][4] = 0.0;
                            c[2][0] = -ke * pow(delta_e[j], 1.5)*(cos(alpha_e[j]) - u[j] * sin(alpha_e[j]));
                            c[2][1] = ki * pow(delta_i[j], 1.5)*(cos(alpha_i[j]) - u[j] * sin(alpha_i[j]));
                            c[2][2] = -1.5*ke*pow(delta_e[j], 0.5)*(sin(alpha_e[j]) + u[j] * cos(alpha_e[j]));
                            c[2][3] = 1.5*ki*pow(delta_i[j], 0.5)*(sin(alpha_i[j]) + u[j] * cos(alpha_i[j]));
                            c[2][4] = ki * pow(delta_i[j], 1.5)*cos(alpha_i[j]) - ke * pow(delta_e[j], 1.5)*cos(alpha_e[j]);
                            T0[j] = Te[j] * (cos(alpha_i[j]) + lamda[j] * sin(alpha_i[j])) + Ti[j] * (cos(alpha_e[j]) + lamda[j] * sin(alpha_e[j]));
                            wc_alpha_e[j] = wi * (Ti[j] * (-sin(alpha_e[j]) + lamda[j] * cos(alpha_e[j]))*T0[j] - Ti[j] * (cos(alpha_e[j]) + lamda[j] * sin(alpha_e[j]))*(-D * sin(alpha_e[j])*(cos(alpha_i[j]) + lamda[j] * sin(alpha_i[j])) + Ti[j] * (-sin(alpha_e[j]) + lamda[j] * cos(alpha_e[j])))) / T0[j] / T0[j];
                            wc_alpha_i[j] = wi * (D*sin(alpha_i[j])*(cos(alpha_e[j]) + lamda[j] * sin(alpha_e[j]))*T0[j] - Ti[j] * (cos(alpha_e[j]) + lamda[j] * sin(alpha_e[j]))*(Te[j] * (-sin(alpha_i[j]) + lamda[j] * cos(alpha_i[j])) + D * sin(alpha_i[j])*(cos(alpha_e[j]) + lamda[j] * sin(alpha_e[j])))) / T0[j] / T0[j];
                            c[3][0] = -ke * pow(delta_e[j], 1.5)*(-sin(alpha_e[j]) - u[j] * cos(alpha_e[j])) + mm * dm*0.001*wc[j] * wc_alpha_e[j];
                            c[3][1] = ki * pow(delta_i[j], 1.5)*(-sin(alpha_i[j]) - u[j] * cos(alpha_i[j])) + mm * dm*0.001*wc[j] * wc_alpha_i[j];
                            c[3][2] = -1.5*ke*pow(delta_e[j], 0.5)*(cos(alpha_e[j]) - u[j] * sin(alpha_e[j]));
                            c[3][3] = 1.5*ki*pow(delta_i[j], 0.5)*(cos(alpha_i[j]) - u[j] * sin(alpha_i[j]));
                            c[3][4] = -ki * pow(delta_i[j], 1.5)*sin(alpha_i[j]) + ke * pow(delta_e[j], 1.5)*sin(alpha_e[j]);
                            Mg_alpha_e[j] = JJ * 2.0*wc[j] * wc_alpha_e[j] * lamda[j] * Te[j] / D / (cos(alpha_e[j]) + lamda[j] * sin(alpha_e[j])) + JJ * wc[j] * wc[j] * (lamda[j] * (-D * sin(alpha_e[j]))*(cos(alpha_e[j]) + lamda[j] * sin(alpha_e[j])) - lamda[j] * Te[j] * (-sin(alpha_e[j]) + lamda[j] * cos(alpha_e[j]))) / D / (cos(alpha_e[j]) + lamda[j] * sin(alpha_e[j])) / (cos(alpha_e[j]) + lamda[j] * sin(alpha_e[j]));
                            Mg_alpha_i[j] = JJ * 2.0*wc[j] * wc_alpha_i[j] * lamda[j] * Te[j] / D / (cos(alpha_e[j]) + lamda[j] * sin(alpha_e[j]));
                            c[4][0] = -2.0*Mg_alpha_e[j] / (D*0.001);
                            c[4][1] = -2.0*Mg_alpha_i[j] / (D*0.001);
                            c[4][2] = 1.5*u[j] * ke*pow(delta_e[j], 0.5);
                            c[4][3] = 1.5*u[j] * ki*pow(delta_i[j], 0.5);
                            c[4][4] = ki * pow(delta_i[j], 1.5) + ke * pow(delta_e[j], 1.5);
                            y[0] = -H1[j];
                            y[1] = -H2[j];
                            y[2] = -H3[j];
                            y[3] = -H4[j];
                            y[4] = -H5[j];
                            //call Gauss_cal(5, c, y, x);
                            int m;
                            m = 5;
                            double jjmx[5];
                            double absmx, absa, temp, it, zz, z, sum;
                            int imax, jmax, itrue;
                            for (int k = 0; k < m; k++)
                            {
                                jjmx[k] = k + 1;
                            }
                            for (int k = 0; k < m - 1; k++)
                            {
                                absmx = 0.0;
                                imax = k;
                                jmax = k;
                                for (int j = k; j < m; j++)
                                {
                                    for (int i = k; i < m; i++)
                                    {
                                        absa = fabs(c[i][j]);
                                        if (absa > absmx)
                                        {
                                            absmx = absa;
                                            imax = i;
                                            jmax = j;
                                        }
                                    }
                                }

                                for (int j = k; j < m; j++)
                                {
                                    temp = c[k][j];
                                    c[k][j] = c[imax][j];
                                    c[imax][j] = temp;
                                }
                                temp = y[k];
                                y[k] = y[imax];
                                y[imax] = temp;
                                for (int i = 0; i < m; i++)
                                {
                                    temp = c[i][k];
                                    c[i][k] = c[i][jmax];
                                    c[i][jmax] = temp;
                                }
                                it = jjmx[k];
                                jjmx[k] = jjmx[jmax];
                                jjmx[jmax] = it;
                                zz = c[k][k];
                                for (int j = k; j < m; j++)
                                {
                                    c[k][j] = c[k][j] / zz;
                                }
                                y[k] = y[k] / zz;
                                for (int i = k + 1; i < m; i++)
                                {
                                    z = c[i][k];
                                    for (int j = k; j < m; j++)
                                    {
                                        c[i][j] = c[i][j] - c[k][j] * z;
                                    }
                                    y[i] = y[i] - y[k] * z;
                                }
                            }
                            //
                            //x[0] = y[0] / c[4][0];
                            //x[1] = y[1] / c[4][1];
                            //x[2] = y[2] / c[4][2];
                            //x[3] = y[3] / c[4][3];
                            x[4] = y[4] / c[4][4];
                            for (int k = m - 2; k >= 0; k--)
                            {
                                sum = y[k];
                                for (int j = k + 1; j < m; j++)

                                {
                                    sum = sum - x[j] * c[k][j];
                                }

                                x[k] = sum;
                            }
                            for (int j = 0; j < m; j++)
                            {
                                itrue = jjmx[j] - 1;
                                y[itrue] = x[j];
                            }
                            for (int j = 0; j < m; j++)
                            {
                                x[j] = y[j];
                            }

                            eps2[j] = max(max(max(max(fabs(x[0]), fabs(x[1])), fabs(x[2])), fabs(x[3])), fabs(x[4]));
                            alpha_e[j] = alpha_e[j] + omiga2 * x[0];
                            alpha_i[j] = alpha_i[j] + omiga2 * x[1];
                            delta_e[j] = delta_e[j] + omiga2 * x[2];
                            delta_i[j] = delta_i[j] + omiga2 * x[3];
                            u[j] = u[j] + omiga2 * x[4];
                        }
                        Qe[j] = ke * pow(delta_e[j], 1.5);
                        Qi[j] = ki * pow(delta_i[j], 1.5);
                        switch (OR)
                        {
                        case(0):
                            //call Hertz_contact_cal(Qe[j], E, v, 0.5*D, 0.5*D, -Te[j] / 2.0 / cos(alpha_e[j]), -fe * D, ae[j], akee[j])
                            double r11, r12, r21, r22, r210, r220;
                            r11 = 0.5*D;
                            r12 = 0.5*D;
                            r21 = -Te[j] / 2.0 / cos(alpha_e[j]); //现在唯一可能出问题的地方就在这里了
                            //qDebug()<<Te[j]<<alpha_e[j]<<cos(alpha_e[j])<<Te[j];
                            //Te[j]特别大，可能会导致r21很大然后导致大家进不来循环然后数据无法初始化出错
                            r22 = -fe * D;
                            Hertz_contact_cal(Qe[j], E, v, r11, r12, r21, r22, ae[j], akee[j]);

                            //call Hertz_contact_cal(Qi[j], E, v, 0.5*D, 0.5*D, Ti[j] / 2.0 / cos(alpha_i[j]), -fi * D, ai[j], akei[j])


                            r210 = Ti[j] / 2.0 / cos(alpha_i[j]);
                            r220 = -fi * D;
                            Hertz_contact_cal(Qi[j], E, v, r11, r12, r210, r220, ai[j], akei[j]);//往上找发现问题出在第一个子函数里面

                            //call Elliptic_integral(akee[j], L2e[j], L1e[j])
                            elliptic_integral(akee[j], L2e[j], L1e[j]);

                            //call Elliptic_integral(akei[j], L2i[j], L1i[j])
                            elliptic_integral(akei[j], L2i[j], L1i[j]);

                            Msie[j] = Qi[j] * ai[j] * L2i[j] / Qe[j] / ae[j] / L2e[j];
                            //qDebug()<<Qi[j]<< ai[j]<<L2i[j]<<Qe[j]<<ae[j]<<L2e[j];//经过测试检查@4，发现主要数组ai[]和ae[]总是会出现0等特别小的数字的情况
                            //qDebug()<<Msie[j]; //经过测试@2发现结果都是0，nan,inf！
                            lamdap[j] = (Msie[j] * (Te[j] * 1.0 / Ti[j] + 1.0)*sin(alpha_i[j]) + 2.0*sin(alpha_e[j])) / (Msie[j] * (Te[j] * 1.0 / Ti[j] + 1.0)*cos(alpha_i[j]) + 2.0*cos(alpha_e[j]) + 2.0*D / dm + D * Msie[j] * (cos(alpha_i[j] - alpha_e[j]) - Te[j] * 1.0 / Ti[j]) / dm);
                            //qDebug()<<alpha_i[j]<<alpha_e[j]; 经过测试检查@3 这两个数组没问题

                            //qDebug()<<lamdap[j]; //检测看是不是lamdap这里出了问题，经过检查测试@1，发现结果都是nan，问题就从这里开始。
                            break;
                        case(1):
                            lamdap[j] = sin(alpha_e[j]) / (cos(alpha_e[j]) + D * 1.0 / dm);//姿态角
                            break;
                        case(2):
                            lamdap[j] = sin(alpha_i[j]) / (cos(alpha_i[j]) - D * 1.0 / dm);
                            break;
                        default:
                            break;
                        }       //这之后决定了四个参数
                        eps1[j] = lamdap[j] - lamda[j];     //问题就出在这之后，为什么我的lamda,wb,SRi,SRe有问题
                        lamda[j] = (1.0 + omiga1 * eps1[j])*lamda[j];

                }
                wb[j] = wc[j] * Te[j] / D / cos(alpha_e[j] - atan(lamda[j]));
                SRi[j] = (D*sin(alpha_i[j]) + Ti[j] * (tan(alpha_i[j]) - lamda[j]) / (1.0 + lamda[j] * tan(alpha_i[j]))) / dm;
                SRe[j] = (D*sin(alpha_e[j]) - Te[j] * (tan(alpha_e[j]) - lamda[j]) / (1.0 + lamda[j] * tan(alpha_e[j]))) / dm;
                //write(*, *) eps, j, eps1[j];
                //Sleep(100);DoEvents();
                //cout << setw(20)  << eps << setw(10) << j <<setw(20)<< eps1[j] << endl;

            }

            Frp = 0.0; Fap = 0.0; Mp = 0.0;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                    cc[i][j] = 0.0;
            }

            for (int j = 0; j < Z; j++)
            {
                Frp = Frp + Qi[j] * (cos(alpha_i[j]) - u[j] * sin(alpha_i[j]))*cos(phi[j]);
                Fap = Fap + Qi[j] * (sin(alpha_i[j]) + u[j] * cos(alpha_i[j]));
                Mp = Mp + Qi[j] * (Ri*sin(alpha_i[j]) + u[j] * Ri*cos(alpha_i[j]) - u[j] * fi*D)*cos(phi[j]);
                cc[0][0] = cc[0][0] - Qi[j] * cos(phi[j])*cos(phi[j]) / Ci[j];
                cc[0][1] = cc[0][1] - Qi[j] * cos(phi[j])*(-u[j]) / Ci[j];
                cc[0][2] = cc[0][2] - Qi[j] * cos(phi[j])*(-u[j])*Ri*cos(phi[j]) / Ci[j];
                cc[1][0] = cc[1][0] - Qi[j] * u[j] * cos(phi[j]) / Ci[j];
                cc[1][1] = cc[1][1] - Qi[j] / Ci[j];
                cc[1][2] = cc[1][2] - Qi[j] * Ri*cos(phi[j]) / Ci[j];
                cc[2][0] = cc[2][0] - Qi[j] * cos(phi[j])*u[j] * Ri*cos(phi[j]) / Ci[j];
                cc[2][1] = cc[2][1] - Qi[j] * cos(phi[j])*Ri / Ci[j];
                cc[2][2] = cc[2][2] - Qi[j] * cos(phi[j])*Ri*Ri*cos(phi[j]) / Ci[j];
            }

            yy[0] = Frp - Fr;
            yy[1] = Fap - Fa;
            yy[2] = Mp - M;
            //call Gauss_cal(3, cc, yy, xx);
            int m;
            m = 3;
            double jjmx[3];
            double absmx, absa, temp, it, zz, z, sum;
            int imax, jmax, itrue;
            for (int k = 0; k < m; k++)
            {
                jjmx[k] = k;
            }
            for (int k = 0; k < m - 1; k++)
            {
                absmx = 0.0;
                imax = k;
                jmax = k;
                for (int j = k; j < m; j++)
                {
                    for (int i = k; i < m; i++)
                    {
                        absa = fabs(cc[i][j]);
                        if (absa > absmx)
                        {
                            absmx = absa;
                            imax = i;
                            jmax = j;
                        }
                    }
                }

                for (int j = k; j < m; j++)
                {
                    temp = cc[k][j];
                    cc[k][j] = cc[imax][j];
                    cc[imax][j] = temp;
                }
                temp = yy[k];
                yy[k] = yy[imax];
                yy[imax] = temp;
                for (int i = 0; i < m; i++)
                {
                    temp = cc[i][k];
                    cc[i][k] = cc[i][jmax];
                    cc[i][jmax] = temp;
                }
                it = jjmx[k];
                jjmx[k] = jjmx[jmax];
                jjmx[jmax] = it;
                zz = cc[k][k];
                for (int j = k; j < m; j++)
                {
                    cc[k][j] = cc[k][j] / zz;
                }
                yy[k] = yy[k] / zz;
                for (int i = k + 1; i < m; i++)
                {
                    z = cc[i][k];
                    for (int j = k; j < m; j++)
                    {
                        cc[i][j] = cc[i][j] - cc[k][j] * z;
                    }
                    yy[i] = yy[i] - yy[k] * z;
                }
            }
            //
            //xx[0] = yy[0] / cc[2][0];
            //xx[1] = yy[1] / cc[2][1];
            xx[2] = yy[2] / cc[2][2];
            for (int k = m - 2; k >= 0; k--)
            {
                sum = yy[k];
                for (int j = k + 1; j < m; j++)

                {
                    sum = sum - xx[j] * cc[k][j];
                }

                xx[k] = sum;
            }
            for (int j = 0; j < m; j++)
            {
                itrue = jjmx[j];
                yy[itrue] = xx[j];
            }
            for (int j = 0; j < m; j++)
            {
                xx[j] = yy[j];
            }

            eps = max(max(fabs(xx[0]), fabs(xx[1])), fabs(xx[2]));
            delta_r = delta_r + omiga * xx[0];
            delta_a = delta_a + omiga * xx[1];
            theta = theta + omiga * xx[2];
            //m_esp = floor(eps * 100000000.0f + 0.5) / 100000000.0f;
            //m_esp1 = eps1[j];
            //UpdateData(FALSE);
            //Sleep(1000);DoEvents();

    }

    //只有当程序没有被中断的时候才进行
    if(m_stop == false)
    {
        pepst[iepst] = eps;
        //最后这里再传一次信号
        //emit sdthreadtodiagro(iepst,pepst[iepst]); //用不上了

        //时间
        m_timeelapsed = m_timer->elapsed();
        if(m_stop == false && m_eccess == false)
            emit sdthreadforerro(iepst,pepst[iepst],m_timeelapsed);

        Ddeltart = floor(delta_r * 1000000.0f + 0.5) / 1000000.0f;
        Ddeltaat = floor(delta_a * 1000000.0f + 0.5) / 1000000.0f;
        Dthetat = floor(theta * 1000000.0f + 0.5) / 1000000.0f;


        for (int i = 0; i < s; i++)
        {
            Dlamdat[i] = atan(lamda[i])*180.0 / pi;
            vecsdlamdat[i] = Dlamdat[i];
            Dalphaet[i] = alpha_e[i] * 180.0 / pi;
            vecsdalphaet[i]=Dalphaet[i];
            Dalphait[i] = alpha_i[i] * 180.0 / pi;
            vecsdalphait[i]=Dalphait[i];
            DQet[i] = Qe[i];
            vecsdQet[i]=DQet[i];
            DQit[i] = Qi[i];
            vecsdQit[i]=DQit[i];
            DFct[i] = Fc[i];
            vecsdFct[i]=DFct[i];
            DMgt[i] = Mg[i];
            vecsdMgt[i]=DMgt[i];
            Dwct[i] = wc[i];
            vecsdwct[i]=Dwct[i];
            Dwbt[i] = wb[i];
            vecsdwbt[i]=Dwbt[i];
            Dut[i] = u[i];
            vecsdut[i]=Dut[i];
            DSRet[i] = SRe[i];
            vecsdSRet[i]=DSRet[i];
            DSRit[i] = SRi[i];
            vecsdSRit[i]=DSRit[i];
        }
    }


    //return 0;


    //只有在
    if(m_stop == false)
    {
        //计算完毕开始返回数值
        emit sdthreadtomain(Dthetat,Ddeltaat,Ddeltart,vecsdlamdat,vecsdalphaet,vecsdalphait,vecsdut,vecsdQet,vecsdQit,vecsdFct,vecsdMgt,vecsdwbt,vecsdwct,vecsdSRet,vecsdSRit,P0_SimuDyn);
        //告诉大家计算完了
        emit sdthreadisallover();
    }

    //释放空间
    delete[] phi;
    //real * 8, allocatable::phi(:),
    delete[] A1; delete[] A2; delete[] lamda; delete[] eps1; delete[]  alpha_e; delete[] alpha_i; delete[] delta_e; delete[]  delta_i; delete[]  u;
    //real * 8, allocatable::
    delete[] eps2; delete[] Ce; delete[] Ci; delete[] Te; delete[] Ti; delete[] wc; delete[] Fc; delete[] Mg; delete[] H1; delete[] H2; delete[] H3; delete[] H4; delete[] H5;
    //real * 8, allocatable::
    delete[] T0; delete[] wc_alpha_e; delete[] wc_alpha_i; delete[] Mg_alpha_e; delete[] Mg_alpha_i;
    //real * 8, allocatable::
    delete[] Qe; delete[] Qi; delete[] ae; delete[] ai; delete[] akee; delete[] akei; delete[] L2e; delete[] L2i; delete[] L1e; delete[] L1i; delete[] Msie;
    //real * 8, allocatable::
    delete[] lamdap; delete[] wb; delete[] SRe; delete[] SRi; delete[] wbs_i; delete[] wbs_e;

}
