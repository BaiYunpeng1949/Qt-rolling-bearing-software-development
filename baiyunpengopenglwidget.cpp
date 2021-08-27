#include "baiyunpengopenglwidget.h"

//定义一个二维数组来存坐标
double Co_Bai[MAX_BUFFER][MAX_BUFFER];
double FindPivot_Bai[100000];
int grid_Bai_x,grid_Bai_y ; //网格数
using namespace std ;

BaiYunpengOpenGLWidget::BaiYunpengOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent),
    m_whichview(0)
    //QWidget(parent)
{
    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&BaiYunpengOpenGLWidget::UpdateAnimation);
    m_timer->start(100);
    m_rotation = 0;
}

//定义析构函数
BaiYunpengOpenGLWidget::~BaiYunpengOpenGLWidget()
{
    //setSurfaceType(QWindow::OpenGLSurface);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2,1);
    setFormat(format);

    m_context = new QOpenGLContext;
    m_context->setFormat(format);
    m_context->create();
    //m_context->makeCurrent();

    m_function = m_context->functions();
}

void BaiYunpengOpenGLWidget::initializeGL()
{
    glClearColor(255.0,255.0,255.0,1.0);
    glEnable(GL_DEPTH_TEST);
    resizeGL(this->width(),this->height());
}

void BaiYunpengOpenGLWidget::resizeGL(int w, int h)
{
    //set viewport
    glViewport(0,0,w,h);    //视口坐标左下角定义在屏幕左下角
    qreal aspectratio = qreal(w)/qreal(h);

    //initialize projection matrix
    glMatrixMode(GL_PROJECTION);    //将当前矩阵指定为投影矩阵
    glLoadIdentity();       //重置当前指定矩阵为单位矩阵

    //gluperspective 原函数定义：
    //void gluPerspective(GLdouble fovy,GLdouble aspect,GLdouble zNear, GLdouble zFar);
    //gluPerspective(75,aspectratio,1.0,400000);   //它们生成的矩阵会与当前的矩阵相乘,生成透视的效果

    //initialize Model View Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    update();
}

void BaiYunpengOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清空屏幕颜色的缓冲

    //glColor3f(1,1,0);
    //glBegin(GL_TRIANGLES);
    //    glVertex3f(-0.5,-0.5,0);
    //    glVertex3f( 0.5,-0.5,0);
    //    glVertex3f( 0.0, 0.5,0);
    //glEnd();

    //Reset Model View Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    ////3D Transformation
    //glTranslatef(0.0,0.0,-3.0);

    //切换视图
    switch(m_whichview)
    {
        case 1:qDebug()<<"1";break;   //俯视图
        case 2:
        {
            glRotatef(90,0.0,1.0,0.0);
            glRotatef(-90,1.0,0.0,0.0);
            qDebug()<<"2";
        }
        break;   //主视图
        case 3:
        {
            glRotatef(90,1.0,0.0,0.0);
            glRotatef(180,0.0,1.0,0.0);
            qDebug()<<"3";
        }
        break;   //侧视图
        default:break;
    }

    //默认视图是俯视图
    //侧视图变化
    //glRotatef(90,0.0,1.0,0.0);
    //glRotatef(-90,1.0,0.0,0.0);
    //主视图b变化
    //glRotatef(90,1.0,0.0,0.0);
    //glRotatef(180,0.0,1.0,0.0);

    //读取txt文档中的数据
    QFile File("testdata.txt");
    if(!File.open(QIODevice::ReadOnly | QIODevice ::Text))
        return;

    //初始化坐标
    int coordinate_x = 0;
    int coordinate_y = 0;

    //初始化一维数组
    int matter = 0;

    //确定划分网格数量
    grid_Bai_x = 129;
    grid_Bai_y = 129;

    QTextStream in(&File);
    while(!File.atEnd())
    {
        m_line_0 = in.readAll();
    }
    //分割
    m_list_0 = m_line_0.split("\n");
    matter = grid_Bai_x * grid_Bai_y -1;

    //存储数据到Co数组
    for(int count_2 = 0;count_2 <=matter;count_2++)
    {
        //得出求最大值数组先
        FindPivot_Bai[count_2] = m_list_0[count_2].toDouble();
        coordinate_x = int((count_2)/grid_Bai_y);
        coordinate_y = int((count_2)%grid_Bai_y);
        Co_Bai[coordinate_x][coordinate_y] =m_list_0[count_2].toDouble();
    }

    //找到最大值
    double pivot = *max_element(FindPivot_Bai,FindPivot_Bai+(matter+1));
    //曲面绘制
    //设定染色方式——平滑
    glShadeModel(GL_SMOOTH);
    //初始化坐标
    int x = 0;
    int y = 0;
    double ratio = 1.0; //x:y = 1:1
    //一行y一行y的画，三角条画图方式
    for(y = 0 ; y < grid_Bai_y - 1 ; y++)   //数据网格数量
    {
        glBegin(GL_TRIANGLE_STRIP);
        for(x = 0 ; x < grid_Bai_x ; x++) //数据网格数量
        {
            //把坐标顺便规范到-1~+1之间
            double xvalue = 2.0*double(x)/double(grid_Bai_x-1)-1.0;
            double yvalue = (2.0*double(y)/double(grid_Bai_y-1)-1.0)*ratio ; //按照16：9的画
            double y_value = (2.0*double(y+1)/double(grid_Bai_y-1)-1.0)*ratio ; //按照16：9的画
            //把z方向的坐标也规范到0~+1之内
            double heightratio = Co_Bai[x][y] / pivot ;
            double heightratio_2 = Co_Bai[x][y+1] / pivot ;
            //初始化r,g,b,做成递增型
            double  r_1 = 0,g_1 = 0,b_1 = 0;
            double  r_2 = 0,g_2 = 0,b_2 = 0;
            //计算本次高度所占比例来分配颜色
            //按照颜色来分层画图，先定义不同情况下的r_1,g_1,b_1,主要分成6层
            //欧拉！！！！！！
            //实验_5色法着色_成功！
            if(heightratio==0 )
            {
                r_1 = 0;
                g_1 = 0;
                b_1 = 125;
            }

            else if(heightratio*4<1 )
            {
                r_1 = 0;
                g_1 = 255*heightratio*4;
                b_1 = 255;
            }

            else if(heightratio*4<2 )
            {
                r_1  = 0;
                g_1  = 255;
                b_1  = 255-255*(heightratio*4-1);
            }

            else if(heightratio*4<3 )
            {
                r_1 = 255*(heightratio*4-2);
                g_1 = 255;
                b_1 = 0;
            }

            else if(heightratio*4<4 )
            {
                r_1 = 255;
                g_1 = 255-255*(heightratio*4-3);
                b_1 = 0;
            }

            //2nd
            if(heightratio==0)
            {
                r_2 = 0;
                g_2 = 0;
                b_2 = 125;
            }

            else if(heightratio_2*4<1 )
            {
                r_2 = 0;
                g_2 = 255*heightratio_2*4;
                b_2 = 255;
            }

            else if(heightratio_2*4<2 )
            {
                r_2  = 0;
                g_2  = 255;
                b_2  = 255-255*(heightratio_2*4-1);
            }

            else if(heightratio_2*4<3 )
            {
                r_2 = 255*(heightratio_2*4-2);
                g_2 = 255;
                b_2 = 0;
            }

            else if(heightratio_2*4<4 )
            {
                r_2 = 255;
                g_2 = 255-255*(heightratio_2*4-3);
                b_2 = 0;
            }

            //根据已有的颜色把点画出来
            //注意，顺序由画点方式决定
            //判断完，把点画在-1~+1之间
            double zed,zed_2;
            zed = heightratio - 0.5;
            zed_2 = heightratio_2 - 0.5;
            glColor3d(r_1/255,g_1/255,b_1/255);
            glVertex3d(xvalue,yvalue,zed);
            glColor3d(r_2/255,g_2/255,b_2/255);
            glVertex3d(xvalue,y_value,zed_2);
        }
        glEnd();
    }
    glFlush();
}

void BaiYunpengOpenGLWidget::resizeEvent(QResizeEvent *event)
{
    resizeGL(this->width(),this->height());
    this->update();
}

//画图
void BaiYunpengOpenGLWidget::paintEvent(QPaintEvent *event)
{
    paintGL();
}

//接收信号
void BaiYunpengOpenGLWidget::dealCloudviewport(int integer)
{
    m_whichview = integer;
    this->update();
}

void BaiYunpengOpenGLWidget::UpdateAnimation()
{
    //m_rotation += 45;
    this->update();
}
