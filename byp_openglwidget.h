#ifndef BYP_OPENGLWIDGET_H
#define BYP_OPENGLWIDGET_H

#include <QColor>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QScreen>
#include <QPixmap>
#include <QImage>

//OpenGL补充库，接口
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QSurfaceFormat>
#include <QtOpenGL>
#include <GL/glu.h>

//Excel 文件读取库
#include <QFileDialog>
#include <QAxObject>

#include <QDebug>
#include <QProcess>
#include <QPushButton>
#include <math.h>   //为了使用max函数

//定义一个空间使得定义数组的时候没有自由数
#define MAX_BUFFER 2048
#define RGB_Min 1
#define RGB_Max 255

class BYP_OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    BYP_OpenGLWidget(QWidget *parent = nullptr);

    //角度改变函数
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    //void resizeEvent(QResizeEvent *event) override;
    //void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    void qColorToRGB(const QColor &C, float &r, float &g, float &b)const;
    float normalize_0_1(float val, float min, float max) const;

    QOpenGLContext *m_context;
    QOpenGLFunctions *m_function;
    float m_rotation;
    QPoint m_lastpos;
    int m_xrotation;
    int m_yrotation;
    int m_zrotation;
    QStringList m_list;
    QString m_line;
};

#endif // BYP_OPENGLWIDGET_H
