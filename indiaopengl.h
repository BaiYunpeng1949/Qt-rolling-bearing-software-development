#ifndef INDIAOPENGL_H
#define INDIAOPENGL_H

#include <QMainWindow>
#include <QWidget>
#include <QOpenGLWindow>
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
#include <QStringList>

//定义一个空间使得定义数组的时候没有自由数
#define MAX_BUFFER 2048

class IndiaOpenGL : public QOpenGLWidget //, protected QOpenGLFunctions//public QOpenGLWindow //,public QWidget
{
    Q_OBJECT
public:
    explicit IndiaOpenGL(QWidget *parent = nullptr);
    ~IndiaOpenGL();

    //角度改变函数
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    //视角改变槽函数
    void dealtopview(int m_ThreeD_mode);
    //槽函数，接收文件名
    void dealSentFilename(QString filename);

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:

public slots:
    void UpdateAnimation();


private:
    //印度教学,我后来才发现这个老师是西班牙人。。。
    QOpenGLContext *m_context;
    QOpenGLFunctions *m_function;

    float m_rotation;
    float m_rotation_x;
    float m_rotation_y;
    float m_rotation_z;

    QPoint m_lastpos;

    int m_xrotation;
    int m_yrotation;
    int m_zrotation;

    QTimer *m_timer;

    QString m_line;
    QStringList m_list;
    QStringList m_list_y;

    //bool topviewset;
};

#endif // INDIAOPENGL_H
