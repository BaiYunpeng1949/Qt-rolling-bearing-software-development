#include "stathread.h"

//补充学长以前C++中的头文件
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include<math.h>


//把学长开头的声明也拷贝过来，不然会无法通过编译，无法识别ofstream之类的
using namespace std;
/*extern*/ double Sdeltar, Sdeltaa, Stheta, Salpha[100], SQ[100];

//定义两个可以被传递的数组
QVector<double> vecsalpha(100);
QVector<double> vecsq(100);


StaThread::StaThread(QObject *parent) : QObject(parent)
{
    //与自己建立连接，告诉自己计算结束了
    connect(this,&StaThread::staprogress,&stadiaprogress,&Sta_DiaProgress::dealstaprogress);
}


//线程中的计算函数，将要被调用
void StaThread::sta(int z, double D, double dm, double alpha0, double fi, double fe, double Fr, double Fa, double M)
{
    int s, j;
    double pi;
    double A0, Ri, Kn, delta_r, delta_a, theta, err;//nc, nb, wc, wb,  /n L
    double Frp, Fap, Mp;
    double c[3][3], x[3], y[3];



    s = z;

    double* phi = new double[s]; //real * 8, allocatable::phi(:), ci(:), co(:), p(:), delta_n(:), Q(:)
    double* ci = new double[s];
    double* co = new double[s];
    double* p = new double[s];
    double* delta_n = new double[s];
    double* Q = new double[s];

    double* s_alpha = new double[s];//real * 8, allocatable::s_alpha(:), c_alpha(:), Qr(:), Qa(:), alpha(:)
    double* c_alpha = new double[s];
    double* Qr = new double[s];
    double* Qa = new double[s];
    double* alpha = new double[s];

    double* n_r = new double[s];//real * 8, allocatable::n_r(:), n_a(:), n_t(:), c_r(:), c_a(:), c_t(:), s_r(:), s_a(:), s_t(:)
    double* n_a = new double[s];
    double* n_t = new double[s];
    double* c_r = new double[s];
    double* c_a = new double[s];
    double* c_t = new double[s];
    double* s_r = new double[s];
    double* s_a = new double[s];
    double* s_t = new double[s];

    pi = 4 * atan(1.0);

    alpha0 = alpha0 * pi / 180;
    A0 = (fi + fe - 1.0)*D;
    Ri = 0.5*dm + (fi*D - 0.5*D)*cos(alpha0);

    Kn = 1.3997*pow(10.0, 0.5)*pow(10.0, 5.0);

    delta_r = 0.01 / A0;
    delta_a = 0.01 / A0;;
    theta = 0.0;
    err = 1.0;
    while (err > 1e-7)//pow(10.0, -7)
    {

        Frp = 0.0; Fap = 0.0; Mp = 0.0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                c[i][j] = 0.0;
            }
        }
        for (int i = 0; i < z; i++)
        {
            phi[i] = 2.0*pi*(i - 1) / z;
            ci[i] = sin(alpha0) + delta_a + Ri * theta*cos(phi[i]);
            co[i] = cos(alpha0) + delta_r * cos(phi[i]);
            p[i] = pow(ci[i], 2) + pow(co[i], 2);
            delta_n[i] = A0 * (pow(p[i], 0.5) - 1.0);
            if (delta_n[i] < 0.0)
            {
                delta_n[i] = 0.0;
            }

            Q[i] = Kn * pow(delta_n[i], 1.5);
            s_alpha[i] = ci[i] / pow(p[i], 0.5);
            c_alpha[i] = co[i] / pow(p[i], 0.5);
            Qr[i] = Q[i] * c_alpha[i] * cos(phi[i]);
            Qa[i] = Q[i] * s_alpha[i];
            Frp = Frp + Qr[i];
            Fap = Fap + Qa[i];
            Mp = Mp + 0.5*dm*Q[i] * s_alpha[i] * cos(phi[i]);
            n_r[i] = A0 * co[i] * cos(phi[i]) / pow(p[i], 0.5);
            n_a[i] = A0 * ci[i] / pow(p[i], 0.5);
            n_t[i] = A0 * ci[i] * Ri*cos(phi[i]) / pow(p[i], 0.5);
            c_r[i] = cos(phi[i])*(p[i] - pow(co[i], 2)) / pow(p[i], 1.5);
            c_a[i] = -co[i] * ci[i] / pow(p[i], 1.5);
            c_t[i] = -co[i] * ci[i] * Ri*cos(phi[i]) / pow(p[i], 1.5);
            s_r[i] = -co[i] * ci[i] * cos(phi[i]) / pow(p[i], 1.5);
            s_a[i] = (p[i] - pow(ci[i], 2)) / pow(p[i], 1.5);
            s_t[i] = Ri * cos(phi[i])*(p[i] - pow(ci[i], 2)) / pow(p[i], 1.5);
            c[0][0] = c[0][0] - Kn * cos(phi[i])*(c_alpha[i] * 1.5*pow(delta_n[i], 0.5)*n_r[i] + pow(delta_n[i], 1.5)*c_r[i]);
            c[0][1] = c[0][1] - Kn * cos(phi[i])*(c_alpha[i] * 1.5*pow(delta_n[i], 0.5)*n_a[i] + pow(delta_n[i], 1.5)*c_a[i]);
            c[0][2] = c[0][2] - Kn * cos(phi[i])*(c_alpha[i] * 1.5*pow(delta_n[i], 0.5)*n_t[i] + pow(delta_n[i], 1.5)*c_t[i]);
            c[1][0] = c[1][0] - Kn * (s_alpha[i] * 1.5*pow(delta_n[i], 0.5)*n_r[i] + pow(delta_n[i], 1.5)*s_r[i]);
            c[1][1] = c[1][1] - Kn * (s_alpha[i] * 1.5*pow(delta_n[i], 0.5)*n_a[i] + pow(delta_n[i], 1.5)*s_a[i]);
            c[1][2] = c[1][2] - Kn * (s_alpha[i] * 1.5*pow(delta_n[i], 0.5)*n_t[i] + pow(delta_n[i], 1.5)*s_t[i]);
            c[2][0] = c[2][0] - 0.5*dm*Kn*cos(phi[i])*(s_alpha[i] * 1.5*pow(delta_n[i], 0.5)*n_r[i] + pow(delta_n[i], 1.5)*s_r[i]);
            c[2][1] = c[2][1] - 0.5*dm*Kn*cos(phi[i])*(s_alpha[i] * 1.5*pow(delta_n[i], 0.5)*n_a[i] + pow(delta_n[i], 1.5)*s_a[i]);
            c[2][2] = c[2][2] - 0.5*dm*Kn*cos(phi[i])*(s_alpha[i] * 1.5*pow(delta_n[i], 0.5)*n_t[i] + pow(delta_n[i], 1.5)*s_t[i]);
        }
        y[0] = Frp - Fr;
        y[1] = Fap - Fa;
        y[2] = Mp - M;

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
        //x[0] = y[0] / c[2][0];x[1] = y[1] / c[2][1];
        x[2] = y[2] / c[2][2];
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
            itrue = jjmx[j];
            y[itrue] = x[j];
        }
        for (int j = 0; j < m; j++)
        {
            x[j] = y[j];
        }

        err = max(max(fabs(x[1]), fabs(x[2])), (fabs(x[0])));
        delta_r = delta_r + x[0];
        delta_a = delta_a + x[1];
        theta = theta + x[2];
    }

    for (int i = 0; i < z; i++)
    {
        ci[i] = sin(alpha0) + delta_a + Ri * theta*cos(phi[i]);
        co[i] = cos(alpha0) + delta_r * cos(phi[i]);
        p[i] = pow(ci[i], 2) + pow(co[i], 2);
        delta_n[i] = A0 * (pow(p[i], 0.5) - 1);
        c_alpha[i] = co[i] / pow(p[i], 0.5);
        alpha[i] = acos(c_alpha[i]);
        if (delta_n[i] < 0.0)
        {
            delta_n[i] = 0.0;
        }
        Q[i] = Kn * pow(delta_n[i], 1.5);
    }

    delta_r = delta_r * A0;
    delta_a = delta_a * A0;
    theta = theta * A0;

    Sdeltar = floor(delta_r * 1000000.0f + 0.5) / 1000000.0f;
    Sdeltaa = floor(delta_a * 1000000.0f + 0.5) / 1000000.0f;
    Stheta = floor(theta * 1000000.0f + 0.5) / 1000000.0f;

    for (j = 0;j<z;j++)
    {
        Salpha[j] = floor(alpha[j] / pi * 180 * 1000000.0f + 0.5) / 1000000.0f;
        vecsalpha[j]=Salpha[j];
        SQ[j] = floor(Q[j] * 1000000.0f + 0.5) / 1000000.0f;
        vecsq[j]=SQ[j];
    }

    double alpha1 = alpha0 / 4 / atan(1.0) * 180.0;

    delete[] phi; delete[] ci; delete[] co; delete[] p; delete[] delta_n; delete[] Q;
    delete[] s_alpha; delete[] c_alpha; delete[] Qr; delete[] Qa; delete[] alpha;
    delete[] n_r; delete[] n_a; delete[] n_t; delete[] c_r; delete[] c_a; delete[] c_t; delete[] s_r; delete[] s_a; delete[] s_t;


    //计算结束将数据返回给主图形界面线程再进行分配
    emit stasendback(Sdeltar,Sdeltaa,Stheta,vecsalpha,vecsq);
    //发出信号告诉大家sta计算完了
    emit staprogress();
}


