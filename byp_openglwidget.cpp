#include "byp_openglwidget.h"

//定义一个二维数组来存坐标
double Co_Bai3[MAX_BUFFER][MAX_BUFFER];
double FindPivot_Bai3[100000];
int grid_Bai3_x,grid_Bai3_y ; //网格数
using namespace std ;

BYP_OpenGLWidget::BYP_OpenGLWidget(QWidget *parent)
    : QOpenGLWidget { parent }
{

}

//引入一个规范化数据处理函数
static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 8;
    while (angle > 360 * 8)
        angle -= 360 * 8;
}

void BYP_OpenGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xrotation) {
        m_xrotation = angle;
        update();
    }
}

void BYP_OpenGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yrotation) {
        m_yrotation = angle;
        update();
    }
}

void BYP_OpenGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zrotation) {
        m_zrotation = angle;
        update();
    }
}



void BYP_OpenGLWidget::initializeGL()
{
    float r , g, b;
    float a = normalize_0_1(255.f,RGB_Min,RGB_Max);
    initializeOpenGLFunctions();
    qColorToRGB(Qt::white,r,g,b);
    glClearColor(r,g,b,a);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void BYP_OpenGLWidget::paintGL()
{
    //float r,g,b;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //默认视图是俯视图
    //x,y,z轴依次转
    glRotatef(-(180.0f-(m_xrotation/8.0f)),1.0,0.0,0.0);
    glRotatef(-m_yrotation,0.0,1.0,0.0);
    glRotatef(m_zrotation,0.0,0.0,1.0);

    //glTranslatef(0.0,0.0,-5.0);
    //读取txt文档中的数据
    QFile File("testdata.txt");
    if(!File.open(QIODevice::ReadOnly | QIODevice ::Text))
        return;

    //初始化坐标
    int coordinate_x = 0;
    int coordinate_y = 0;
    //初始化中间变量
    //double midterm;
    //初始化一维数组
    int matter = 0;

    //确定划分网格数量
    grid_Bai3_x = 129;
    grid_Bai3_y = 129;

    QTextStream in(&File);
    while(!File.atEnd())
    {
        m_line = in.readAll();
    }
    //分割
    m_list = m_line.split("\n");
    matter = grid_Bai3_x * grid_Bai3_y -1;

    //存储数据到Co数组
    for(int count_2 = 0;count_2 <=matter;count_2++)
    {
        //得出求最大值数组先
        FindPivot_Bai3[count_2] = m_list[count_2].toDouble();
        coordinate_x = int((count_2)/grid_Bai3_y);
        coordinate_y = int((count_2)%grid_Bai3_y);
        Co_Bai3[coordinate_x][coordinate_y] =m_list[count_2].toDouble();
    }

    //找到最大值
    double pivot = *max_element(FindPivot_Bai3,FindPivot_Bai3+(matter+1));
    //曲面绘制
    //设定染色方式——平滑
    glShadeModel(GL_SMOOTH);
    //初始化坐标
    int x = 0;
    int y = 0;
    double ratio = 1.0;//0.5625; //x:y = 16:9
    //一行y一行y的画，三角条画图方式
    for(y = 0 ; y < grid_Bai3_y - 1 ; y++)   //数据网格数量
    {
        glBegin(GL_TRIANGLE_STRIP);
        for(x = 0 ; x < grid_Bai3_x ; x++) //数据网格数量
        {
            //把坐标顺便规范到-1~+1之间
            double xvalue = 2.0*double(x)/double(grid_Bai3_x-1)-1.0;
            double yvalue = (2.0*double(y)/double(grid_Bai3_y-1)-1.0)*ratio ; //按照16：9的画
            double y_value = (2.0*double(y+1)/double(grid_Bai3_y-1)-1.0)*ratio ; //按照16：9的画
            //把z方向的坐标也规范到0~+1之内
            double heightratio = Co_Bai3[x][y] / pivot ;
            double heightratio_2 = Co_Bai3[x][y+1] / pivot ;
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
            glColor3d(r_1/255,g_1/255,b_1/255);
            glVertex3d(xvalue,yvalue,heightratio);
            glColor3d(r_2/255,g_2/255,b_2/255);
            glVertex3d(xvalue,y_value,heightratio_2);
        }
        glEnd();
    }
    glFlush();


}

void BYP_OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    //qreal aspectratio = qreal(w)/qreal(h);  //
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(90,aspectratio,1,4000); //
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//void BYP_OpenGLWidget::resizeEvent(QResizeEvent *event)
//{
//    //resizeGL(this->width(),this->height()); //崩溃代码就出现在这里
//    this->update();
//}
//
//void BYP_OpenGLWidget::paintEvent(QPaintEvent *event)
//{
//    paintGL();
//}

void BYP_OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastpos = event->pos();
}

void BYP_OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_lastpos.x();
    int dy = event->y() - m_lastpos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(m_xrotation +  1 * dy);
        setYRotation(m_yrotation +  1 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(m_xrotation +  1 * dy);
        setZRotation(m_zrotation +  1 * dx);
    }
    m_lastpos = event->pos();
}

void BYP_OpenGLWidget::qColorToRGB(const QColor &C, float &r, float &g, float &b) const
{
    //int red = C.red();
    //int green = C.green();
    //int blue = C.blue();
    r = normalize_0_1(C.red(),RGB_Min,RGB_Max);
    g = normalize_0_1(C.green(),RGB_Min,RGB_Max);
    b = normalize_0_1(C.blue(),RGB_Min,RGB_Max);
}

float BYP_OpenGLWidget::normalize_0_1(float val, float min, float max) const
{
    return (val - min)/(max - min);
}
