#include "indiaopengl.h"

//定义一个二维数组来存坐标
double Co[MAX_BUFFER][MAX_BUFFER];
double FindPivot[100000];
int grid_x,grid_y ; //网格数
double pivot;
QString ThreeD_Filename;

using namespace std ;


IndiaOpenGL::IndiaOpenGL(QWidget *parent) :
    QOpenGLWidget ( parent )
    //QWidget(parent),
    //QWindow(parent)
{
    //重新定义大小
    //this->resize(1000,800);
    //setSurfaceType(QWindow::OpenGLSurface);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2,1);
    setFormat(format);

    m_context = new QOpenGLContext;
    m_context->setFormat(format);
    m_context->create();
    //m_context->makeCurrent(this);

    m_function = m_context->functions();

    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&IndiaOpenGL::UpdateAnimation);
    m_timer->start(100);
    m_rotation = 0;
}

//没写析构函数会编译不过的！！！
IndiaOpenGL::~IndiaOpenGL()
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


void IndiaOpenGL::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xrotation) {
        m_xrotation = angle;
        update();
    }
}

void IndiaOpenGL::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yrotation) {
        m_yrotation = angle;
        update();
    }
}

void IndiaOpenGL::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zrotation) {
        m_zrotation = angle;
        update();
    }
}

//改变视角的槽函数
void IndiaOpenGL::dealtopview(int m_ThreeD_mode)
{
    switch (m_ThreeD_mode) {
    case 0:
        {
            m_rotation_x = 180;
            m_rotation_y = 0;
            m_rotation_z = 0;
        }
        break;

    case 1:
        {
            m_rotation_x = 0;
            m_rotation_y = 0;
            m_rotation_z = 90;
        }
        break;
    }
    this->update();
}



void IndiaOpenGL::initializeGL()
{
    //initializeOpenGLFunctions();
    //尺寸
    //this->setTitle("IndiaOpenGL_Test");
    glEnable(GL_DEPTH_TEST);
    //resize(800,600);
    resizeGL(this->width(),this->height());
}

void IndiaOpenGL::resizeGL(int w, int h)
{
    //set viewport
    glViewport(0,0,w,h);    //视口坐标左下角定义在屏幕左下角
    qreal aspectratio = qreal(w)/qreal(h);

    //initialize projection matrix
    glMatrixMode(GL_PROJECTION);    //将当前矩阵指定为投影矩阵
    glLoadIdentity();       //重置当前指定矩阵为单位矩阵

    //gluperspective 原函数定义：
    //void gluPerspective(GLdouble fovy,GLdouble aspect,GLdouble zNear, GLdouble zFar);
    gluPerspective(75,aspectratio,0.1,400000000);   //它们生成的矩阵会与当前的矩阵相乘,生成透视的效果

    //initialize Model View Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,w,h);
    qreal aspectratio = qreal(w)/qreal(h);
    glOrtho(-1*aspectratio,1*aspectratio,-1,1,1,-1);
    */
}

void IndiaOpenGL::paintGL()
{
    //清空屏幕所用的颜色，参数分别为红绿蓝以及透明度
    //glClearColor(0.2f,0.3f,0.3f,1.0f);
    //glClearColor(1.0f,0,0,0);
    //使用三种颜色的分量可配置出超过1600万种不同的颜色
    glClearColor(255.0f,251.0f,240.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清空屏幕颜色的缓冲

    //Reset Model View Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //3D Transformation
    glTranslatef(0.0,0.0,-2.5);

    //默认视图是俯视图
    //x,y,z轴依次转
    glRotatef(-(180.0f-(m_xrotation/8.0f)),1.0,0.0,0.0);
    glRotatef(-m_yrotation,0.0,1.0,0.0);
    glRotatef(m_zrotation,0.0,0.0,1.0);
    //glRotatef(m_rotation,0.0,0.0,1.0);
    //glRotatef(m_rotation_x,1.0,0.0,0.0);
    //glRotatef(m_rotation_y,0.0,1.0,0.0);
    //glRotatef(m_rotation_z,0.0,0.0,1.0);
    //qDebug()<<m_rotation_x<<m_rotation_y<<m_rotation_z;



    ////曲面绘制
    //设定染色方式——平滑
    glShadeModel(GL_SMOOTH);
    //初始化坐标
    int x = 0;
    int y = 0;

    //一行y一行y的画，三角条画图方式
    for(y = 0 ; y < grid_y - 1 ; y++)   //数据网格数量
    {
        glBegin(GL_TRIANGLE_STRIP);
        for(x = 0 ; x < grid_x ; x++) //数据网格数量
        {
            //把坐标顺便规范到-1~+1之间
            double xvalue = 2.0*double(x)/double(grid_x-1)-1.0;
            double yvalue = 2.0*double(y)/double(grid_y-1)-1.0;
            double y_value = 2.0*double(y+1)/double(grid_y-1)-1.0;
            //qDebug()<<xvalue<<" "<<yvalue<<" "<<y_value;
            //初始化r,g,b,做成递增型
            double  r_1= 0,g_1= 0,b_1= 0;
            double  r_2= 0,g_2= 0,b_2= 0;
            //计算本次高度所占比例来分配颜色
            //把z方向的坐标也规范到0~+1之内
            double heightratio = Co[x][y] / pivot ;
            double heightratio_2 = Co[x][y+1] / pivot ;

            //按照颜色来分层画图，先定义不同情况下的r_1,g_1,b_1,主要分成6层
            //欧拉！！！！！！
            //实验_5色法着色_成功！
            if(heightratio<=0.000001 )
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
            if(heightratio_2<=0.000001 )
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

    this->makeCurrent(); //尝试一下
}

void IndiaOpenGL::resizeEvent(QResizeEvent *event)
{
    resizeGL(this->width(),this->height());
    this->update();

}

void IndiaOpenGL::paintEvent(QPaintEvent *event)
{
    this->makeCurrent();    //神来之笔！
    paintGL();
    //this->update();
}

void IndiaOpenGL::mousePressEvent(QMouseEvent *event)
{
    m_lastpos = event->pos();
}

void IndiaOpenGL::mouseMoveEvent(QMouseEvent *event)
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
    this->update();
}

void IndiaOpenGL::UpdateAnimation()
{
    m_rotation += 10;
    this->update();
}

//接收文件名槽函数
void IndiaOpenGL::dealSentFilename(QString filename)
{
    ThreeD_Filename = filename;
    ////读取txt文档中的数据
    //QFile File("testdata2.txt");
    QFile File(ThreeD_Filename);    //读取给定的文件
    if(!File.open(QIODevice::ReadOnly | QIODevice ::Text))
        return;

    //初始化坐标
    //int coordinate_x = 0;
    //int coordinate_y = 0;
    //初始化一维数组
    int matter = 0;
    //初始化划分网格数量
    grid_x = 0;
    grid_y = 0;

    //第一遍读取看看有多少行，确定grid_x的值
    QTextStream in(&File);
    while(!File.atEnd())
    {
        m_line = in.readAll();
    }
    //分割
    m_list = m_line.split("\n");
    //得到grid_x的数字
    grid_x = m_list.size() - 1; //这里要注意！ \n 会多份出来一个元素

    //第二遍循环看有多少列，确定grid_y的值
    m_list_y = m_list[0].split("\t");
    grid_y = m_list_y.size();

    //计算总数
    matter = grid_x * grid_y -1;
    int findit = 0;

    //存储数据到Co数组
    for(int item_x=0;item_x<grid_x;item_x++)
    {
        //获取这一行的所有数据并且分割好
        m_list_y = m_list[item_x].split("\t");
        for(int item_y=0;item_y<grid_y;item_y++)
        {
            //给最大值数组先赋值
            FindPivot[findit] = m_list_y[item_y].toDouble();
            findit++;
            //给坐标组赋值
            Co[item_x][item_y] = m_list_y[item_y].toDouble();
        }
    }



    //存储数据到Co数组
    //for(int count_2 = 0;count_2 <=matter;count_2++)
    //{
    //    //得出求最大值数组先
    //    FindPivot[count_2] = m_list[count_2].toDouble();
    //    coordinate_x = int((count_2)/grid_y);
    //    coordinate_y = int((count_2)%grid_y);
    //    Co[coordinate_x][coordinate_y] =m_list[count_2].toDouble();
    //}
    //找到最大值
    pivot = *max_element(FindPivot,FindPivot+(matter+1));
}
