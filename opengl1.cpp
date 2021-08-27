#include "opengl1.h"
#include "ui_opengl1.h"

OpenGL1::OpenGL1(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::OpenGL1)
{
    ui->setupUi(this);

    //印度教程
    //setSurfaceType(QWidget::QOpenGLSurface);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2,1);
    setFormat(format);

    m_context = new QOpenGLContext;
    m_context->setFormat(format);
    m_context->create();
    //m_context->makeCurrent(this);

    m_function = m_context->functions();

    //setGeometry(0,0,800,600);
    resize(800,600);
    //setWindowTitle("nnd");
}

OpenGL1::~OpenGL1()
{
    delete ui;
}

//初始化
void OpenGL1::initializeGL()
{
    //需要在调用任何gl函数前调用该函数
    this->initializeOpenGLFunctions();
}

//改变窗口大小时调用
void OpenGL1::resizeGL(int w, int h)
{
    //开始渲染前，必须告诉OpenGL渲染窗口尺寸的大小，即视口viewport
    //这样OpenGL才只能知道怎样根据窗口大小显示数据和坐标
    glViewport(0,0,w,h);
    qDebug()<<"w h"<<w<<h;
}

//每一帧绘制的函数
void OpenGL1::paintGL()
{
    //清空屏幕所用的颜色，参数分别为红绿蓝以及透明度
    //glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClearColor(1.0f,0,0,0);
    //使用三种颜色的分量可配置出超过1600万种不同的颜色
    glClear(GL_COLOR_BUFFER_BIT);//清空屏幕颜色的缓冲

    glBegin(GL_QUADS);
    glVertex2f(-0.5f,-0.5f);
    glVertex2f(0.5f,-0.5f);
    glVertex2f(0.5f,0.5f);
    glVertex2f(-0.5f,0.5f);

    glEnd();
    glFlush();
}

void OpenGL1::keyPressEvent(QKeyEvent *keyevent)
{
    //ESC按下后，关闭窗体
    switch(keyevent->key())
    {
     case Qt::Key_Escape:
        close();
        break;
    }
}

void OpenGL1::paintEvent(QPaintEvent *e)
{
    paintGL();
}
